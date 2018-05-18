#ifndef ALGOMUSE_H
#define ALGOMUSE_H

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <iostream>

using namespace std;

class AlgoMuse
{
public:
  AlgoMuse();

  void play_notes();

  void PlayWindChime();
  void PlayGreekMusic();
  void PlayMozartDiceGame();
private:
  int octave = 24;

};

#endif // ALGOMUSE_H
