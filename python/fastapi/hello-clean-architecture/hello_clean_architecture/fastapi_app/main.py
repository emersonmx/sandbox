from fastapi import FastAPI


def create_app() -> FastAPI:
    from . import events, middlewares, routes

    app = FastAPI()

    events.init_app(app)
    middlewares.init_app(app)
    routes.init_app(app)

    return app
