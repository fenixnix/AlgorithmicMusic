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
  float tmpSample = 0;
  switch(type)
    {
    case 0: // square
      if(phase<duty)
        tmpSample=0.5f;
      else
        tmpSample=-0.5f;
      break;
    case 1: // sawtooth
      tmpSample=1.0f-phase*2;
      break;
    case 2: // sine
      tmpSample=(float)sin(phase*2*M_PI);
      break;
    case 3: // noise
      int i = (int)(phase*(float)(32));
      if(i>31){
          i = 31;
        }
      tmpSample=noise_buffer[i];
      break;
    }
  return tmpSample;
}

void WavBase::DutyQuality()
{
  if(duty>0.5f)duty = 0.5f;
  if(duty<0.0f)duty = 0.0f;
}
