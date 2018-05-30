#include "wavenvelope.h"
#include <random>

using namespace std;

#define rnd(n) (rand()%(n+1))

extern float frnd(float range);

WavEnvelope::WavEnvelope()
{

}

void WavEnvelope::Init()
{
    p_env_attack=0.0f;
    p_env_sustain=0.3f;
    p_env_decay=0.4f;
    p_env_punch=0.0f;
}

void WavEnvelope::Reset()
{
    env_vol=0.0f;
    env_stage=0;
    env_time=0;
    env_length[0]=(int)(p_env_attack*p_env_attack*100000.0f);
    env_length[1]=(int)(p_env_sustain*p_env_sustain*100000.0f);
    env_length[2]=(int)(p_env_decay*p_env_decay*100000.0f);
}

void WavEnvelope::Mutate()
{
    if(rnd(1)) p_env_attack+=frnd(0.1f)-0.05f;
    if(rnd(1)) p_env_sustain+=frnd(0.1f)-0.05f;
    if(rnd(1)) p_env_decay+=frnd(0.1f)-0.05f;
    if(rnd(1)) p_env_punch+=frnd(0.1f)-0.05f;
}

void WavEnvelope::Randomize()
{
    p_env_attack=pow(frnd(2.0f)-1.0f, 3.0f);
    p_env_sustain=pow(frnd(2.0f)-1.0f, 2.0f);
    p_env_decay=frnd(2.0f)-1.0f;
    p_env_punch=pow(frnd(0.8f), 2.0f);
    if(p_env_attack+p_env_sustain+p_env_decay<0.2f)
    {
        p_env_sustain+=0.2f+frnd(0.3f);
        p_env_decay+=0.2f+frnd(0.3f);
    }
}

void WavEnvelope::PickUp_Coin()
{
    p_env_attack=0.0f;
    p_env_sustain=frnd(0.1f);
    p_env_decay=0.1f+frnd(0.4f);
    p_env_punch=0.3f+frnd(0.3f);
}

void WavEnvelope::Laser_Shoot()
{
    p_env_attack=0.0f;
    p_env_sustain=0.1f+frnd(0.2f);
    p_env_decay=frnd(0.4f);
    if(rnd(1))
        p_env_punch=frnd(0.3f);
}

void WavEnvelope::Explosion()
{
    p_env_attack=0.0f;
    p_env_sustain=0.1f+frnd(0.3f);
    p_env_decay=frnd(0.5f);
    p_env_punch=0.2f+frnd(0.6f);
}

void WavEnvelope::PowerUp()
{
    p_env_attack=0.0f;
    p_env_sustain=frnd(0.4f);
    p_env_decay=0.1f+frnd(0.4f);
}

void WavEnvelope::Hit_Hurt()
{
    p_env_attack=0.0f;
    p_env_sustain=frnd(0.1f);
    p_env_decay=0.1f+frnd(0.2f);
}

void WavEnvelope::Jump()
{
    p_env_attack=0.0f;
    p_env_sustain=0.1f+frnd(0.3f);
    p_env_decay=0.1f+frnd(0.2f);
}

void WavEnvelope::Blip_Select()
{
    p_env_attack=0.0f;
    p_env_sustain=0.1f+frnd(0.1f);
    p_env_decay=frnd(0.2f);
}

float WavEnvelope::Sampling(bool &playing_sample)
{
    env_time++;
    if(env_time>env_length[env_stage])
    {
        env_time=0;
        env_stage++;
        if(env_stage==3)
            playing_sample=false;//判断直接退出采样
            //env_stage = 0;
    }
    if(env_stage==0)
        env_vol= (float)env_time/env_length[0];
    if(env_stage==1)
        //env_vol= 1.0f+pow(1.0f-(float)env_time/env_length[1], 1.0f)*2.0f*p_env_punch;
       env_vol= 1.0f+ (1.0f-(float)env_time/env_length[1])*2.0f*p_env_punch;
    if(env_stage==2)
        env_vol= 1.0f-(float)env_time/env_length[2];

    return env_vol;
}

void WavEnvelope::Setup(WavContour& contour)
{
  contour.Sfx8BitContour(p_env_attack,p_env_sustain,p_env_decay,p_env_punch);
}
