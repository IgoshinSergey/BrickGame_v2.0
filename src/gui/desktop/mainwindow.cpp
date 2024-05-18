#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      s(new SnakeWidget),
      t(new TetrisWidget) {
  ui->setupUi(this);
  setFixedSize(300, 200);
}

MainWindow::~MainWindow() {
  delete s;
  delete ui;
}

void MainWindow::on_tetrisButton_clicked() {
  hide();
  t->show();
}

void MainWindow::on_snakeButton_clicked() {
  hide();
  s->show();
}
