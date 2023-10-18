from fastapi import APIRouter, status

from api import schemas
from api.schemas import Question
from polls import models

router = APIRouter()


async def map_question(question: models.Question) -> schemas.Question:
    return schemas.Question(
        id=question.id,
        question_text=question.question_text,
        pub_date=question.pub_date,
        was_published_recenlty=question.was_published_recently(),
        choices=[
            schemas.Choice(id=c.id, choice_text=c.choice_text, votes=c.votes)
            async for c in question.choice_set.all()
        ],
    )


@router.get("/polls")
async def list_polls() -> list[schemas.Question]:
    return [await map_question(q) async for q in models.Question.objects.all()]


@router.get("/polls/{poll_id}")
async def show_poll(poll_id: int) -> schemas.Question:
    question = await models.Question.objects.aget(id=poll_id)
    return await map_question(question)


@router.post("/polls/vote/{choice_id}", status_code=status.HTTP_204_NO_CONTENT)
async def vote_poll(choice_id: int) -> None:
    choice = await models.Choice.objects.aget(id=choice_id)
    choice.votes += 1
    await choice.asave()
