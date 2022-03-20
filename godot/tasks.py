from invoke import Context, task


@task(aliases=["fmt"])
def format(c):
    # type: (Context) -> None
    c.run("gdformat .", pty=True)


@task
def lint(c):
    # type: (Context) -> None
    c.run("gdlint .", pty=True)


@task
def check(c):
    # type: (Context) -> None
    c.run("gdformat --check .", pty=True)
    c.run("gdlint .", pty=True)
