#include "formkeyboard.h"
#include "ui_formkeyboard.h"
#include <QPushButton>
#include <QDebug>
#include <QThread>

FormKeyboard::FormKeyboard(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FormKeyboard)
{
  ui->setupUi(this);
  music.SetMode("China");
  InitKey();
  RefreshModes();
  QObject::connect(&timer,&QTimer::timeout,this,&FormKeyboard::onTimer);
}

FormKeyboard::~FormKeyboard()
{
  delete ui;
}

void FormKeyboard::OnClickKey()
{
  QPushButton* btn = (QPushButton*)sender();
  int v = btn->toolTip().toInt();
  music.Play(v);
}

void FormKeyboard::RefreshModes()
{
  auto modeList = music.music.GetModes();
  for(int i = 0;i<modeList.size();i++){
      ui->comboBoxMode->addItem(QString::fromStdString(modeList[i]));
    }
}

void FormKeyboard::InitKey()
{
  int cnt = music.GetModeNoteCount();
  for(int i = -cnt;i<cnt*2;i++){
      QPushButton* btn = new QPushButton();
      btn->setText(QString::number(i));
      btn->setToolTip(QString::number(i));
      QObject::connect(btn,&QPushButton::pressed,this,&FormKeyboard::OnClickKey);
      ui->horizontalLayout_Keyboard->addWidget(btn);
      btn->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    }
}

void FormKeyboard::on_btnBass_clicked()
{
    Drum.Bass();
}

void FormKeyboard::on_btnSide_clicked()
{
    Drum.SideDrum();
}

void FormKeyboard::on_btnHighHat_clicked()
{
    Drum.HighHat();
}

void FormKeyboard::on_btnTomtom_clicked()
{
    Drum.Tomtom();
}

void FormKeyboard::on_comboBoxMode_currentTextChanged(const QString &arg1)
{
  music.SetMode(arg1);
  index = 0;
  timer.start(150);
}

void FormKeyboard::onTimer()
{
  music.Play(index);
  qDebug()<<"Play"<<index;
  index++;
  if(index>music.GetModeNoteCount()){
      timer.stop();
    }
}
