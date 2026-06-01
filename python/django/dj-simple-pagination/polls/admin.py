from django.contrib import admin
from django.core.paginator import Paginator
from django.db import OperationalError, connection, transaction
from django.utils.functional import cached_property

from .models import Choice, Question


class DumbPaginator(Paginator):
    @cached_property
    def count(self):
        return 9999999999

    def get_elided_page_range(self, *args, **kwargs):
        kwargs.update({"on_each_side": 4, "on_ends": 0})
        yield from super().get_elided_page_range(*args, **kwargs)


# postgres only
class TimeLimitedPaginator(Paginator):
    @cached_property
    def count(self):
        with transaction.atomic(), connection.cursor() as cursor:
            cursor.execute("SET LOCAL statement_timeout TO 200;")
            try:
                return super().count
            except OperationalError:
                return 9999999999


class ChoiceInline(admin.TabularInline):
    model = Choice
    extra = 0


@admin.register(Question)
class QuestionAdmin(admin.ModelAdmin):
    fieldsets = [
        (None, {"fields": ["text"]}),
        (
            "Date information",
            {"fields": ["published_at"], "classes": "collapse"},
        ),
    ]
    inlines = [ChoiceInline]
    list_display = ("text", "published_at", "was_published_recently")
    list_filter = ["published_at"]
    search_fields = ["text"]
    list_per_page = 4
    show_full_result_count = False
    paginator = DumbPaginator
