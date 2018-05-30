#include "nchiptune.h"

NChipTune::NChipTune()
{
  Format.setSampleRate(22500);
  Format.setChannelCount(1);
  Format.setSampleSize(8);
  Format.setSampleType(QAudioFormat::SignedInt);
  Format.setByteOrder(QAudioFormat::LittleEndian);
  Format.setCodec("audio/pcm");
}

void NChipTune::Start()
{
  open(QIODevice::ReadOnly);
}

void NChipTune::Stop()
{
  m_pos = 0;
  close();
}

//char c;
qint64 NChipTune::readData(char *data, qint64 len)
{
  qint64 total = 0;
  if (!buffer.isEmpty()) {
      while (len - total > 0) {
          const qint64 chunk = qMin((buffer.size() - m_pos), len - total);
          memcpy(data + total, buffer.constData() + m_pos, chunk);
          m_pos = (m_pos + chunk) % buffer.size();
          total += chunk;
        }
    }
  return total;
  //    c = 127;
  //    memcpy(data,&c,1);
  //    return 1;
}

qint64 NChipTune::writeData(const char *data, qint64 len)
{
  Q_UNUSED(data);
  Q_UNUSED(len);
  return 0;
}

qint64 NChipTune::bytesAvailable() const
{
  return buffer.size() + QIODevice::bytesAvailable();
}

vector<float> BrToRawData(QByteArray data)
{
  vector<float> outDatas;
  for(char c :data){
      outDatas.push_back((float)c/127.0f);
    }
  return outDatas;
}

void NChipTune::generateData(QString type, int freq, WavContour contour)
{
  if(type == "Pulse"){
      Pulse(freq);
    }

  if(type == "Triangle"){
      Triangle(freq);
    }

  if(type == "Sine"){
      Sine(freq);
    }

  if(type == "Noise"){
      Noise(freq);
    }

  auto dataSize = contour.DataSize(Format.sampleRate());
  QByteArray tmpBuffer;
  while(tmpBuffer.size()<dataSize){
      tmpBuffer.push_back(buffer);
    }
  auto data = contour.GetData(Format.sampleRate());
  buffer.clear();
  for(int i = 0;i<data.size();i++){
      float v = data[i];
      char b = tmpBuffer[i];
      char val = b*v;
      //qDebug()<<"v:"<<v<<"*"<<b<<"*"<<val;
      buffer.append(val);
    }
}

void NChipTune::Pulse()
{
  Stop();
  buffer.clear();
  Period = Format.sampleRate()/Freq;
  int HiCnt = Period*Duty;
  int LoCnt = Period-HiCnt;
  int Amp = CHAR_MAX*Volume;
  char HiVal = Amp;
  char LoVal = -Amp;

  buffer.append(QByteArray(HiCnt,HiVal));
  buffer.append(QByteArray(LoCnt,LoVal));
}

void NChipTune::Pulse(int freq)
{
  Freq = freq;
  Pulse();
}

void NChipTune::Triangle()
{
  Stop();
  buffer.clear();
  Period = Format.sampleRate()/Freq;
  int halfT = Period/2;

  int Amp = CHAR_MAX*Volume;
  int DAmp = Amp*2;
  char HiVal = Amp;
  char LoVal = -Amp;

  for(int i = 0;i<halfT;i++){
      char v = LoVal + i*DAmp/halfT;
      buffer.append(v);
    }
  for(int i = 0;i<halfT;i++){
      char v = HiVal - i*DAmp/halfT;
      buffer.append(v);
    }
}

void NChipTune::Triangle(int freq)
{
  Freq = freq;
  Triangle();
}

void NChipTune::Sine()
{
  Stop();
  buffer.clear();
  Period = Format.sampleRate()/Freq;
  int Amp = CHAR_MAX*Volume;
  for(int i = 0;i<Period;i++){
      char v = Amp*sin(M_PI*2*i/Period);
      buffer.append(v);
    }
}

void NChipTune::Sine(int freq)
{
  Freq =freq;
  Sine();
}

void NChipTune::Noise()
{
  Stop();
  buffer.clear();
  Period = Format.sampleRate()/Freq;
  int Amp = CHAR_MAX*Volume;
  int DAmp = Amp*2;

  //Type1
      for(int j = 0;j<Freq;j++){
          char v = qrand()%DAmp-Amp;
          for(int i = 0;i<Period;i++){
              buffer.append(v);
          }
      }

  //  //Type2
  //  for(int i = 0;i<Period;i++){
  //      char v = qrand()%DAmp-Amp;
  //      buffer.append(v);
  //    }

//  //Type3
//  char rndData[32];
//  for(int i = 0;i<32;i++){
//      rndData[i] = qrand()%DAmp-Amp;
//    }

//  for(int i = 0;i<Period;i++){
//      buffer.append(rndData[i/32]);
//    }

//      //Type4
//          for(int j = 0;j<32;j++){
//              char v = qrand()%DAmp-Amp;
//              for(int i = 0;i<Period/32;i++){
//                  buffer.append(v);
//              }
//          }

}

void NChipTune::Noise(int freq)
{
  Freq = freq;
  Noise();
}

QString NChipTune::Print()
{
  QString str;
  foreach (auto b, buffer) {
      str += b;
      qDebug()<<(char)b;
    }
  return str;
}
