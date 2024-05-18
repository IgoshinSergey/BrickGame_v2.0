#ifndef TETRISWIDGET_H
#define TETRISWIDGET_H

#ifdef __cplusplus
extern "C" {
#endif
#include "../../brick_game/tetris/inc/tetris.h"
#ifdef __cplusplus
}
#endif

#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QWidget>

#include "../../brick_game/common/common.h"

class TetrisWidget : public QWidget {
  Q_OBJECT
 public:
  explicit TetrisWidget(QWidget *parent = nullptr);
  ~TetrisWidget();

 protected:
  void paintEvent(QPaintEvent *e) override;
  void keyPressEvent(QKeyEvent *e) override;

 private:
  QTimer *timer;

 private slots:
  void update_paint(void);
};

#endif  // TETRISWIDGET_H
