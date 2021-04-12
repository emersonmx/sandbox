from invoke import task
from invoke.context import Context


@task
def run(c):
    # type: (Context) -> None
    c.run("python src/main/game.py")


@task
def format(c):
    # type: (Context) -> None
    c.run("black .")
    c.run("isort .")


@task
def check_format(c):
    # type: (Context) -> None
    c.run("black --check .")
    c.run("isort --check .")


@task
def lint(c):
    # type: (Context) -> None
    c.run("flake8 .")
    c.run("mypy .")


@task
def tests(c):
    # type: (Context) -> None
    c.run("coverage run -m pytest .")


@task
def coverage(c):
    # type: (Context) -> None
    c.run("coverage report")


@task(check_format, lint, tests, coverage)
def check(c):
    # type: (Context) -> None
    pass
