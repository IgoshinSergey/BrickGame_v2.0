#include "inc/tetris.h"

GameInfo_t updateCurrentState(void) {
  AllInfo_t *info = getAllInfo();
  StateTetris_t *state = getState();
  bool res;
  if (!info->player.pause && info->player.start) {
    struct timespec cur_time = {0};
    double difference = 0;
    switch (*state) {
      case StartGame:
        *state = Spawn;
        break;
      case Spawn:
        spawnFigure(info);
        *state = Moving;
        break;
      case Moving:
        clock_gettime(CLOCK_REALTIME, &cur_time);
        difference =
            (cur_time.tv_sec - info->last_drop_time.tv_sec) * 1000 +
            (cur_time.tv_nsec - info->last_drop_time.tv_nsec) / 1000000;
        if (difference >= info->player.speed) {
          clock_gettime(CLOCK_REALTIME, &info->last_drop_time);
          *state = Shifting;
        }
        break;
      case Shifting:
        res = moveDown(info);
        if (res == false) {
          *state = Attaching;
        } else {
          *state = Moving;
        }
        break;
      case Attaching:
        if (isEndGame(info)) {
          setTetrisScore(info->player.high_score);
          initAllInfo();
          *state = StartGame;
        } else {
          connectionFigure(info);
          updateAllInfo(info);
          *state = Spawn;
        }
        break;
      default:
        break;
    }
  }
  GameInfo_t display = makeGameInfo(info);
  return display;
}

void userInput(UserAction_t action, bool hold) {
  AllInfo_t *info = getAllInfo();
  StateTetris_t *state = getState();
  bool pause = info->player.pause;
  if (!hold) {
    switch (action) {
      case Start:
        if (*state == StartGame) info->player.start = 1;
        break;
      case Pause:
        if (*state != StartGame) info->player.pause = !info->player.pause;
        break;
      case Terminate:
        setTetrisScore(info->player.high_score);
        *state = End;
        break;
      case Left:
        if (*state == Moving && !pause) moveLeft(info);
        break;
      case Right:
        if (*state == Moving && !pause) moveRight(info);
        break;
      case Up:
        break;
      case Down:
        break;
      case Action:
        if (*state == Moving && !pause) rotation(info);
        break;
      default:
        break;
    }
  } else {
    if (*state == Moving && !pause) {
      while (moveDown(info)) {
        moveDown(info);
      }
    }
  }
}
