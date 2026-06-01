from fastapi.applications import FastAPI

from .factories import get_client


def init_app(app: FastAPI) -> None:
    print("init events")

    @app.on_event("startup")
    async def _startup() -> None:
        print("startup fastapi")

    @app.on_event("shutdown")
    async def _shutdown() -> None:
        print("shutdown fastapi")
        client = get_client()
        if client:
            client.close()
