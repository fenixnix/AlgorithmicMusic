#ifndef NMOTIVICTUNE_H
#define NMOTIVICTUNE_H

#include "ntune.h"
#include "nmidiauther.h"

class NMotivicTune
{
public:
    NMotivicTune();
    void m001Beginning();
    void m002ShortSilence();
    void m003Mod(int index);

    void Test();
private:
    NTune tune;
    NMidiAuther midi;
    int tempo = 48;
};

#endif // NMOTIVICTUNE_H
