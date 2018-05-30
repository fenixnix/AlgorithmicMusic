#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include "ACM/algomuse.h"
#include "formkeyboard.h"
#include "dialogmusicinstrumenttest.h"
#include "dialogsfx.h"

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

  void on_actionKeyboard_triggered();

  void on_actionTone_Tester_triggered();

  void on_actionSfx_triggered();

  void on_actionTest_2_triggered();

private:
  Ui::MainWindow *ui;
  AlgoMuse muse;
  FormKeyboard keyboard;
  DialogMusicInstrumentTest toneTester;
  DialogSFX sfx;
};

#endif // MAINWINDOW_H
