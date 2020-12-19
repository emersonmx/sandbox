.PHONY: tests

ifndef VERBOSE
MAKEFLAGS += --silent
endif


lint:
	@flake8 .
	@mypy .

format:
	@isort .
	@black .

tests:
	@pytest .

watch-tests:
	@find tests -type f -iname "*.py" | entr make tests

clean:
	@find . -type f -name "*.py[co]" -delete
	@find . -type d -name "__pycache__" -delete
	@find . -depth -type d -name ".mypy_cache" -exec rm -r "{}" +
	@find . -depth -type d -name ".pytest_cache" -exec rm -r "{}" +
