#include "wavfilter.h"
#include <random>
#include "math.h"

using namespace std;

#define rnd(n) (rand()%(n+1))

extern float frnd(float range);

WavFilter::WavFilter()
{

}

void WavFilter::Init()
{
    p_lpf_resonance=0.0f;
    p_lpf_freq=1.0f;
    p_lpf_ramp=0.0f;
    p_hpf_freq=0.0f;
    p_hpf_ramp=0.0f;
}

void WavFilter::Reset()
{
    // reset filter
    fltp=0.0f;
    fltdp=0.0f;
    fltw=pow(p_lpf_freq, 3.0f)*0.1f;
    fltw_d=1.0f+p_lpf_ramp*0.0001f;
    fltdmp=5.0f/(1.0f+pow(p_lpf_resonance, 2.0f)*20.0f)*(0.01f+fltw);
    if(fltdmp>0.8f) fltdmp=0.8f;
    fltphp=0.0f;
    flthp=pow(p_hpf_freq, 2.0f)*0.1f;
    flthp_d=1.0+p_hpf_ramp*0.0003f;
}

void WavFilter::Prepare()
{
    //在Sample前预处理
    if(flthp_d!=0.0f)
    {
        flthp*=flthp_d;
        if(flthp<0.00001f) flthp=0.00001f;
        if(flthp>0.1f) flthp=0.1f;
    }
}

void WavFilter::Randomize()
{
    p_lpf_resonance=frnd(2.0f)-1.0f;
    p_lpf_freq=1.0f-pow(frnd(1.0f), 3.0f);
    p_lpf_ramp=pow(frnd(2.0f)-1.0f, 3.0f);
    if(p_lpf_freq<0.1f && p_lpf_ramp<-0.05f)
        p_lpf_ramp=-p_lpf_ramp;
    p_hpf_freq=pow(frnd(1.0f), 5.0f);
    p_hpf_ramp=pow(frnd(2.0f)-1.0f, 5.0f);
}

void WavFilter::Mutate()
{
    if(rnd(1)) p_lpf_resonance+=frnd(0.1f)-0.05f;
    if(rnd(1)) p_lpf_freq+=frnd(0.1f)-0.05f;
    if(rnd(1)) p_lpf_ramp+=frnd(0.1f)-0.05f;
    if(rnd(1)) p_hpf_freq+=frnd(0.1f)-0.05f;
    if(rnd(1)) p_hpf_ramp+=frnd(0.1f)-0.05f;
}

void WavFilter::Laser_Shoot()
{
    if(rnd(1))
        p_hpf_freq=frnd(0.3f);
}

void WavFilter::Hit_Hurt()
{
    if(rnd(1))
        p_hpf_freq=frnd(0.3f);
}

void WavFilter::Jump()
{
    if(rnd(1))
        p_hpf_freq=frnd(0.3f);
    if(rnd(1))
        p_lpf_freq=1.0f-frnd(0.6f);
}

void WavFilter::Blip_Select()
{
    p_hpf_freq=0.1f;
}

float WavFilter::Filtration(float input)
{
    float sample = input;
    // lp filter
    float pp=fltp;
    fltw*=fltw_d;
    if(fltw<0.0f) fltw=0.0f;
    if(fltw>0.1f) fltw=0.1f;
    if(p_lpf_freq!=1.0f)
    {
        fltdp+=(sample-fltp)*fltw;
        fltdp-=fltdp*fltdmp;
    }
    else
    {
        fltp=sample;
        fltdp=0.0f;
    }
    fltp+=fltdp;
    // hp filter
    fltphp+=fltp-pp;
    fltphp-=fltphp*flthp;
    sample=fltphp;
    return sample;
}
