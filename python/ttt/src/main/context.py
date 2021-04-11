import pygame
import pygame.surface

from ttt.domain.models import Match

match: Match
running = True
paused = False
can_pause = True
can_mark_position = True
match_is_over = False
screen: pygame.surface.Surface
