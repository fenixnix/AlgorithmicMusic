#include "nTonic.h"
#include <math.h>

int NTonic::modes[OCTAVE_SCALE][OCTAVE_SCALE];

NTonic::NTonic(int baseNote, MODE mode)
{
  initMode();
  this->baseNote = baseNote;
  this->mode = mode;
}

void NTonic::SetBase(int note)
{
  baseNote = note;
}

void NTonic::SetMode(MODE mode)
{
  this->mode = mode;
}

int NTonic::Note(int index)
{
  int octave = 0;
  int pitch = 0;
  if(index>=0){
      octave = index/OCTAVE_SCALE;
      pitch = index%OCTAVE_SCALE;
    }else{
      octave = (abs(index)/OCTAVE_SCALE)*-1 -1;
      pitch = OCTAVE_SCALE - (index*-1)%OCTAVE_SCALE;
    }
  return baseNote + octave*OCTAVE_CNT + modes[mode][pitch];
}

void NTonic::initMode()
{
  char baseMode[] = {2,2,1,2,2,2,1};
  for(int j = 0;j<OCTAVE_SCALE;j++){
      modes[j][0] = 0;
      for(int i = 0;i<OCTAVE_SCALE-1;i++){
          modes[j][i+1] = modes[j][i]+baseMode[i];
        }
      //mov array
      int tmp = baseMode[0];
      for(int i = 0;i<OCTAVE_SCALE-1;i++){
          baseMode[i] = baseMode[i+1];
        }
      baseMode[6] = tmp;
    }
}
