#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "snakewidget.h"
#include "tetriswidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_tetrisButton_clicked();

  void on_snakeButton_clicked();

 private:
  Ui::MainWindow *ui;
  SnakeWidget *s;
  TetrisWidget *t;
};
#endif  // MAINWINDOW_H
