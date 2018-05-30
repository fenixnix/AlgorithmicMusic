#include "Sfx8Bit.h"

#define rnd(n) (rand()%(n+1))

#define PI 3.14159265f

float frnd(float range)
{
    return (float)rnd(10000)/10000*range;
}

Sfx8Bit::Sfx8Bit()
{

}

void Sfx8Bit::Init()
{
    wave_type=0;

    p_base_freq=0.3f;
    p_freq_limit=0.0f;
    p_freq_ramp=0.0f;
    p_freq_dramp=0.0f;
    p_duty=0.0f;
    p_duty_ramp=0.0f;

    p_vib_strength=0.0f;
    p_vib_speed=0.0f;
    p_vib_delay=0.0f;

    envelope.Init();
    filter.Init();

    p_pha_offset=0.0f;
    p_pha_ramp=0.0f;

    p_repeat_speed=0.0f;

    p_arp_speed=0.0f;
    p_arp_mod=0.0f;
}

void Sfx8Bit::Reset()
{
    phase=0;
    fperiod=100.0/(p_base_freq*p_base_freq+0.001);
    period=(int)fperiod;
    fmaxperiod=100.0/(p_freq_limit*p_freq_limit+0.001);
    fslide=1.0-pow((double)p_freq_ramp, 3.0)*0.01;
    fdslide=-pow((double)p_freq_dramp, 3.0)*0.000001;
    WavBase::duty=0.5f-p_duty*0.5f;
    square_slide=-p_duty_ramp*0.00005f;
    if(p_arp_mod>=0.0f)
        arp_mod=1.0-pow((double)p_arp_mod, 2.0)*0.9;
    else
        arp_mod=1.0+pow((double)p_arp_mod, 2.0)*10.0;
    arp_time=0;
    arp_limit=(int)(pow(1.0f-p_arp_speed, 2.0f)*20000+32);
    if(p_arp_speed==1.0f)
        arp_limit=0;

    filter.Reset();

    // reset vibrato
    vib_phase=0.0f;
    vib_speed=pow(p_vib_speed, 2.0f)*0.01f;
    vib_amp=p_vib_strength*0.5f;

    fphase=pow(p_pha_offset, 2.0f)*1020.0f;
    if(p_pha_offset<0.0f) fphase=-fphase;
    fdphase=pow(p_pha_ramp, 2.0f)*1.0f;
    if(p_pha_ramp<0.0f) fdphase=-fdphase;
    iphase=abs((int)fphase);
    ipp=0;
    for(int i=0;i<1024;i++)
        phaser_buffer[i]=0.0f;

    rep_time=0;
    rep_limit=(int)(pow(1.0f-p_repeat_speed, 2.0f)*20000+32);
    if(p_repeat_speed==0.0f)
      rep_limit=0;
}

void Sfx8Bit::Randomize()
{
    p_base_freq=pow(frnd(2.0f)-1.0f, 2.0f);
    if(rnd(1))
        p_base_freq=pow(frnd(2.0f)-1.0f, 3.0f)+0.5f;
    p_freq_limit=0.0f;
    p_freq_ramp=pow(frnd(2.0f)-1.0f, 5.0f);
    if(p_base_freq>0.7f && p_freq_ramp>0.2f)
        p_freq_ramp=-p_freq_ramp;
    if(p_base_freq<0.2f && p_freq_ramp<-0.05f)
        p_freq_ramp=-p_freq_ramp;
    p_freq_dramp=pow(frnd(2.0f)-1.0f, 3.0f);
    p_duty=frnd(2.0f)-1.0f;
    p_duty_ramp=pow(frnd(2.0f)-1.0f, 3.0f);
    p_vib_strength=pow(frnd(2.0f)-1.0f, 3.0f);
    p_vib_speed=frnd(2.0f)-1.0f;
    p_vib_delay=frnd(2.0f)-1.0f;

    envelope.Randomize();
    filter.Randomize();

    p_pha_offset=pow(frnd(2.0f)-1.0f, 3.0f);
    p_pha_ramp=pow(frnd(2.0f)-1.0f, 3.0f);
    p_repeat_speed=frnd(2.0f)-1.0f;
    p_arp_speed=frnd(2.0f)-1.0f;
    p_arp_mod=frnd(2.0f)-1.0f;
}

void Sfx8Bit::Mutate()
{
    if(rnd(1)) p_base_freq+=frnd(0.1f)-0.05f;
    //		if(rnd(1)) p_freq_limit+=frnd(0.1f)-0.05f;
    if(rnd(1)) p_freq_ramp+=frnd(0.1f)-0.05f;
    if(rnd(1)) p_freq_dramp+=frnd(0.1f)-0.05f;
    if(rnd(1)) p_duty+=frnd(0.1f)-0.05f;
    if(rnd(1)) p_duty_ramp+=frnd(0.1f)-0.05f;
    if(rnd(1)) p_vib_strength+=frnd(0.1f)-0.05f;
    if(rnd(1)) p_vib_speed+=frnd(0.1f)-0.05f;
    if(rnd(1)) p_vib_delay+=frnd(0.1f)-0.05f;

    envelope.Mutate();
    filter.Mutate();

    if(rnd(1)) p_pha_offset+=frnd(0.1f)-0.05f;
    if(rnd(1)) p_pha_ramp+=frnd(0.1f)-0.05f;
    if(rnd(1)) p_repeat_speed+=frnd(0.1f)-0.05f;
    if(rnd(1)) p_arp_speed+=frnd(0.1f)-0.05f;
    if(rnd(1)) p_arp_mod+=frnd(0.1f)-0.05f;
}

float Sfx8Bit::SuperSamplingX8()
{
    float ssample=0.0f;
    for(int si=0;si<8;si++) // 8x supersampling
    {
        float sample=0.0f;
        phase++;
        if(phase>=period)
        {
            //				phase=0;
            phase%=period;
            if(wave_type==3)
              WavBase::randomNoise();
        }
        // base waveform
        float fp=(float)phase/period;
        sample = WavBase::wave(wave_type, fp);
        sample = filter.Filtration(sample);

        // phaser
        phaser_buffer[ipp&1023]=sample;
        sample+=phaser_buffer[(ipp-iphase+1024)&1023];
        ipp=(ipp+1)&1023;
        // final accumulation and envelope application
        ssample+=sample*env_vol;
    }
    ssample=ssample/8*master_vol;
    ssample*=2.0f*sound_vol;
    if(ssample>1.0f) ssample=1.0f;
    if(ssample<-1.0f) ssample=-1.0f;

    return ssample;
}

void Sfx8Bit::SynthSample(vector<float> &data)
{
    data.clear();
    Reset();
    envelope.Reset();
    playing_sample = true;
    for(int i = 0;i<wav_freq*2;i++)
    {
        if(!playing_sample){
            break;
        }
        rep_time++;
        if(rep_limit!=0 && rep_time>=rep_limit)
        {
            rep_time=0;
            Reset();
        }

        // frequency envelopes/arpeggios
        arp_time++;
        if(arp_limit!=0 && arp_time>=arp_limit)
        {
            arp_limit=0;
            fperiod*=arp_mod;
        }

        fslide+=fdslide;
        fperiod*=fslide;
        if(fperiod>fmaxperiod)
        {
            fperiod=fmaxperiod;
            if(p_freq_limit>0.0f)
                playing_sample=false;
        }
        float rfperiod=fperiod;
        if(vib_amp>0.0f)
        {
            vib_phase+=vib_speed;
            rfperiod=fperiod*(1.0+sin(vib_phase)*vib_amp);
        }
        period=(int)rfperiod;
        if(period<8) period=8;
        WavBase::duty+=square_slide;
        WavBase::DutyQuality();

        env_vol = envelope.Sampling(playing_sample);

        // phaser step
        fphase+=fdphase;
        iphase=abs((int)fphase);
        if(iphase>1023) iphase=1023;


        filter.Prepare();

        float ssample = SuperSamplingX8();
        data.push_back(ssample);

    }
}

void Sfx8Bit::PickUp_Coin()
{
    Init();
    p_base_freq=0.4f+frnd(0.5f);
    envelope.PickUp_Coin();
    if(rnd(1))
    {
        p_arp_speed=0.5f+frnd(0.2f);
        p_arp_mod=0.2f+frnd(0.4f);
    }
}

void Sfx8Bit::Laser_Shoot()
{
    Init();
    wave_type=rnd(2);
    if(wave_type==2 && rnd(1))
        wave_type=rnd(1);
    p_base_freq=0.5f+frnd(0.5f);
    p_freq_limit=p_base_freq-0.2f-frnd(0.6f);
    if(p_freq_limit<0.2f) p_freq_limit=0.2f;
    p_freq_ramp=-0.15f-frnd(0.2f);
    if(rnd(2)==0)
    {
        p_base_freq=0.3f+frnd(0.6f);
        p_freq_limit=frnd(0.1f);
        p_freq_ramp=-0.35f-frnd(0.3f);
    }
    if(rnd(1))
    {
        p_duty=frnd(0.5f);
        p_duty_ramp=frnd(0.2f);
    }
    else
    {
        p_duty=0.4f+frnd(0.5f);
        p_duty_ramp=-frnd(0.7f);
    }
    envelope.Laser_Shoot();
    if(rnd(2)==0)
    {
        p_pha_offset=frnd(0.2f);
        p_pha_ramp=-frnd(0.2f);
    }
    filter.Laser_Shoot();
}

void Sfx8Bit::Explosion()
{
    Init();
    wave_type=3;
    if(rnd(1))
    {
        p_base_freq=0.1f+frnd(0.4f);
        p_freq_ramp=-0.1f+frnd(0.4f);
    }
    else
    {
        p_base_freq=0.2f+frnd(0.7f);
        p_freq_ramp=-0.2f-frnd(0.2f);
    }
    p_base_freq*=p_base_freq;
    if(rnd(4)==0)
        p_freq_ramp=0.0f;
    if(rnd(2)==0)
        p_repeat_speed=0.3f+frnd(0.5f);

    envelope.Explosion();
    if(rnd(1)==0)
    {
        p_pha_offset=-0.3f+frnd(0.9f);
        p_pha_ramp=-frnd(0.3f);
    }

    if(rnd(1))
    {
        p_vib_strength=frnd(0.7f);
        p_vib_speed=frnd(0.6f);
    }
    if(rnd(2)==0)
    {
        p_arp_speed=0.6f+frnd(0.3f);
        p_arp_mod=0.8f-frnd(1.6f);
    }
}

void Sfx8Bit::PowerUp()
{
    Init();
    if(rnd(1))
        wave_type=1;
    else
        p_duty=frnd(0.6f);
    if(rnd(1))
    {
        p_base_freq=0.2f+frnd(0.3f);
        p_freq_ramp=0.1f+frnd(0.4f);
        p_repeat_speed=0.4f+frnd(0.4f);
    }
    else
    {
        p_base_freq=0.2f+frnd(0.3f);
        p_freq_ramp=0.05f+frnd(0.2f);
        if(rnd(1))
        {
            p_vib_strength=frnd(0.7f);
            p_vib_speed=frnd(0.6f);
        }
    }
    envelope.PowerUp();
}

void Sfx8Bit::Hit_Hurt()
{
    Init();
    wave_type=rnd(2);
    if(wave_type==2)
        wave_type=3;
    if(wave_type==0)
        p_duty=frnd(0.6f);
    p_base_freq=0.2f+frnd(0.6f);
    p_freq_ramp=-0.3f-frnd(0.4f);
    envelope.Hit_Hurt();
    filter.Hit_Hurt();
}

void Sfx8Bit::Jump()
{
    Init();
    wave_type=0;
    p_duty=frnd(0.6f);
    p_base_freq=0.3f+frnd(0.3f);
    p_freq_ramp=0.1f+frnd(0.2f);
    envelope.Jump();
    filter.Jump();
}

void Sfx8Bit::Blip_Select()
{
    Init();
    wave_type=rnd(1);
    if(wave_type==0)
        p_duty=frnd(0.6f);
    p_base_freq=0.2f+frnd(0.4f);
    envelope.Blip_Select();
    filter.Blip_Select();
}
