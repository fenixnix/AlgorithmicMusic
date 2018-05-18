#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  NMidiAuther::SelfTest();
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
