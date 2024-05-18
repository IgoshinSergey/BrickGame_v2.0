#include "tetris_loop.h"

void game_tetris(void) {
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_WHITE);
  init_pair(2, COLOR_WHITE, COLOR_WHITE);

  WINDOW *field = newwin(22, 22, 0, 0);
  WINDOW *player = newwin(12, 18, 0, 24);

  initAllInfo();
  while (*getState() != End) {
    int c = getch();
    UserAction_t user_act = getAction(c);
    bool hold = (user_act == Down) ? true : false;
    userInput(user_act, hold);

    GameInfo_t display = updateCurrentState();
    showGame(field, player, display);
  }
  destroyGame();
  delwin(field);
  delwin(player);
}

void showGame(WINDOW *field, WINDOW *player, GameInfo_t game) {
  showField(field, game);
  showNext(player, game);
  showInfo(player, game);
}

void showField(WINDOW *field, GameInfo_t game) {
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
}

void showNext(WINDOW *player, GameInfo_t game) {
  werase(player);
  box(player, 0, 0);
  int **next = game.next;
  if (next) {
    int len = getAllInfo()->next->length;
    for (int i = 0; i < len; i++) {
      for (int j = 0; j < len; j++) {
        if (next[i][j]) {
          wattron(player, COLOR_PAIR(1));
          mvwaddch(player, i + 3, j * 2 + 5, ' ');
          mvwaddch(player, i + 3, j * 2 + 6, ' ');
          wattroff(player, COLOR_PAIR(1));
        }
      }
    }
  }
}

void showInfo(WINDOW *player, GameInfo_t game) {
  mvwprintw(player, 1, 1, "NEXT FIGURE");
  mvwprintw(player, 6, 1, "SCORE %d", game.score);
  mvwprintw(player, 7, 1, "HIGH SCORE %d", game.high_score);
  mvwprintw(player, 8, 1, "LEVEL %d", game.level);
  mvwprintw(player, 9, 1, "SPEED %d", game.speed);
  if (game.pause) mvwprintw(player, 10, 1, "PAUSE");
  wrefresh(player);
}

UserAction_t getAction(int user_input) {
  StateTetris_t *state = getState();
  UserAction_t action = -1;
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
  if ((*state == Spawn || *state == Shifting) && action >= Left &&
      action <= Action) {
    ungetch(user_input);
  }
  return action;
}
