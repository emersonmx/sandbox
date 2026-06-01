import dataclasses
from typing import List

from fastapi import APIRouter
from pydantic import BaseModel

from hello_clean_architecture.service import Post

from ..factories import make_post_service


class PostSchema(BaseModel):
    slug: str
    title: str
    content: str


router = APIRouter()


@router.get("/")
async def get_all() -> List[PostSchema]:
    service = make_post_service()
    posts: List[Post] = await service.get_all()
    return [PostSchema(**dataclasses.asdict(p)) for p in posts]


@router.post("/")
async def create(post: PostSchema) -> PostSchema:
    service = make_post_service()
    new_post: Post = await service.create(Post(**post.dict()))
    return PostSchema(**dataclasses.asdict(new_post))
