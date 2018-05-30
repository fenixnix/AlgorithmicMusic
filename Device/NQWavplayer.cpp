#include "NQWavPlayer.h"

NQWavPlayer::NQWavPlayer()
{
  buffer = NULL;
  format.setSampleRate(22500);
  format.setChannelCount(1);
  format.setSampleSize(8);
  format.setSampleType(QAudioFormat::SignedInt);
  format.setByteOrder(QAudioFormat::LittleEndian);
  format.setCodec("audio/pcm");
  deviceInfo = QAudioDeviceInfo::defaultOutputDevice();
  CheckDevice();
  buffer = new QBuffer(&dataBuffer);
  output = new QAudioOutput(deviceInfo,format);
}

NQWavPlayer::~NQWavPlayer()
{
  buffer->close();
  output->stop();
  delete buffer;
  delete output;
}

QStringList NQWavPlayer::GetAvailableDevices()
{
  auto deviceList = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);
  QStringList list;
  for(auto d : deviceList){
      list.append(d.deviceName());
    }
  return list;
}

void NQWavPlayer::SetDevice(QString deviceID)
{
  auto deviceList = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);
  for(auto d : deviceList){
      if(d.deviceName() == deviceID){
          deviceInfo = d;
          CheckDevice();
          break;
        }
    }
  CheckDevice();
}

void NQWavPlayer::ImportData(vector<float> rawData)
{
  output->stop();
  dataBuffer.clear();
  for(auto d :rawData){
      dataBuffer.append((char)(d*127+128));
    }
  buffer->open(QIODevice::ReadOnly);
}

void NQWavPlayer::Save(QString fileName)
{
  auto data = Export(dataBuffer);
  NWavWriter::Save(fileName.toStdString(),data);
}

vector<float> NQWavPlayer::Export(QByteArray data)
{
  vector<float> outDatas;
  for(char c :data){
      outDatas.push_back((float)c/127.0f);
    }
}

void NQWavPlayer::Import(QByteArray data)
{
  output->stop();
  dataBuffer.clear();
  dataBuffer.append(data);
  buffer->open(QIODevice::ReadOnly);
}

void NQWavPlayer::Play()
{
  output->start(buffer);
}

void NQWavPlayer::Play(QByteArray data)
{
  Import(data);
  Play();
}

bool NQWavPlayer::CheckDevice()
{
  if (!deviceInfo.isFormatSupported(format)) {
      qWarning() << "Raw audio format not supported by backend, cannot play audio.";
      return false;
    }
  return true;
}

