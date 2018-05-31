#ifndef WAVBASE_H
#define WAVBASE_H


class WavBase
{
public:
  WavBase();
  static void randomNoise();
  static float wave(int type, float phase);

  static float Square(float phase, float duty);
  static float Triangle(float phase, float duty);
  static float Sine(float phase);
  static float Noise(float phase);

  static void SetDuty(float d);
  static float duty;
private:
};

#endif // WAVBASE_H
