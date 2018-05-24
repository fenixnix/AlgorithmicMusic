#include "nTonic.h"
#include <math.h>
#include <iostream>

using namespace std;

int ChinaScale[] = {0,2,4,7,9};
int China2Scale[] = {0,3,5,7,10};
int Japan1Scale[] = {0,4,5,9,11};//日本音阶
int Japan2Scale[] = {0,4,5,7,11};
int GypsyScale[] = {0,3,6,7,8,10};//吉普赛音阶（Gypsy）
int OriScale[] = {0,1,4,5,6,9,10};//东方音阶
int ArabicScale[] = {1,2,4,6,7,9,11};//阿拉伯音阶
int Arabic2Scale[] = {0,1,4,5,7,8,10};
int FlamencoScale[] = {0,1,4,6,7,8,10};//弗拉门戈音阶
int HinduScale[] = {0,2,4,5,7,8,10};//印度音阶
int HungarianScale[] = {0,3,4,6,7,9,10};//匈牙利音阶
int HungarianMinorScale[] = {0,2,3,6,7,8,11};//匈牙利音阶小调
int RussiaScale[] = {0,2,4,5,6,7,8,9,10,11};//俄罗斯音阶
int NapoliScale[] = {0,1,3,5,7,9,11};
int NapoliMinorScale[] = {0,1,3,5,7,8,11};
int LydianDominant[] = {0,2,4,6,7,9,10};//大利底亚音阶
int SuperLocrianp[] = {0,1,3,4,6,8,10};//超级洛克里亚音阶

int BlusScale[] = {0,3,5,6,7,10};//布鲁斯音阶
int MixelBluesScale[] = { 0,3,4,5,6,7,10};//混合布鲁斯音阶
int JazzMinor[] = {0,2,3,5,7,9,11};//爵士小调音阶：

int scale0[] = {0,2,4,6,8,9,11};//和声小调
int scale1[] = {0,2,3,5,6,8,10};//减音阶
int scale2[] = {0,1,3,4,6,7,9,10};//半—全减音阶
int scale3[] = {0,2,4,6,8,10};//全音音阶


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
    SetMode(RussiaScale,10);
}

int NTonic::Note(int index)
{
    int octave = 0;
    int pitch = 0;
    if(index>=0){
            octave = index/octaveScale;
            pitch = index%(octaveScale);
        }else{
            int absIndex = abs(index);
            octave = (absIndex/octaveScale)*-1 -1;
            pitch = octaveScale - absIndex%octaveScale;
        }
    int note = baseNote + octave*OCTAVE_CNT + curMode[pitch%octaveScale];
    if(pitch==octaveScale){
            note += OCTAVE_CNT;
        }
    return note;
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
