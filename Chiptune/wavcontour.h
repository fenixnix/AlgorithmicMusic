#ifndef WAVCONTOUR_H
#define WAVCONTOUR_H

#include <QList>
#include <QPoint>
#include <QString>
#include <QDebug>

class WavContour
{
public:
  WavContour();
  void Clear();
  void Push(QPointF node);//x diffSecond y:0~1.0
  void Push(float x, float y);

  void Sfx8BitContour(float attack, float sustain, float decay, float punch);

  void TrapezoidaEnvelope(float t1 = 0.1f,float t2 = 0.4f, float t3 = 0.5f, float maxVal = 1.0f);

  QList<float> GetData(int sampleRate);
  int DataSize(int sampleRate);

  QString Print();

private:
  QList<QPointF> contour;
  float startTime = 0.0f;
  float startVol = 0.0f;
  int index = 0;
};

#endif // WAVCONTOUR_H
