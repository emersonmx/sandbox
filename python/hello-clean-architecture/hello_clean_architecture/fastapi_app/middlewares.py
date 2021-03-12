from fastapi.applications import FastAPI


def init_app(app: FastAPI) -> None:
    print("init middlewares")
