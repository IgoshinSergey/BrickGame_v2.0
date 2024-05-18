#ifndef CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_COMMON_
#define CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_COMMON_

typedef enum UserAction_t {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

#endif // CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_COMMON_
