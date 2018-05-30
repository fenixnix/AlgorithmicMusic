#include "dialogsfx.h"
#include "ui_dialogsfx.h"

DialogSFX::DialogSFX(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogSFX)
{
  ui->setupUi(this);
}

DialogSFX::~DialogSFX()
{
  delete ui;
}

Sfx8Bit sfx;
NQWavPlayer player;
vector<float> wavData;

void Play(vector<float> rawData){
    player.ImportData(rawData);
    player.Play();
}

void Play(){
  sfx.SynthSample(wavData);
  Play(wavData);
  NWavWriter::Save("tmp.wav",wavData);
  //QSound::play("tmp.wav");
}

void DialogSFX::on_PickUp_CoinBtn_clicked()
{
  sfx.PickUp_Coin();
  Play();
}

void DialogSFX::on_Laser_ShootBtn_clicked()
{
  sfx.Laser_Shoot();
  Play();
}

void DialogSFX::on_ExplosionBtn_clicked()
{
  sfx.Explosion();
  Play();
}

void DialogSFX::on_PowerUpBtn_clicked()
{
  sfx.PowerUp();
  Play();
}

void DialogSFX::on_Hit_HurtBtn_clicked()
{
  sfx.Hit_Hurt();
  Play();
}

void DialogSFX::on_JumpBtn_clicked()
{
  sfx.Jump();
  Play();
}

void DialogSFX::on_Blip_SelectBtn_clicked()
{
  sfx.Blip_Select();
  Play();
}
