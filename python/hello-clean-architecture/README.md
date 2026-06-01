# hello-clean-architecture

## Run

```sh
docker run -d --rm \
    -e MONGO_INITDB_ROOT_USERNAME=app_user \
    -e MONGO_INITDB_ROOT_PASSWORD=app_pass \
    -e MONGO_INITDB_DATABASE=app_db \
    -p '27017:27017' \
    mongo

poetry env use 3.9
poetry install

poetry run uvicorn \
    --reload \
    --factory hello_clean_architecture.fastapi_app.main:create_app
```
