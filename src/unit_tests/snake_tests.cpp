#include "testing.h"

TEST(state_test, test_1) {
  s21::SnakeGame model{};
  s21::Controller controller{&model};
  EXPECT_EQ(model.state, s21::StartGame);
  controller.userInput(Start, false);
  controller.updateCurrentState();
  EXPECT_EQ(model.state, s21::Moving);
  controller.userInput(Pause, false);
  EXPECT_EQ(model.state, s21::Moving);
  controller.updateCurrentState();
}

TEST(state_test, test_2) {
  s21::SnakeGame model{};
  s21::Controller controller{&model};
  EXPECT_EQ(model.state, s21::StartGame);
  controller.userInput(Start, false);
  controller.updateCurrentState();
  controller.userInput(Left, false);
  for (int i{}; i < 6; ++i) model.moveSnake();
  controller.updateCurrentState();
  EXPECT_EQ(model.state, s21::StartGame);
}

TEST(state_test, test_3) {
  s21::SnakeGame model{};
  s21::Controller controller{&model};
  EXPECT_EQ(model.state, s21::StartGame);
  controller.userInput(Start, false);
  controller.updateCurrentState();
  controller.userInput(Left, false);
  model.moveSnake();
  controller.userInput(Up, false);
  model.moveSnake();
  controller.userInput(Right, false);
  model.moveSnake();
  controller.updateCurrentState();
  EXPECT_EQ(model.state, s21::StartGame);
}

TEST(state_test, test_4) {
  s21::SnakeGame model{};
  s21::Controller controller{&model};
  EXPECT_EQ(model.state, s21::StartGame);
  controller.userInput(Start, false);
  controller.updateCurrentState();
  controller.userInput(Action, true);
  EXPECT_EQ(model.state, s21::Moving);
}

TEST(state_test, test_5) {
  s21::SnakeGame model{};
  s21::Controller controller{&model};
  EXPECT_EQ(model.state, s21::StartGame);
  controller.userInput(Start, false);
  controller.updateCurrentState();
  controller.userInput(Terminate, false);
  controller.updateCurrentState();
  EXPECT_EQ(model.state, s21::End);
}

TEST(state_test, test_6) {
  s21::SnakeGame model{};
  s21::Controller controller{&model};
  EXPECT_EQ(model.state, s21::StartGame);
  controller.userInput(Start, false);
  controller.updateCurrentState();
  controller.userInput(Down, false);
  controller.updateCurrentState();
  EXPECT_EQ(model.state, s21::Moving);
}

TEST(state_test, test_7) {
  s21::SnakeGame model{};
  s21::Controller controller{&model};
  EXPECT_EQ(model.state, s21::StartGame);
  controller.userInput(Start, false);
  model.apple.x = 5;
  model.apple.y = 12;
  model.moveSnake();
  EXPECT_EQ(model.state, s21::Spawn);
  controller.updateCurrentState();
  EXPECT_EQ(model.state, s21::Moving);
}

TEST(state_test, test_8) {
  s21::SnakeGame model{};
  s21::Controller controller{&model};
  EXPECT_EQ(model.state, s21::StartGame);
  controller.userInput(Start, false);
  controller.updateCurrentState();
  usleep(1000000);
  controller.updateCurrentState();
  EXPECT_EQ(model.state, s21::Shifting);
  controller.updateCurrentState();
  EXPECT_EQ(model.state, s21::Moving);
}

TEST(info_test, test_1) {
  s21::SnakeGame model{};
  s21::Controller controller{&model};
  EXPECT_EQ(model.state, s21::StartGame);
  EXPECT_EQ(model.info.level, 0);
  controller.userInput(Start, false);
  model.info.score = 4;
  model.apple.x = 5;
  model.apple.y = 12;
  model.moveSnake();
  EXPECT_EQ(model.info.level, 1);
  EXPECT_EQ(model.info.score, 5);
  controller.updateCurrentState();
  EXPECT_EQ(model.state, s21::Moving);
}

TEST(info_test, test_2) {
  s21::SnakeGame model{};
  s21::Controller controller{&model};
  EXPECT_EQ(model.state, s21::StartGame);
  EXPECT_EQ(model.info.level, 0);
  controller.userInput(Start, false);
  model.info.level = 10;
  model.info.score = 54;
  model.apple.x = 5;
  model.apple.y = 12;
  model.moveSnake();
  EXPECT_EQ(model.info.level, 10);
  EXPECT_EQ(model.info.score, 55);
  controller.updateCurrentState();
  EXPECT_EQ(model.state, s21::Moving);
}

TEST(info_test, test_3) {
  s21::SnakeGame model{};
  s21::Controller controller{&model};
  EXPECT_EQ(model.state, s21::StartGame);
  EXPECT_EQ(model.info.level, 0);
  controller.userInput(Start, false);
  model.apple.x = 5;
  model.apple.y = 12;
  model.moveSnake();
  EXPECT_EQ(model.info.level, 0);
  EXPECT_EQ(model.info.score, 1);
  controller.updateCurrentState();
  EXPECT_EQ(model.state, s21::Moving);
}

TEST(info_test, test_4) {
  s21::SnakeGame model{};
  s21::Controller controller{&model};
  EXPECT_EQ(model.state, s21::StartGame);
  EXPECT_EQ(model.info.level, 0);
  controller.userInput(Start, false);
  controller.userInput(Left, false);
  model.apple.x = 4;
  model.apple.y = 11;
  model.moveSnake();
  EXPECT_EQ(model.info.level, 0);
  EXPECT_EQ(model.info.score, 1);
  controller.updateCurrentState();
  EXPECT_EQ(model.state, s21::Moving);
}

TEST(info_test, test_5) {
  s21::SnakeGame model{};
  s21::Controller controller{&model};
  EXPECT_EQ(model.state, s21::StartGame);
  EXPECT_EQ(model.info.level, 0);
  controller.userInput(Start, false);
  controller.userInput(Right, false);
  model.apple.x = 6;
  model.apple.y = 11;
  model.moveSnake();
  EXPECT_EQ(model.info.level, 0);
  EXPECT_EQ(model.info.score, 1);
  controller.updateCurrentState();
  EXPECT_EQ(model.state, s21::Moving);
}

TEST(info_test, test_6) {
  s21::SnakeGame model{};
  s21::Controller controller{&model};
  EXPECT_EQ(model.state, s21::StartGame);
  EXPECT_EQ(model.info.level, 0);
  controller.userInput(Start, false);
  model.apple.x = 6;
  model.apple.y = 10;
  controller.userInput(Right, false);
  model.moveSnake();
  controller.userInput(Up, false);
  model.moveSnake();
  EXPECT_EQ(model.info.level, 0);
  EXPECT_EQ(model.info.score, 1);
  controller.updateCurrentState();
  EXPECT_EQ(model.state, s21::Moving);
}