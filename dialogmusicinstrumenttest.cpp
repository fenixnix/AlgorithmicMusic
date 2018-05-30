#include "dialogmusicinstrumenttest.h"
#include "ui_dialogmusicinstrumenttest.h"
#include <QDebug>

DialogMusicInstrumentTest::DialogMusicInstrumentTest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogMusicInstrumentTest)
{
    ui->setupUi(this);
    music.contour.TrapezoidaEnvelope();
}

DialogMusicInstrumentTest::~DialogMusicInstrumentTest()
{
  delete ui;
}

void DialogMusicInstrumentTest::Refresh()
{
//  music.contour.TrapezoidaEnvelope((float)ui->verticalSliderT1->value()/100.0f,
//                                   (float)ui->verticalSliderT2->value()/100.0f,
//                                   (float)ui->verticalSliderT3->value()/100.0f,
//                                   ui->verticalSliderMaxVol->value());
  qDebug()<<ui->comboBoxWavType->currentText()<<"Freq:"<<ui->spinBoxFreq->value();
  music.chipTune.generateData(ui->comboBoxWavType->currentText(),ui->horizontalSliderFreq->value(),music.contour);
  music.PlayChip();

}

void DialogMusicInstrumentTest::on_pushButtonPlay_clicked()
{
    Refresh();
}
