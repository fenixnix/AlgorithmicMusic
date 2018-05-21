#include "nmotivictune.h"

int sounds[2][4];

NMotivicTune::NMotivicTune()
{

}

void NMotivicTune::m002ShortSilence()
{
    midi.tracks[0].Wait(tempo*2);
}

void NMotivicTune::m003Mod(int index)
{
    if(index == 0){
        for(int i = 0;i<tune.inver.size();i++){
            midi.tracks[0].Play(tempo,0,tune.inver[i] + MID_C + 12,50);
        }
        for(int i = 0;i<tune.inver.size();i++){
            midi.tracks[0].On(3,tune.inver[i] + 24,90);
            PlayRhythmiCarray();
            midi.tracks[0].Off(3,tune.inver[i] + 24);
        }
    }

    if(index == 1){
        auto sounds = tune.RandomSel();
        midi.tracks[0].On(3,tune.base[0]+24,70);

        for(int i = 0;i<tune.base.size();i++){
            midi.tracks[0].On(0,tune.base[i]+60,40);
            PlayTune(sounds);
            midi.tracks[0].Off(0,tune.base[i]+60);
        }
        midi.tracks[0].Off(3,tune.base[0]+24);
    }
}

void NMotivicTune::PlayTune(vector<int> tune)
{
    for (int i = 0; i < tune.size(); ++i)
    {
        midi.tracks[0].Play(32*2,3,tune[i]+48,35);
      }
}

void NMotivicTune::PlayBeats(vector<int> beat, vector<int> tempo, vector<int> vol)
{
  for(int i = 0;i<beat.size();i++){
      midi.tracks[0].Beat(tempo[i],beat[i],vol[i]);
    }
}

void NMotivicTune::PlayRhythmiCarray(int cnt, int ins)//60,64,50,62 //5,6,7,8  //2*62 2,4,2
{
    vector<bool> rArray;
    for(int i = 0;i<cnt;i++){
        rArray.push_back(rand()%2);
    }
    for (int i = 0; i < rArray.size(); i++)
      {
        if (rArray[i]){
          midi.tracks[0].Beat(tempo*2,ins);
        }else{
          midi.tracks[0].Wait(tempo*2);
        }
      }
}


void NMotivicTune::BeatTest()
{
  vector<int> beats = {36,42,42,42,36,42,42,42};
  vector<int> tempos = {48,24,12,6,48,24,12,6};
  vector<int> vol = {100,50,50,50,100,50,50,50};

  for(int i = 0;i<8;i++){
      PlayBeats(beats,tempos,vol);
    }


  for(int i = 0;i<8;i++){
      PlayBeats(beats,tempos,vol);
    }


}

void NMotivicTune::m001Beginning()
{
    for(int i = 0;i<tune.base.size();i++){
        midi.tracks[0].Play(tempo*4,0,tune.base[i] + MID_C,50);
    }
    midi.tracks[0].Wait(tempo*4);
    for(int i = 0;i<tune.base.size();i++){
        midi.tracks[0].Play(tempo,0,tune.base[i] + MID_C,50);
    }
    for(int i = 0;i<tune.base.size();i++){
        midi.tracks[0].Play(tempo/2,0,tune.base[i] + MID_C,50);
    }
    for(int i = 0;i<tune.base.size();i++){
        midi.tracks[0].Play(tempo/4,0,tune.base[i] + MID_C,50);
    }
}

void NMotivicTune::Test()
{
    midi.Open();
    tune.Random(12);
    int instruments[] = {73,46,61,48};
    midi.tracks[0].instrumentsSetup(instruments);
    midi.tracks[0].Wait(tempo);
    //m001Beginning();
    BeatTest();
    m003Mod(1);
    midi.Close();
}
