#include "wavcontour.h"

WavContour::WavContour()
{

}

void WavContour::Clear()
{
  contour.clear();
}

void WavContour::Push(QPointF node)
{
  contour.push_back(node);
}

void WavContour::Push(float x, float y)
{
  Push(QPointF(x,y));
}

void WavContour::Sfx8BitContour(float attack, float sustain, float decay, float punch)
{
  Clear();
  Push(attack,1);
  Push(0,punch*2+1);
  Push(sustain,1);
  Push(decay,0);
}

void WavContour::TrapezoidaEnvelope(float t1, float t2, float t3, float maxVal)
{
  Clear();
  Push(t1,maxVal);
  Push(t2,maxVal);
  Push(t3,0);
}

QList<float> WavContour::GetData(int sampleRate)
{
  QList<float> data;
  startTime = 0;
  startVol = 0;

  for(index = 0;index<contour.size();index++){
      auto p = contour[index];

      int x = sampleRate*(float)p.x();
      float dVol = (float)p.y() - startVol;

      for(int dCnt = 0;dCnt<x;dCnt++){
          float val = startVol + dVol*dCnt/x;
          data.append(val);
        }

      startTime += p.x();
      startVol = p.y();
    }
  return data;
}

int WavContour::DataSize(int sampleRate)
{
  float totleTime = 0;
  for(int i = 0;i<contour.size();i++){
    totleTime += contour[i].x();
    }
  return totleTime*sampleRate;
}

QString WavContour::Print()
{
  return QString();
}
