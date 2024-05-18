#ifndef SNAKEWIDGET_H
#define SNAKEWIDGET_H

#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QWidget>

#include "../../brick_game/common/common.h"
#include "../../brick_game/snake/controller/controller.h"

class SnakeWidget : public QWidget {
  Q_OBJECT
 public:
  explicit SnakeWidget(QWidget *parent = nullptr);
  ~SnakeWidget();

 protected:
  void paintEvent(QPaintEvent *e) override;
  void keyPressEvent(QKeyEvent *e) override;

 private:
  s21::SnakeGame model;
  s21::Controller controller;
  QTimer *timer;

 private slots:
  void update_paint(void);
};

#endif  // SNAKEWIDGET_H
