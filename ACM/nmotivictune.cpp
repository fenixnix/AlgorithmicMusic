#include "nmotivictune.h"

int channel[8] = { 144, 145, 146, 147, 148, 149, 149, 149 };
int instruments[8] = {73,46,61,48,0,0,0,0};

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
        for(int i = 0;i<tune.base.size();i++){
            midi.Play(tempo,channel[0],tune.base[i] + 60 + 12,50);
        }
    }
}

void NMotivicTune::m001Beginning()
{
    for(int i = 0;i<tune.base.size();i++){
        midi.Play(tempo*4,channel[0],tune.base[i] + 60,50);
    }
    midi.Wait(tempo*4);
    for(int i = 0;i<tune.base.size();i++){
        midi.Play(tempo,channel[0],tune.base[i] + 60,50);
    }
    for(int i = 0;i<tune.base.size();i++){
        midi.Play(tempo/2,channel[0],tune.base[i] + 60,50);
    }
    for(int i = 0;i<tune.base.size();i++){
        midi.Play(tempo/4,channel[0],tune.base[i] + 60,50);
    }
}

void NMotivicTune::Test()
{
    midi.Open("tmp");
    tune.Random(4);
    midi.instrumentsSetup(instruments);
    midi.Wait(tempo);
    m001Beginning();
    m002ShortSilence();
    midi.Close();
}
