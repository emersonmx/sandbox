FROM python:3.9-buster as setup

RUN : \
    && curl --location --output /virtualenv.pyz https://bootstrap.pypa.io/virtualenv.pyz \
    && python3.9 /virtualenv.pyz /opt/venv \
    && :

ENV PATH=/opt/venv/bin:$PATH

COPY requirements.txt .
RUN pip install --require-hashes -r requirements.txt

ENV DOCKERIZE_VERSION=v0.6.1
RUN : \
    && curl --location \
        -O \
        https://github.com/jwilder/dockerize/releases/download/$DOCKERIZE_VERSION/dockerize-linux-amd64-$DOCKERIZE_VERSION.tar.gz \
    && tar -C /tmp -xzvf dockerize-linux-amd64-$DOCKERIZE_VERSION.tar.gz \
    && :


FROM python:3.9-slim-buster

COPY --from=setup /opt/venv /opt/venv
COPY --from=setup /tmp/dockerize /usr/local/bin/dockerize

ENV PATH=/opt/venv/bin:$PATH \
    PYTHONDONTWRITEBYTECODE=1 \
    PYTHONUNBUFFERED=1 \
    PYTHONPATH=/app/src

WORKDIR /app

COPY . .

RUN useradd --create-home appuser
USER appuser

EXPOSE 8000

CMD ["gunicorn", "--reload", "--bind", "0.0.0.0:8000", "config.wsgi"]
