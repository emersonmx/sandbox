from datetime import datetime

from pydantic import BaseModel


class Choice(BaseModel):
    id: int
    choice_text: str
    votes: int


class Question(BaseModel):
    id: int
    question_text: str
    pub_date: datetime
    was_published_recenlty: bool
    choices: list[Choice]
