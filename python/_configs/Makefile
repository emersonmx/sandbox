.PHONY: setup-dev shell format lint tests clean

ifndef VERBOSE
MAKEFLAGS += --silent
endif


setup-dev:
	@poetry install
	@poetry run pre-commit install

shell:
	@poetry shell

format:
	@isort .
	@black .

lint:
	@flake8 .
	@mypy .

tests:
	@pytest .

clean:
	@find . -type f -name "*.py[co]" -delete
	@find . -type d -name "__pycache__" -delete
	@find . -depth -type d -name ".mypy_cache" -exec rm -r "{}" +
	@find . -depth -type d -name ".pytest_cache" -exec rm -r "{}" +
