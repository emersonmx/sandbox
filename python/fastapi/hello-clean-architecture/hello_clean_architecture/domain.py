from dataclasses import dataclass


@dataclass
class Post:
    slug: str
    title: str
    content: str
