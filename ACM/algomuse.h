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
  void PlayMozartDiceGame();
  void PlayMotivic();
  void ChordTest();
private:
  NMidi midi;
  NMotivicTune motivic;
};

#endif // ALGOMUSE_H
