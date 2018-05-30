#ifndef QMUSICINSTRUMENT_H
#define QMUSICINSTRUMENT_H

#include "NQWavPlayer.h"
#include "ACM/NTonic.h"
#include "Chiptune/wavcontour.h"

class QMusicInstrument
{
public:
  QMusicInstrument();
  void Play(int index);
  void PlayChip();

  void Bass();
  void SideDrum();
  void Tomtom();
  void HighHat();

  void SetMode(QString mode);
  int GetModeNoteCount();

//private:

  NTonic music;
  WavContour contour;
  NChipTune chipTune;
  NQWavPlayer player;
};

#endif // QMUSICINSTRUMENT_H
