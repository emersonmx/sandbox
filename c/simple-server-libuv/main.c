#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>

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
            uv_write(req, client, &wrbuf, 1, req_write_cb);
        } else {
            const char *res = "HTTP/1.1 404 Not Found\r\n"
                              "Content-Length: 9\r\n"
                              "\r\n"
                              "Not Found";
            uv_write_t *req = malloc(sizeof(uv_write_t));
            uv_buf_t wrbuf = uv_buf_init((char *)res, strlen(res));
            uv_write(req, client, &wrbuf, 1, req_write_cb);
        }

        uv_close((uv_handle_t *)client, (void (*)(uv_handle_t *))free);
    } else if (nread < 0)
        uv_close((uv_handle_t *)client, (void (*)(uv_handle_t *))free);

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
        uv_close((uv_handle_t *)client, (void (*)(uv_handle_t *))free);
        return;
    }

    printf("accepted new connection\n");
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

    uv_tcp_t server;
    err = uv_tcp_init(loop, &server);
    if (err) {
        fprintf(stderr, "tcp init error: %s\n", uv_strerror(err));
        return 1;
    }

    err = uv_ip4_addr(host, port, &addr);
    if (err) {
        fprintf(stderr, "ip4 addr error: %s\n", uv_strerror(err));
        return 1;
    }

    err = uv_tcp_bind(&server, (const struct sockaddr *)&addr, 0);
    if (err) {
        fprintf(stderr, "bind error: %s\n", uv_strerror(err));
        return 1;
    }

    printf("server listening on %s:%d\n", host, port);
    err = uv_listen((uv_stream_t *)&server, default_backlog, on_new_connection);
    if (err) {
        fprintf(stderr, "listen error: %s\n", uv_strerror(err));
        return 1;
    }

    return uv_run(loop, UV_RUN_DEFAULT);
}
