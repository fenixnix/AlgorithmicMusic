#ifndef NCHIPTUNE_H
#define NCHIPTUNE_H

#include <QIODevice>
#include <QAudioFormat>
#include <QDebug>
#include <qmath.h>
#include "Chiptune/wavcontour.h"
#include "Device//nchiptune.h"

using namespace std;

class NChipTune: public QIODevice
{
public:
    NChipTune();

    void Start();
    void Stop();

    qint64 readData(char *data, qint64 maxlen) override;
    qint64 writeData(const char *data, qint64 len) override;
    qint64 bytesAvailable() const override;

    void generateData(QString type,int freq,WavContour contour);

    QString Print();

    int Period = 1;
    float Duty = 0.25f;//0~0.5
    int Freq = 440;//200~10000
    float Volume = 0.3f;//0~1

    QAudioFormat Format;
    QByteArray buffer;
private:
    void Pulse();//12.5% 25% 50%
    void Pulse(int freq);
    void Triangle();
    void Triangle(int freq);
    void Sine();
    void Sine(int freq);
    void Noise();
    void Noise(int freq);
    qint64 m_pos;
};

#endif // NCHIPTUNE_H
