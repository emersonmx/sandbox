import datetime

from django.contrib import admin
from django.db import models
from django.utils import timezone


class Question(models.Model):
    text = models.CharField(max_length=200)
    published_at = models.DateTimeField("date published")

    def __str__(self):
        return self.text

    @admin.display(
        boolean=True,
        ordering="published_at",
        description="Published recently?",
    )
    def was_published_recently(self):
        return self.published_at >= timezone.now() - datetime.timedelta(days=1)


class Choice(models.Model):
    question = models.ForeignKey(Question, on_delete=models.CASCADE)
    text = models.CharField(max_length=200)
    votes = models.IntegerField(default=0)

    def __str__(self):
        return self.text
