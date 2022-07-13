from invoke import Context, task


@task
def build_image(c):
    # type: (Context) -> None
    c.run("poetry export -o requirements.txt --without-hashes")
    c.run("docker build -t security-study .")


@task(build_image)
def run(c):
    # type: (Context) -> None
    c.run("docker-compose up")


@task(aliases=("fmt",))
def format(c, all_files=False):
    # type: (Context, bool) -> None
    precommit_options = []

    if all_files:
        precommit_options.append("--all-files")

    hooks = [
        "end-of-file-fixer",
        "trailing-whitespace",
        "pyupgrade",
        "add-trailing-comma",
        "yesqa",
        "isort",
        "black",
    ]
    for hook in hooks:
        cmd = " ".join(["pre-commit", "run", *precommit_options, hook])
        c.run(cmd)


@task
def lint(c, all_files=False):
    # type: (Context, bool) -> None
    precommit_options = []

    if all_files:
        precommit_options.append("--all-files")

    hooks = [
        "check-added-large-files",
        "check-merge-conflict",
        "debug-statements",
        "detect-private-key",
        "name-tests-test",
        "flake8",
        "mypy",
        "vulture",
        "bandit",
    ]
    for hook in hooks:
        cmd = " ".join(["pre-commit", "run", *precommit_options, hook])
        c.run(cmd)


@task
def tests(c, quiet=False):
    # type: (Context, bool) -> None
    pytest_options: list[str] = []

    if quiet:
        pytest_options.append("-q")

    cmd = " ".join(
        [
            "coverage",
            "run",
            "-m",
            "pytest",
            *pytest_options,
        ],
    )
    c.run(cmd)


@task
def coverage(c):
    # type: (Context) -> None
    c.run("coverage report")
