/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow {
 public:
  QWidget *centralwidget;
  QWidget *gridLayoutWidget;
  QGridLayout *gridLayout;
  QPushButton *snakeButton;
  QPushButton *tetrisButton;
  QSpacerItem *horizontalSpacer;
  QLabel *label;

  void setupUi(QMainWindow *MainWindow) {
    if (MainWindow->objectName().isEmpty())
      MainWindow->setObjectName("MainWindow");
    MainWindow->resize(300, 243);
    MainWindow->setMinimumSize(QSize(300, 0));
    centralwidget = new QWidget(MainWindow);
    centralwidget->setObjectName("centralwidget");
    gridLayoutWidget = new QWidget(centralwidget);
    gridLayoutWidget->setObjectName("gridLayoutWidget");
    gridLayoutWidget->setGeometry(QRect(10, 130, 281, 51));
    gridLayout = new QGridLayout(gridLayoutWidget);
    gridLayout->setObjectName("gridLayout");
    gridLayout->setContentsMargins(0, 0, 0, 0);
    snakeButton = new QPushButton(gridLayoutWidget);
    snakeButton->setObjectName("snakeButton");
    QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum,
                           QSizePolicy::Policy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(snakeButton->sizePolicy().hasHeightForWidth());
    snakeButton->setSizePolicy(sizePolicy);

    gridLayout->addWidget(snakeButton, 0, 2, 1, 1);

    tetrisButton = new QPushButton(gridLayoutWidget);
    tetrisButton->setObjectName("tetrisButton");
    sizePolicy.setHeightForWidth(
        tetrisButton->sizePolicy().hasHeightForWidth());
    tetrisButton->setSizePolicy(sizePolicy);

    gridLayout->addWidget(tetrisButton, 0, 0, 1, 1);

    horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Policy::Fixed,
                                       QSizePolicy::Policy::Minimum);

    gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

    label = new QLabel(centralwidget);
    label->setObjectName("label");
    label->setGeometry(QRect(40, 50, 216, 50));
    QFont font;
    font.setFamilies({QString::fromUtf8("Noto Mono")});
    font.setPointSize(18);
    font.setBold(true);
    font.setItalic(false);
    font.setUnderline(false);
    font.setStrikeOut(false);
    label->setFont(font);
    label->setTextFormat(Qt::PlainText);
    MainWindow->setCentralWidget(centralwidget);

    retranslateUi(MainWindow);

    QMetaObject::connectSlotsByName(MainWindow);
  }  // setupUi

  void retranslateUi(QMainWindow *MainWindow) {
    MainWindow->setWindowTitle(
        QCoreApplication::translate("MainWindow", "Brick Game v2.0", nullptr));
    snakeButton->setText(
        QCoreApplication::translate("MainWindow", "SNAKE", nullptr));
    tetrisButton->setText(
        QCoreApplication::translate("MainWindow", "TETRIS", nullptr));
    label->setText(
        QCoreApplication::translate("MainWindow", "Brick Game v2.0", nullptr));
  }  // retranslateUi
};

namespace Ui {
class MainWindow : public Ui_MainWindow {};
}  // namespace Ui

QT_END_NAMESPACE

#endif  // UI_MAINWINDOW_H
