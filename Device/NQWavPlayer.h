#ifndef QAUDIOPLAYER_H
#define QAUDIOPLAYER_H

#include <QAudioOutput>
#include <QBuffer>
#include <QString>
#include <QDebug>
#include <vector>
#include "nchiptune.h"
#include "Chiptune/nwavwriter.h"

using namespace std;

class NQWavPlayer
{
public:
  NQWavPlayer();
  ~NQWavPlayer();

  QStringList GetAvailableDevices();
  void SetDevice(QString deviceID);
  void Import(QByteArray data);
  void ImportData(vector<float> rawData);
  void Save(QString fileName);
  static vector<float> Export(QByteArray data);

  void Play();
  void Play(QByteArray data);

  QAudioFormat format;

private:
  bool CheckDevice();
  QAudioDeviceInfo deviceInfo;
  QAudioOutput* output;

  QBuffer* buffer;
  QByteArray dataBuffer;
};

#endif // QAUDIOPLAYER_H
