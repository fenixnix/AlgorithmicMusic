#ifndef DIALOGSFX_H
#define DIALOGSFX_H

#include <QDialog>
#include "Chiptune/Sfx8Bit.h"
#include "Device/NQWavPlayer.h"

namespace Ui {
  class DialogSFX;
}

class DialogSFX : public QDialog
{
  Q_OBJECT

public:
  explicit DialogSFX(QWidget *parent = 0);
  ~DialogSFX();

private slots:
  void on_PickUp_CoinBtn_clicked();

  void on_Laser_ShootBtn_clicked();

  void on_ExplosionBtn_clicked();

  void on_PowerUpBtn_clicked();

  void on_Hit_HurtBtn_clicked();

  void on_JumpBtn_clicked();

  void on_Blip_SelectBtn_clicked();

private:
  Ui::DialogSFX *ui;
};

#endif // DIALOGSFX_H
