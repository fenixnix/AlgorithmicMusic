#ifndef FORMKEYBOARD_H
#define FORMKEYBOARD_H

#include <QWidget>
#include "Device//qmusicinstrument.h"

namespace Ui {
  class FormKeyboard;
}

class FormKeyboard : public QWidget
{
  Q_OBJECT

public:
  explicit FormKeyboard(QWidget *parent = 0);
  ~FormKeyboard();

public slots:
  void OnClickKey();
  void RefreshModes();

private slots:
  void on_btnBass_clicked();

  void on_btnSide_clicked();

  void on_btnHighHat_clicked();

  void on_btnTomtom_clicked();

  void on_comboBoxMode_currentTextChanged(const QString &arg1);

private:
  Ui::FormKeyboard *ui;
  QMusicInstrument music;
  QMusicInstrument Drum;
  void InitKey();
};

#endif // FORMKEYBOARD_H
