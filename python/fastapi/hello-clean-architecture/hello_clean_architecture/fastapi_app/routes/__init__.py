from fastapi.applications import FastAPI


def init_app(app: FastAPI) -> None:
    from . import posts

    print("init routes")
    app.include_router(posts.router, prefix="/posts")
