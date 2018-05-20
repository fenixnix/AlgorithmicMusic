#include "nmotivictune.h"

int channel[8] = { 144, 145, 146, 147, 148, 149, 149, 149 };
int instruments[8] = {73,46,61,48,0,0,0,0};
int sounds[2][4];

NMotivicTune::NMotivicTune()
{

}

void NMotivicTune::m002ShortSilence()
{
    midi.Wait(tempo*2);
}

void NMotivicTune::m003Mod(int index)
{
    if(index == 0){
        for(int i = 0;i<tune.inver.size();i++){
            midi.Play(tempo,channel[0],tune.inver[i] + MID_C + 12,50);
        }
        for(int i = 0;i<tune.inver.size();i++){
            midi.On(channel[3],tune.inver[i] + 24,90);
            PlayRhythmiCarray();
            midi.Off(channel[3],tune.inver[i] + 24);
        }
    }

    if(index == 1){
        auto sounds = tune.RandomSel();
        midi.On(channel[3],tune.base[0]+24,70);

        for(int i = 0;i<tune.base.size();i++){
            midi.On(channel[0],tune.base[i]+60,40);
            PlayTune(sounds);
            midi.Off(channel[0],tune.base[i]+60);
        }
        midi.Off(channel[3],tune.base[0]+24);
    }
}

void NMotivicTune::PlayTune(vector<int> tune)
{
    for (int i = 0; i < tune.size(); ++i)
    {
        midi.Play(32*2,channel[3],tune[i]+48,35);
    }
}

int rhythmmarker;
int rhythmmarker1;
int rhythmmarker2;
int rhythmmarker3;
void NMotivicTune::PlayRhythmiCarray(int cnt, int ins)//60,64,50,62 //5,6,7,8  //2*62 2,4,2
{
    vector<bool> rArray;
    for(int i = 0;i<cnt;i++){
        rArray.push_back(rand()%2);
    }
    for (int i = 0; i < rArray.size(); i++)
      {
        if (rArray[i]){
          midi.Play(tempo*2,153,ins);
        }else{
          midi.Wait(tempo*2);
        }
      }
}

void NMotivicTune::m001Beginning()
{
    for(int i = 0;i<tune.base.size();i++){
        midi.Play(tempo*4,channel[0],tune.base[i] + MID_C,50);
    }
    midi.Wait(tempo*4);
    for(int i = 0;i<tune.base.size();i++){
        midi.Play(tempo,channel[0],tune.base[i] + MID_C,50);
    }
    for(int i = 0;i<tune.base.size();i++){
        midi.Play(tempo/2,channel[0],tune.base[i] + MID_C,50);
    }
    for(int i = 0;i<tune.base.size();i++){
        midi.Play(tempo/4,channel[0],tune.base[i] + MID_C,50);
    }
}

void NMotivicTune::Test()
{
    midi.Open("tmp");
    tune.Random(4);
    midi.instrumentsSetup(instruments);
    midi.Wait(tempo);
    //m001Beginning();
    m003Mod(1);
    midi.Close();
}
