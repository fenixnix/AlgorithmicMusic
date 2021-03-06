#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_btnPlay3_clicked()
{
  muse.PlayWindChime();
}

void MainWindow::on_btnMozart_clicked()
{
  muse.PlayMozartDiceGame();
}

void MainWindow::on_actionbeginning_triggered()
{
  muse.PlayMotivic();
}

void MainWindow::on_actionKeyboard_triggered()
{
  keyboard.show();
}

void MainWindow::on_actionTone_Tester_triggered()
{
  toneTester.show();
}

void MainWindow::on_actionSfx_triggered()
{
  sfx.show();
}

void MainWindow::on_actionTest_2_triggered()
{
  QString mode = QInputDialog::getText(this,"Mode","Mode");
  muse.TonicTest(mode.toStdString());
}
