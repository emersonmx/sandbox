from invoke import Context, task


def get_files(c: Context, file: str, exclude: str = "") -> str:
    cmd = f"git ls-files '{file}'"
    if exclude:
        cmd = f"{cmd} | grep -v '{exclude}'"

    return " ".join(c.run(cmd, hide=True).stdout.strip().splitlines())


@task
def run(c):
    # type: (Context) -> None
    c.run("python manage.py runserver 0.0.0.0:8000")


@task
def shell(c):
    # type: (Context) -> None
    c.run("python manage.py shell")


@task(aliases=("fmt",))
def format(c):
    # type: (Context) -> None
    all_files = get_files(c, ".")
    py_files = get_files(c, "*.py")
    ipy_files = get_files(c, "*.ipy")

    c.run(f"trailing-whitespace-fixer {all_files}")
    c.run(f"end-of-file-fixer {all_files}")
    c.run(f"pyupgrade --py310-plus {py_files}")
    c.run(f"add-trailing-comma {py_files}")
    c.run(f"yesqa {py_files}")
    c.run(f"isort --filter-files {py_files} {ipy_files}".strip())
    c.run(f"black {py_files} {ipy_files}".strip())


@task
def lint(c):
    # type: (Context) -> None
    all_files = get_files(c, ".")
    source_files = get_files(c, "*.py", "^tests/")
    py_files = get_files(c, "*.py")
    # ipy_files = get_files(c, "*.ipy")
    py_test_files = get_files(c, "tests/*.py")

    c.run(f"check-ast {py_files}")
    c.run(f"debug-statement-hook {py_files}")
    c.run(f"name-tests-test {py_test_files}")
    c.run(f"check-merge-conflict {all_files}")
    c.run(f"check-added-large-files {all_files}")
    c.run(f"detect-private-key {all_files}")
    c.run(f"flake8 {py_files}")
    # c.run(f"mypy --strict {py_files} {ipy_files}".strip())
    c.run(f"vulture {py_files}")
    c.run(f"bandit -r {source_files}")


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
