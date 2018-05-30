#ifndef SFX8BIT_H
#define SFX8BIT_H

#include<vector>
#include "wavbase.h"
#include "wavfilter.h"
#include "wavenvelope.h"
#include "wavcontour.h"

using namespace std;

class Sfx8Bit
{
public:
    Sfx8Bit();
    void Init();
    void Reset();
    void Randomize();
    void Mutate();
    void SynthSample(vector<float> &data);

    void PickUp_Coin();//type 0
    void Laser_Shoot();//type 0,1,2
    void Explosion();//type 3
    void PowerUp();//type 0,1
    void Hit_Hurt();//type 0,1,3
    void Jump();//type 0
    void Blip_Select();//type 0,1


private:
    int wave_type = 0;

    WavFilter filter;
    WavEnvelope envelope;

    float p_base_freq;//"START FREQUENCY"
    float p_freq_limit;//"MIN FREQUENCY"
    float p_freq_ramp;//"SLIDE"
    float p_freq_dramp;//"DELTA SLIDE"
    float p_duty;//"SQUARE DUTY"
    float p_duty_ramp;//"DUTY SWEEP"

    float p_vib_strength;//"VIBRATO DEPTH"
    float p_vib_speed;//"VIBRATO SPEED"
    float p_vib_delay;

    float p_pha_offset;//"PHASER OFFSET"
    float p_pha_ramp;//"PHASER SWEEP"

    float p_repeat_speed;//"REPEAT SPEED"

    float p_arp_speed;//"CHANGE SPEED"
    float p_arp_mod;//"CHANGE AMOUNT"

    float master_vol=0.05f;

    float sound_vol=0.5f;//"VOLUME"
    //////////////////////////////////////////////////////////////
    bool playing_sample=false;
    int phase;
    double fperiod;
    double fmaxperiod;
    double fslide;
    double fdslide;
    int period;
    float square_slide;

    float env_vol;


    float fphase;
    float fdphase;
    int iphase;
    float phaser_buffer[1024];
    int ipp;

    float vib_phase;
    float vib_speed;
    float vib_amp;
    int rep_time;
    int rep_limit;
    int arp_time;
    int arp_limit;
    double arp_mod;

    float* vselected=NULL;
    int vcurbutton=-1;

    int wav_bits=8;
    int wav_freq=22050;
    float SuperSamplingX8();
};

#endif // SFX8BIT_H
