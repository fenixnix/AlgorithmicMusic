#ifndef NMOTIVICTUNE_H
#define NMOTIVICTUNE_H

#include "ntune.h"
#include "nMidiAuther.h"

class NMotivicTune
{
public:
    NMotivicTune();
    void m001Beginning();
    void m002ShortSilence();
    void m003Mod(int index);

    void PlayTune(vector<int> tune);
    void PlayBeats(vector<int> beat, vector<int> tempo, vector<int> vol);

    void PlayRhythmiCarray(int cnt = 5,int ins = 60);

    void BeatTest();
    void Test();
private:
    NTune tune;
    NMidiAuther midi;
    int tempo = 48;
};

#endif // NMOTIVICTUNE_H
