#include "snake_loop.h"

namespace s21 {

SnakeNcurses::SnakeNcurses(Controller *c) : controller{c} {};
SnakeNcurses::~SnakeNcurses(){};

void SnakeNcurses::game_snake(void) {
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_WHITE);
  init_pair(2, COLOR_WHITE, COLOR_WHITE);

  WINDOW *field = newwin(22, 22, 0, 0);
  WINDOW *player = newwin(12, 18, 0, 24);

  while (controller->model->state != s21::End) {
    timeout(50);
    int c = getch();
    bool hold = false;
    UserAction_t user_act = getAction(c);
    if (user_act == Action) hold = true;
    controller->userInput(user_act, hold);
    GameInfo_t display = controller->updateCurrentState();
    showField(field, display);
    showInfo(player, display);
  }

  delwin(field);
  delwin(player);
};
UserAction_t SnakeNcurses::getAction(int user_input) {
  UserAction_t action;
  switch (user_input) {
    case KEY_UP:
      action = Up;
      break;
    case KEY_LEFT:
      action = Left;
      break;
    case KEY_RIGHT:
      action = Right;
      break;
    case KEY_DOWN:
      action = Down;
      break;
    case 'z':
    case 'Z':
      action = Action;
      break;
    case '\n':
      action = Start;
      break;
    case 27:
      action = Terminate;
      break;
    case 'p':
    case 'P':
      action = Pause;
      break;
    default:
      break;
  }
  return action;
};

void SnakeNcurses::showGame(WINDOW *field, WINDOW *player, GameInfo_t game) {
  showField(field, game);
  showInfo(player, game);
};

void SnakeNcurses::showField(WINDOW *field, GameInfo_t game) {
  werase(field);
  box(field, 0, 0);
  int **coordinates = game.field;
  if (coordinates) {
    for (int i = 0; i < 20; i++) {
      for (int j = 0; j < 10; j++) {
        if (coordinates[i][j]) {
          wattron(field, COLOR_PAIR(1));
          mvwaddch(field, i + 1, j * 2 + 1, ' ');
          mvwaddch(field, i + 1, j * 2 + 2, ' ');
          wattroff(field, COLOR_PAIR(1));
        }
      }
    }
  }
  wrefresh(field);
};

void SnakeNcurses::showInfo(WINDOW *info, GameInfo_t game) {
  werase(info);
  box(info, 0, 0);
  mvwprintw(info, 1, 1, "NEXT");
  mvwprintw(info, 6, 1, "SCORE %d", game.score);
  mvwprintw(info, 7, 1, "HIGH SCORE %d", game.high_score);
  mvwprintw(info, 8, 1, "LEVEL %d", game.level);
  mvwprintw(info, 9, 1, "SPEED %d", game.speed);
  if (game.pause) mvwprintw(info, 10, 1, "PAUSE");
  wrefresh(info);
};

}  // namespace s21
