#include "wavbase.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <random>

using namespace std;

#define rnd(n) (rand()%(n+1))
#define frnd(n) ((float)rnd(10000)/10000*n)

float WavBase::duty = 0.5f;
#define NOISE_BUFFER_SIZE 32
static float noise_buffer[NOISE_BUFFER_SIZE];

WavBase::WavBase()
{
  randomNoise();
}

void WavBase::randomNoise()
{
  for(int i=0;i<sizeof(noise_buffer);i++)
    noise_buffer[i]=frnd(2.0f)-1.0f;
}

float WavBase::wave(int type, float phase)
{
  switch(type)
    {
    case 0: return Square(phase,duty);break;// square
    case 1: return Triangle(phase,duty);break;// sawtooth
    case 2: return Sine(phase);break;// sine
    case 3: return Noise(phase);break;// noise
    default: return 0;break;
    }
  return 0;
}

void WavBase::SetDuty(float d)
{
  if(d>0.5f)duty = 0.5f;
  if(d<0)duty = 0;
}

float WavBase::Square(float phase, float duty)
{
  if(phase<duty)
    return 1;
  return -1;
}

float WavBase::Triangle(float phase, float duty)
{
  if(phase<duty){
      return -1+2.0f*(phase/duty);
    }
  return 1-2.0f*((phase-duty)/(1-duty));
}

float WavBase::Sine(float phase)
{
  return (float)sin(phase*2.0f*M_PI);
}

float WavBase::Noise(float phase)
{
  int i = (int)(phase*(float)(32));
  if(i>31){
      i = 31;
    }
  return noise_buffer[i];
}
