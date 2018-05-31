#include "nchiptune.h"
#include "Chiptune/nwavwriter.h"

NChipTune::NChipTune()
{
  Format.setSampleRate(22500);
  Format.setChannelCount(1);
  Format.setSampleSize(8);
  Format.setSampleType(QAudioFormat::UnSignedInt);
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
//  for(int i = 0;i<data.size();i++){
//      float v = data[i];
//      char b = tmpBuffer[i];
//      char val = b*v;
//      //qDebug()<<"v:"<<v<<"*"<<b<<"*"<<val;
//      buffer.append(val);
//    }
  buffer.push_back(tmpBuffer);
}

void NChipTune::Pulse()
{
  Stop();
  buffer.clear();
  Period = Format.sampleRate()/Freq;
  int HiCnt = Period*Duty;
  int LoCnt = Period-HiCnt;
  int Amp = SCHAR_MAX*Volume;
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

  rawBuffer.clear();

  Period = Format.sampleRate()/Freq;

  int Amp = SCHAR_MAX*Volume;

  for(int i = 0;i<Period;i++){
      float phase = (float)i/Period;
      char v = Amp*WavBase::Triangle(phase,Duty)+127;
      rawBuffer.push_back(WavBase::Triangle(phase,Duty));
      buffer.append(v);
    }
  NWavWriter::Save("triangle.wav",rawBuffer);
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

  rawBuffer.clear();

  Period = Format.sampleRate()/Freq;
  int Amp = SCHAR_MAX*Volume;
  for(int i = 0;i<Period;i++){
      float phase = (float)i/Period;
      char v = Amp*WavBase::Sine(phase)+127;
      rawBuffer.push_back(WavBase::Sine(phase));
      buffer.append(v);
    }
  NWavWriter::Save("sine.wav",rawBuffer);
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
  int Amp = SCHAR_MAX*Volume;

  //Type1
      for(int j = 0;j<Freq;j++){
          WavBase::randomNoise();
          for(int i = 0;i<Period;i++){
              float phase = (float)i/Period;
              char v = Amp*WavBase::Noise(phase)+127;
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
