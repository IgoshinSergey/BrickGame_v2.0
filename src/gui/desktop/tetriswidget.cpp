#include "tetriswidget.h"

TetrisWidget::TetrisWidget(QWidget *parent) : QWidget{parent} {
  setFixedSize(470, 605);
  setFocusPolicy(Qt::StrongFocus);
  setWindowTitle("Tetris");
  timer = new QTimer;
  initAllInfo();
  connect(timer, &QTimer::timeout, this, &TetrisWidget::update_paint);
  timer->start(50);
}

TetrisWidget::~TetrisWidget() { delete timer; }

void TetrisWidget::paintEvent(QPaintEvent *e) {
  Q_UNUSED(e)
  QPainter p(this);
  p.drawRect(0, 0, 300, 600);
  GameInfo_t inf = updateCurrentState();
  ;
  for (int i{}; i < 20; ++i) {
    for (int j{}; j < 10; ++j) {
      if (inf.field[i][j]) {
        p.setBrush(Qt::black);
      } else {
        p.setBrush(Qt::white);
      }
      p.drawRect(30 * j, 30 * i, 30, 30);
    }
  }
  if (inf.next) {
    int len = getAllInfo()->next->length;
    for (int i{}; i < len; ++i) {
      for (int j{}; j < len; ++j) {
        if (inf.next[i][j]) {
          p.setBrush(Qt::black);
        } else {
          p.setBrush(Qt::white);
        }
        p.drawRect(30 * j + 310, 30 * i + 30, 30, 30);
      }
    }
  }
  QFont font;
  font.setPointSize(14);
  p.setFont(font);
  p.drawText(305, 25, "Next:");
  std::string s = "Score: " + std::to_string(inf.score);
  p.drawText(305, 205, s.data());
  std::string hs = "High score: " + std::to_string(inf.high_score);
  p.drawText(305, 235, hs.data());
  std::string l = "Level: " + std::to_string(inf.level);
  p.drawText(305, 265, l.data());
  std::string sp = "Speed: " + std::to_string(inf.speed);
  p.drawText(305, 295, sp.data());
  if (inf.pause) {
    p.drawText(305, 325, "Pause");
  }
}

void TetrisWidget::keyPressEvent(QKeyEvent *e) {
  UserAction_t act = Start;
  if (e->key() == Qt::Key_Down) {
    act = Down;
  } else if (e->key() == Qt::Key_Up) {
    act = Up;
  } else if (e->key() == Qt::Key_Left) {
    act = Left;
  } else if (e->key() == Qt::Key_Right) {
    act = Right;
  } else if (e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return) {
    act = Start;
  } else if (e->key() == Qt::Key_Escape) {
    act = Terminate;
  } else if (e->key() == 'p' || e->key() == 'P') {
    act = Pause;
  } else if (e->key() == 'z' || e->key() == 'Z') {
    act = Action;
  }
  bool hold = (act == Down) ? true : false;
  userInput(act, hold);
  update_paint();
  if (act == Terminate) {
    QWidget::close();
  }
}

void TetrisWidget::update_paint(void) { repaint(); }
