#ifndef GAME_H
#define GAME_H

typedef enum { GAME_CONTINUE, GAME_SUCCESS, GAME_FAILURE } GameResult;

GameResult game_run(int argc, char *argv[]);

#endif // GAME_H
