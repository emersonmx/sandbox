from typing import Any, List

from motor.motor_asyncio import AsyncIOMotorCollection

from hello_clean_architecture.service import Post, PostRepository


class PostMotorRepository(PostRepository):
    def __init__(self, collection: AsyncIOMotorCollection) -> None:
        self.collection = collection

    def get_all(self) -> Any:
        async def wrap() -> List[Post]:
            return [
                Post(slug=p["_id"], title=p["title"], content=p["content"])
                async for p in self.collection.find()
            ]

        return wrap()

    def create(self, post: Post) -> Any:
        async def wrap() -> Post:
            await self.collection.insert_one(
                {
                    "_id": post.slug,
                    "title": post.title,
                    "content": post.content,
                }
            )
            return post

        return wrap()
