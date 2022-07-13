from abc import ABC, abstractmethod
from typing import Any, List

from .domain import Post

Posts = List[Post]


class PostRepository(ABC):
    @abstractmethod
    def get_all(self) -> Any:
        ...

    @abstractmethod
    def create(self, post: Post) -> Any:
        ...


class PostService:
    def __init__(self, repository: PostRepository) -> None:
        self.repository = repository

    def get_all(self) -> Any:
        return self.repository.get_all()

    def create(self, post: Post) -> Any:
        return self.repository.create(post)
