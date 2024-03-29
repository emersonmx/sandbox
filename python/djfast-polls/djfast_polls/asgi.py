"""
ASGI config for djfast_polls project.

It exposes the ASGI callable as a module-level variable named ``application``.

For more information on this file, see
https://docs.djangoproject.com/en/4.2/howto/deployment/asgi/
"""

import os

from django.core.asgi import get_asgi_application

os.environ.setdefault("DJANGO_SETTINGS_MODULE", "djfast_polls.settings")

# You must call django.setup() before using Django models. Function
# get_asgi_application() already does this internally.
django_app = get_asgi_application()


from fastapi import FastAPI

from api.routes import router as api_router

app = FastAPI(title="djfast-polls")

# The FastAPI's routes must come before django urls to avoid overlapping.
app.include_router(api_router, prefix="/api")
app.mount("/", django_app)
