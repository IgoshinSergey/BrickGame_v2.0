#ifndef CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_SNAKE_MODEL_HPP_
#define CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_SNAKE_MODEL_HPP_

#include <time.h>

#include <algorithm>
#include <random>

#include "../../common/common.h"

namespace s21 {

#define WIDTH 10
#define HEIGTH 20

typedef enum StateSnake_t {
  StartGame,
  Spawn,
  Moving,
  Shifting,
  End
} StateSnake_t;

typedef enum Direction {
  UpDirection,
  DownDirection,
  RightDirection,
  LeftDirection
} Direction;

class Point {
 public:
  int x;
  int y;
  Point();
  Point(int x, int y);
  Point randomPoint(std::vector<Point>& snake);
  Point(const Point& other);
  Point& operator=(const Point& other);
};

class SnakeGame {
 public:  // пока что поля публичные для тестов
  GameInfo_t info;
  StateSnake_t state;
  std::vector<Point> snake;
  Direction snake_direction;
  Direction next_direction;
  Point apple;
  bool start;
  struct timespec last_move_time;

  SnakeGame();
  ~SnakeGame();

  int getSnakeScore(void);
  void setSnakeScore(int high_score);
  void initStartInfo(void);
  void initSnakeVector(void);
  void randomApple(void);
  void clearField(void);
  void connectSnakeAndField(void);
  void connectAppleAndField(void);
  GameInfo_t connectFiguresAndField(void);
  bool checkCollision(void);
  void updateInfo(void);
  void moveSnake(void);
};
}  // namespace s21

#endif  // CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_SNAKE_MODEL_HPP_