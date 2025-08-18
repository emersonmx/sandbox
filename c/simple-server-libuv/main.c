#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>

static uv_tcp_t *server = NULL;
static uv_signal_t *sig = NULL;

void server_close_cb(uv_handle_t *handle)
{
    free(handle);
    server = NULL;
}

void signal_close_cb(uv_handle_t *handle)
{
    free(handle);
    if ((uv_signal_t *)handle == sig) {
        sig = NULL;
    }
}

void signal_cb(uv_signal_t *handle, int signum)
{
    printf("\nReceived SIGINT, shutting down gracefully...\n");
    if (server) {
        uv_close((uv_handle_t *)server, server_close_cb);
    }
    uv_signal_stop(handle);
    uv_close((uv_handle_t *)handle, signal_close_cb);
}

void client_close_cb(uv_handle_t *client)
{
    free(client);
}

void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf)
{
    buf->base = (char *)malloc(suggested_size);
    if (buf->base == NULL) {
        fprintf(stderr, "failed to allocate memory for buffer\n");
        buf->len = 0;
    } else
        buf->len = suggested_size;
}

void req_write_cb(uv_write_t *req, int status)
{
    if (status < 0)
        fprintf(stderr, "write error: %s\n", uv_strerror(status));

    free(req);
}

void read_cb(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf)
{
    if (nread > 0) {
        if (strncmp(buf->base, "GET /", 5) == 0) {
            const char *res = "HTTP/1.1 200 OK\r\n"
                              "Content-Type: text/plain\r\n"
                              "Content-Length: 13\r\n"
                              "\r\n"
                              "Hello, World!";
            uv_write_t *req = malloc(sizeof(uv_write_t));
            uv_buf_t wrbuf = uv_buf_init((char *)res, strlen(res));
            int err = uv_write(req, client, &wrbuf, 1, req_write_cb);
            if (err) {
                fprintf(stderr, "write error: %s\n", uv_strerror(err));
                free(req);
            }
        } else {
            const char *res = "HTTP/1.1 404 Not Found\r\n"
                              "Content-Length: 9\r\n"
                              "\r\n"
                              "Not Found";
            uv_write_t *req = malloc(sizeof(uv_write_t));
            uv_buf_t wrbuf = uv_buf_init((char *)res, strlen(res));
            int err = uv_write(req, client, &wrbuf, 1, req_write_cb);
            if (err) {
                fprintf(stderr, "write error: %s\n", uv_strerror(err));
                free(req);
            }
        }

        uv_close((uv_handle_t *)client, client_close_cb);
    } else if (nread < 0)
        uv_close((uv_handle_t *)client, client_close_cb);

    if (buf->base)
        free(buf->base);
}

void on_new_connection(uv_stream_t *server, int status)
{
    if (status < 0) {
        fprintf(stderr, "new connection error: %s\n", uv_strerror(status));
        return;
    }

    uv_tcp_t *client = malloc(sizeof(uv_tcp_t));
    if (client == NULL) {
        fprintf(stderr, "failed to allocate memory for client\n");
        return;
    }

    int err = uv_tcp_init(server->loop, client);
    if (err) {
        fprintf(stderr, "tcp init error: %s\n", uv_strerror(err));
        free(client);
        return;
    }

    err = uv_accept(server, (uv_stream_t *)client);
    if (err) {
        fprintf(stderr, "accept error: %s\n", uv_strerror(err));
        uv_close((uv_handle_t *)client, client_close_cb);
        return;
    }

    struct sockaddr_in peer_addr;
    int addr_len = sizeof(peer_addr);
    err = uv_tcp_getpeername(client, (struct sockaddr *)&peer_addr, &addr_len);
    if (err)
        printf("accepted new connection (unable to get peer address)\n");
    else {
        char ip[INET_ADDRSTRLEN];
        uv_ip4_name(&peer_addr, ip, sizeof(ip));
        printf("connection from %s:%d\n", ip, ntohs(peer_addr.sin_port));
    }

    err = uv_read_start((uv_stream_t *)client, alloc_buffer, read_cb);
    if (err) {
        fprintf(stderr, "read start error: %s\n", uv_strerror(err));
    }
}

int main()
{
    uv_loop_t *loop = uv_default_loop();
    if (loop == NULL) {
        fprintf(stderr, "failed to create default loop\n");
        return 1;
    }

    struct sockaddr_in addr;
    int err;
    char *host = "0.0.0.0";
    uint16_t port = 8000;
    size_t default_backlog = 128;

    server = malloc(sizeof(uv_tcp_t));
    if (server == NULL) {
        fprintf(stderr, "failed to allocate memory for server\n");
        return 1;
    }

    err = uv_tcp_init(loop, server);
    if (err) {
        fprintf(stderr, "tcp init error: %s\n", uv_strerror(err));
        free(server);
        return 1;
    }

    err = uv_ip4_addr(host, port, &addr);
    if (err) {
        fprintf(stderr, "ip4 addr error: %s\n", uv_strerror(err));
        free(server);
        return 1;
    }

    err = uv_tcp_bind(server, (const struct sockaddr *)&addr, 0);
    if (err) {
        fprintf(stderr, "bind error: %s\n", uv_strerror(err));
        free(server);
        return 1;
    }

    err = uv_listen((uv_stream_t *)server, default_backlog, on_new_connection);
    if (err) {
        fprintf(stderr, "listen error: %s\n", uv_strerror(err));
        free(server);
        return 1;
    }

    sig = malloc(sizeof(uv_signal_t));
    if (sig == NULL) {
        fprintf(stderr, "failed to allocate memory for signal handle\n");
        free(server);
        return 1;
    }

    err = uv_signal_init(loop, sig);
    if (err) {
        fprintf(stderr, "signal init error: %s\n", uv_strerror(err));
        free(sig);
        uv_close((uv_handle_t *)server, server_close_cb);
        uv_run(loop, UV_RUN_DEFAULT);
        return 1;
    }

    err = uv_signal_start(sig, signal_cb, SIGINT);
    if (err) {
        fprintf(stderr, "signal start error: %s\n", uv_strerror(err));
        uv_close((uv_handle_t *)sig, signal_close_cb);
        uv_close((uv_handle_t *)server, server_close_cb);
        uv_run(loop, UV_RUN_DEFAULT);
        return 1;
    }

    printf("server listening on %s:%d\n", host, port);
    printf("press ctrl+c to stop the server...\n");
    return uv_run(loop, UV_RUN_DEFAULT);
}
