ifndef VERBOSE
MAKEFLAGS += --silent
endif


.PHONY: setup
setup:
	@poetry install
	@poetry run pre-commit install

.PHONY: shell
shell:
	@poetry shell

.PHONY: format
format:
	@poetry run isort .
	@poetry run black .

.PHONY: lint
lint:
	@poetry run flake8 .
	@poetry run mypy .

.PHONY: tests
tests:
	@poetru run pytest .

.PHONY: clean
clean:
	@find . -type f -name "*.py[co]" -delete
	@find . -type d -name "__pycache__" -delete
	@find . -depth -type d -name ".mypy_cache" -exec rm -r "{}" +
	@find . -depth -type d -name ".pytest_cache" -exec rm -r "{}" +
