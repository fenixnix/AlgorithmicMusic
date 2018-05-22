#ifndef NTUNEMODE_H
#define NTUNEMODE_H

#include <iostream>

using namespace std;

#define OCTAVE_CNT 12
#define MID_C 60
#define NumOfScale 7

static char allMode[NumOfScale][NumOfScale];
static char chord[] = {0,1,2,4,6,8,10,12};
static void initAllMode(){
  char baseMode[] = {2,2,1,2,2,2,1};
  for(int j = 0;j<NumOfScale;j++){
      allMode[j][0] = 0;
      for(int i = 0;i<NumOfScale-1;i++){
          allMode[j][i+1] = allMode[j][i]+baseMode[i];
        }
      int tmp = baseMode[0];
      for(int i = 0;i<NumOfScale-1;i++){
          baseMode[i] = baseMode[i+1];
        }
      baseMode[6] = tmp;
    }
}

#define ionian allMode[0]
#define dorian allMode[1]
#define phrygian allMode[2]
#define lydian allMode[3]
#define mixolydian allMode[4]
#define aeolian allMode[5]
#define locrian allMode[6]

#define major ionian
#define minor aeolian

static void PrintAllMode(){
  cout<<"All Mode:"<<endl;
  for(int j = 0;j<NumOfScale;j++){
      for(int i = 0;i<NumOfScale;i++){
          cout<<(int)allMode[j][i]<<",";
        }
      cout<<endl;
    }
}

static char ModeTune(int tune,char mode[]){
  int size = NumOfScale;
  int oct = tune/size;
  int pitch = tune%size;
  return MID_C + OCTAVE_CNT*oct + mode[pitch];
}

static char Major(int tune){
  return ModeTune(tune, major);
}

static char Minor(int tune){
  return ModeTune(tune, minor);
}

#endif // NTUNEMODE_H
