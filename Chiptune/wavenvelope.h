#ifndef WAVENVELOPE_H
#define WAVENVELOPE_H

#include "wavcontour.h"

class WavEnvelope
{
public:
    WavEnvelope();
    void Init();
    void Reset();
    void Mutate();
    void Randomize();

    void PickUp_Coin();
    void Laser_Shoot();
    void Explosion();
    void PowerUp();
    void Hit_Hurt();
    void Jump();
    void Blip_Select();

    float Sampling(bool &playing_sample);

    void Setup(WavContour& contour);

    float p_env_attack;//"ATTACK TIME"
    float p_env_sustain;//"SUSTAIN TIME"
    float p_env_decay;//"DECAY TIME"
    float p_env_punch;//"SUSTAIN PUNCH"

private:
    int env_stage;
    int env_time;
    int env_length[3];
    float env_vol;
};

#endif // WAVENVELOPE_H
