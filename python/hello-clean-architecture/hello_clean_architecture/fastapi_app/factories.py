from functools import cache

from motor.motor_asyncio import AsyncIOMotorClient, AsyncIOMotorDatabase

from hello_clean_architecture.data import PostMotorRepository, PostRepository
from hello_clean_architecture.service import PostService


@cache
def get_client() -> AsyncIOMotorClient:
    return AsyncIOMotorClient("mongodb://app_user:app_pass@localhost")


def get_db() -> AsyncIOMotorDatabase:
    client = get_client()
    return client["app_db"]


def make_post_repository() -> PostRepository:
    db = get_db()
    return PostMotorRepository(db["posts"])


def make_post_service() -> PostService:
    repository = make_post_repository()
    return PostService(repository)
