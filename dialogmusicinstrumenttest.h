#ifndef DIALOGMUSICINSTRUMENTTEST_H
#define DIALOGMUSICINSTRUMENTTEST_H

#include <QDialog>
#include "Device/qmusicinstrument.h"

namespace Ui {
class DialogMusicInstrumentTest;
}

class DialogMusicInstrumentTest : public QDialog
{
    Q_OBJECT

public:
    explicit DialogMusicInstrumentTest(QWidget *parent = 0);
    ~DialogMusicInstrumentTest();

    void Refresh();

private slots:
    void on_pushButtonPlay_clicked();

private:
    Ui::DialogMusicInstrumentTest *ui;
    QMusicInstrument music;
};

#endif // DIALOGMUSICINSTRUMENTTEST_H
