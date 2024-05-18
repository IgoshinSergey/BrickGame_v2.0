#include "snakewidget.h"

SnakeWidget::SnakeWidget(QWidget *parent)
    : QWidget{parent}, model{}, controller{&model} {
  setFixedSize(470, 605);
  setFocusPolicy(Qt::StrongFocus);
  setWindowTitle("Snake");
  timer = new QTimer;
  connect(timer, &QTimer::timeout, this, &SnakeWidget::update_paint);
  timer->start(30);
}

SnakeWidget::~SnakeWidget() { delete timer; }

void SnakeWidget::paintEvent(QPaintEvent *e) {
  Q_UNUSED(e)
  QPainter p(this);
  p.drawRect(0, 0, 300, 600);
  controller.updateCurrentState();
  GameInfo_t inf = controller.model->info;
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
  QFont font;
  font.setPointSize(14);
  p.setFont(font);
  p.drawText(305, 25, "Next: empty");
  std::string s = "Score: " + std::to_string(inf.score);
  p.drawText(305, 55, s.data());
  std::string hs = "High score: " + std::to_string(inf.high_score);
  p.drawText(305, 85, hs.data());
  std::string l = "Level: " + std::to_string(inf.level);
  p.drawText(305, 115, l.data());
  std::string sp = "Speed: " + std::to_string(inf.speed);
  p.drawText(305, 145, sp.data());
  if (inf.pause) {
    p.drawText(305, 175, "Pause");
  }
}

void SnakeWidget::keyPressEvent(QKeyEvent *e) {
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
  bool hold = (act == Action) ? true : false;
  controller.userInput(act, hold);
  update_paint();
  if (act == Terminate) {
    QWidget::close();
  }
}

void SnakeWidget::update_paint() {
  // controller.updateCurrentState();
  repaint();
}
