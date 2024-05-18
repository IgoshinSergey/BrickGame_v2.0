#include "brick_game_cli.h"

int main(void) {
  init_ncurses();
  int key = getch();
  while (key != 27) {
    erase();
    mvprintw(1, 7, "BrickGame v2.0");
    mvprintw(3, 1, "Tetris - Enter \'T\' or \'t\' for start");
    mvprintw(4, 1, "Snake  - Enter \'S\' or \'s\' for start");
    mvprintw(5, 1, "Exit   - Enter \'Esc\'");
    if (key == 't' || key == 'T') {
      clear();
      game_tetris();
    } else if (key == 's' || key == 'S') {
      clear();
      s21::SnakeGame model{};
      s21::Controller controller{&model};
      s21::SnakeNcurses view{&controller};
      view.game_snake();
    }
    key = getch();
  }
  end_ncurses();
  return 0;
}

void init_ncurses(void) {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, true);
  timeout(50);
  curs_set(0);
}

void end_ncurses(void) { endwin(); };
