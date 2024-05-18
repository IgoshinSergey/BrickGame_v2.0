#ifndef CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_SNAKE_CONTROLLER_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_SNAKE_CONTROLLER_H_

#include "../../common/common.h"
#include "../model/model.h"

namespace s21 {

class Controller {
 public:
  SnakeGame *model;

  Controller(SnakeGame *model);
  ~Controller();

  void userInput(UserAction_t action, bool hold);
  GameInfo_t updateCurrentState();
};

}  // namespace s21

#endif  // CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_SNAKE_CONTROLLER_H_