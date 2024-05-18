#ifndef C7_BRICKGAME_V_1_0_SNAKE_LOOP_H_
#define C7_BRICKGAME_V_1_0_SNAKE_LOOP_H_

#include <ncurses.h>

#include "../../brick_game/snake/controller/controller.h"

namespace s21 {

class SnakeNcurses {
 private:
  Controller *controller;

 public:
  SnakeNcurses(Controller *controller);
  ~SnakeNcurses();

  void game_snake(void);
  UserAction_t getAction(int user_input);

  void showGame(WINDOW *field, WINDOW *player, GameInfo_t game);
  void showField(WINDOW *field, GameInfo_t game);
  void showInfo(WINDOW *player, GameInfo_t game);
};

}  // namespace s21

#endif  // C7_BRICKGAME_V_1_0_SNAKE_LOOP_H_
