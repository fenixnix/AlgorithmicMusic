#ifndef ALGOMUSE_H
#define ALGOMUSE_H

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include "nmotivictune.h"

using namespace std;

class AlgoMuse
{
public:
  AlgoMuse();
  void PlayWindChime();
  void PlayGreekMusic();
  void PlayMozartDiceGame();
  void PlayMotivic();
private:
  int octave = 24;
  NMidi midi;
  NMotivicTune motivic;
};

#endif // ALGOMUSE_H
