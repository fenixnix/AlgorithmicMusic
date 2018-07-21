#ifndef ALGOMUSE_H
#define ALGOMUSE_H

#include <stdlib.h>
//#include <time.h>
#include <stdio.h>
#include <iostream>
#include "ntrack.h"
#include "nmotivictune.h"

using namespace std;

class AlgoMuse
{
public:
    AlgoMuse();

//    void PlayWindChime();
//    void PlayMozartDiceGame();
//    void PlayMotivic();

//    void TonicTest(string mode);

private:
    NMidi midi;
    NMotivicTune motivic;
    NTrack track;
};

#endif // ALGOMUSE_H
