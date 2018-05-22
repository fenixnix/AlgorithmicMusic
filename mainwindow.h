#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ACM/algomuse.h"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void on_btnPlay3_clicked();

  void on_btnMozart_clicked();

  void on_actionbeginning_triggered();

  void on_actionTest_triggered();

private:
  Ui::MainWindow *ui;
  AlgoMuse muse;
};

#endif // MAINWINDOW_H
