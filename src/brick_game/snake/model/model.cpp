#include "model.h"

namespace s21 {

// class Point
Point::Point() : x{}, y{} {}
Point::Point(int x, int y) : x{x}, y{y} {}
Point::Point(const Point &other) : x{other.x}, y{other.y} {}
Point Point::randomPoint(std::vector<Point> &snake) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> x_dis(0, WIDTH - 1);
  std::uniform_int_distribution<> y_dis(0, HEIGTH - 1);
  Point res;
  do {
    res.x = x_dis(gen);
    res.y = y_dis(gen);
  } while (std::any_of(snake.begin(), snake.end(),
                       [&](Point p) { return p.x == res.x && p.y == res.y; }));
  return res;
}
Point &Point::operator=(const Point &other) {
  if (this != &other) {
    x = other.x;
    y = other.y;
  }
  return *this;
}

// class SnakeGame
SnakeGame::SnakeGame() {
  info.field = new int *[HEIGTH];
  for (int i{}; i < HEIGTH; ++i) {
    info.field[i] = new int[WIDTH]{};
  }
  state = StartGame;
  snake_direction = DownDirection;
  next_direction = DownDirection;
  info.score = info.level = 0;
  info.high_score = getSnakeScore();
  info.pause = start = false;
  info.speed = 600;
  initSnakeVector();
  clock_gettime(CLOCK_REALTIME, &last_move_time);
}

SnakeGame::~SnakeGame() {
  for (int i{}; i < HEIGTH; ++i) {
    delete[] info.field[i];
  }
  delete[] info.field;
}

int SnakeGame::getSnakeScore(void) {
  int high_score = 0;
  FILE *f = fopen("./snake_score.txt", "r");
  if (f != NULL) {
    int res = fscanf(f, "%d", &high_score);
    if (res) fclose(f);
  }
  return high_score;
}

void SnakeGame::setSnakeScore(int high_score) {
  FILE *f = fopen("./snake_score.txt", "w");
  if (f != NULL) {
    fprintf(f, "%d", high_score);
    fclose(f);
  }
}

void SnakeGame::randomApple() {
  Point tmp = apple.randomPoint(snake);
  apple.x = tmp.x;
  apple.y = tmp.y;
}

void SnakeGame::initStartInfo(void) {
  clearField();
  snake.clear();
  initSnakeVector();
  randomApple();
  snake_direction = DownDirection;
  next_direction = DownDirection;
  connectFiguresAndField();
};

void SnakeGame::initSnakeVector() {
  snake.clear();
  snake.push_back(Point(WIDTH / 2, HEIGTH / 2 + 1));
  snake.push_back(Point(WIDTH / 2, HEIGTH / 2));
  snake.push_back(Point(WIDTH / 2, HEIGTH / 2 - 1));
  snake.push_back(Point(WIDTH / 2, HEIGTH / 2 - 2));
}

void SnakeGame::clearField(void) {
  for (int i{}; i < HEIGTH; ++i) {
    for (int j{}; j < WIDTH; ++j) {
      info.field[i][j] = 0;
    }
  }
}

void SnakeGame::connectSnakeAndField(void) {
  for (auto iter = snake.begin(); iter != snake.end(); ++iter) {
    int x = (*iter).x;
    int y = (*iter).y;
    info.field[y][x] = 1;
  }
}

void SnakeGame::connectAppleAndField(void) { info.field[apple.y][apple.x] = 1; }

GameInfo_t SnakeGame::connectFiguresAndField(void) {
  clearField();
  connectAppleAndField();
  connectSnakeAndField();
  return info;
}

bool isOutsideBorders(int x, int y) {
  bool res = false;
  if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGTH) res = true;
  return res;
}

bool isCollisionWithBody(int x, int y, std::vector<Point> &snake) {
  bool res = false;
  if (std::any_of(++(snake.begin()), snake.end(),
                  [&](Point p) { return p.x == x && p.y == y; })) {
    res = true;
  }
  return res;
}

bool SnakeGame::checkCollision(void) {
  Point tmp = snake.front();
  bool res = false;
  if (isOutsideBorders(tmp.x, tmp.y) ||
      isCollisionWithBody(tmp.x, tmp.y, snake)) {
    res = true;
  }
  return res;
}

void SnakeGame::updateInfo(void) {
  info.score++;
  if (info.high_score < info.score) info.high_score = info.score;
  if (info.level < 10) info.level = info.score / 5;
  info.speed = 600 - 30 * info.level;
};

void SnakeGame::moveSnake(void) {
  if (!info.pause && start) {
    Point tmp{snake.front()};
    switch (next_direction) {
      case UpDirection:
        tmp.y -= 1;
        break;
      case DownDirection:
        tmp.y += 1;
        break;
      case RightDirection:
        tmp.x += 1;
        break;
      case LeftDirection:
        tmp.x -= 1;
        break;
      default:
        break;
    }
    snake.insert(snake.begin(), tmp);
    if (tmp.x == apple.x && tmp.y == apple.y) {
      state = Spawn;
      updateInfo();
    } else if (checkCollision()) {
      clearField();
      snake.clear();
      info.score = info.level = 0;
      info.speed = 600;
      setSnakeScore(info.high_score);
      state = StartGame;
      start = false;
    } else {
      state = Moving;
      snake.pop_back();
    }
    snake_direction = next_direction;
  }
  clock_gettime(CLOCK_REALTIME, &last_move_time);
  connectFiguresAndField();
}

}  // namespace s21
