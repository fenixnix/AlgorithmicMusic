#ifndef WAVBASE_H
#define WAVBASE_H


class WavBase
{
public:
  WavBase();
  static void randomNoise();
  static float wave(int type, float phase);
  static float duty;
  static void DutyQuality();
private:
};

#endif // WAVBASE_H
