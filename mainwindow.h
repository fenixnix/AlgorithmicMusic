#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ACM/algomuse.h"
#include "ACM/nmidiauther.h"

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

private:
  Ui::MainWindow *ui;
  AlgoMuse muse;
};

#endif // MAINWINDOW_H
