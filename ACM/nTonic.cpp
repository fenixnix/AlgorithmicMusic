#include "nTonic.h"
#include <math.h>
#include <iostream>

using namespace std;

int ChinaScale[] = {0,2,4,7,9};
int China2Scale[] = {0,3,5,7,10};
int Japan1Scale[] = {0,4,5,9,11};//日本音阶
int Japan2Scale[] = {0,4,5,7,11};
int OriScale[] = {0,1,4,5,6,9,10};//东方音阶

int ArabicScale[] = {1,2,4,6,7,9,11};//阿拉伯音阶
int Arabic2Scale[] = {0,1,4,5,7,8,10};
int FlamencoScale[] = {0,1,4,6,7,8,10};//弗拉门戈音阶
// ⑻ 印度音阶: [/B]1 2 3 4 5 b6 b7 （Hindu）
// ⑼ 吉普赛音阶： [/B]1 b3 #4 5 b6 b7 （Gypsy）
// ⑽ 匈牙利音阶： [/B]1 #2 3 #4 5 6 b7 （Hungarian）
// ⑾ 匈牙利小调音阶： [/B]1 2 b3 #4 5 b6 7 （Hungarian Minor）
// ⒂ 俄罗斯音阶[/B]： 1 2 3 4 (#4) 5 (#5) 6 (b7) 7
// ⒃ 爵士小调音阶：[/B] 1 2 b3 4 5 6 7

// ⒅ 拿波里大音阶：[/B] 1 b2 b3 4 5 6 7
// ⒆ 拿波里小音阶：[/B] 1 b2 b3 4 5 b6 7

int BlusScale[] = {0,3,5,6,7,10};//布鲁斯音阶
int MixelBluesScale[] = { 0,3,4,5,6,7,10};//混合布鲁斯音阶

int scale0[] = {0,2,4,6,8,9,11};//和声小调
int scale1[] = {0,2,3,5,6,8,10};//减音阶
int scale2[] = {0,1,3,4,6,7,9,10};//半—全减音阶
int scale3[] = {0,2,4,6,8,10};//全音音阶

// ⑹大利底亚音阶： [/B]1 2 3 #4 5 6 b7 ( Lydian-Dominant )
// ⑺ 超级洛克里亚音阶： [/B]1 b2 b3 b4 b5 b6 b7 （Super-Locrian）
// ⑿旋律大调音阶: [/B]1 2 3 4 5 b6 7 1 b7 b6 5 4 3 2 1
// ⒀旋律小调音阶： [/B]6 7 1 2 3 #4 #5 6 5 4 3 2 1 7 6


int NTonic::modes[OCTAVE_SCALE][OCTAVE_SCALE];

NTonic::NTonic(int baseNote, MODE mode)
{
  initMode();
  this->baseNote = baseNote;
  SetMode(mode);
}

void NTonic::SetBase(int note)
{
  baseNote = note;
}

void NTonic::SetMode(MODE mode)
{
  SetMode(modes[mode],OCTAVE_SCALE);
}

void NTonic::SetMode(int array[], int size)
{
    curMode.clear();
    octaveScale = size;

    cout<<__FUNCTION__<<" Size:"<<octaveScale<<endl;

    for(int i = 0;i<octaveScale;i++){
        cout<<array[i]<<"*";
        curMode.push_back(array[i]);
    }
    cout<<endl;
}

void NTonic::SetMode(int i)
{
    SetMode(ArabicScale,7);
}

int NTonic::Note(int index)
{
  int octave = 0;
  int pitch = 0;
  if(index>=0){
      octave = index/octaveScale;
      pitch = index%octaveScale;
    }else{
      octave = (abs(index)/octaveScale)*-1 -1;
      pitch = octaveScale - (index*-1)%octaveScale;
    }
  return baseNote + octave*OCTAVE_CNT + curMode[pitch];
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
