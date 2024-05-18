#ifndef C7_BRICKGAME_V_1_0_TETRIS_LOOP_H_
#define C7_BRICKGAME_V_1_0_TETRIS_LOOP_H_

#include <ncurses.h>

#include "../../brick_game/tetris/inc/tetris.h"

void game_tetris(void);
UserAction_t getAction(int user_input);

void showGame(WINDOW *field, WINDOW *player, GameInfo_t game);
void showField(WINDOW *field, GameInfo_t game);
void showNext(WINDOW *player, GameInfo_t game);
void showInfo(WINDOW *player, GameInfo_t game);

#endif  // C7_BRICKGAME_V_1_0_TETRIS_LOOP_H_
