#ifndef WAVFILTER_H
#define WAVFILTER_H


class WavFilter
{
public:
    WavFilter();
    void Init();
    void Reset();
    void Prepare();
    void Randomize();
    void Mutate();

    void Laser_Shoot();
    void Hit_Hurt();
    void Jump();
    void Blip_Select();

    float Filtration(float input);

    float p_lpf_resonance;//"LP FILTER RESONANCE"
    float p_lpf_freq;//"LP FILTER CUTOFF"
    float p_lpf_ramp;//"LP FILTER CUTOFF SWEEP"
    float p_hpf_freq;//"HP FILTER CUTOFF"
    float p_hpf_ramp;//"HP FILTER CUTOFF SWEEP"

private:
    float fltp;
    float fltdp;
    float fltw;
    float fltw_d;
    float fltdmp;
    float fltphp;
    float flthp;
    float flthp_d;
};

#endif // WAVFILTER_H
