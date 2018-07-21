#ifndef NTRACK_H
#define NTRACK_H

#include <vector>
#include <string>
#include <sstream>

#include "ntonic.h"
#include "percussionsound.h"

#define WAITNOTE 0x88

using namespace std;

class NTrack
{
public:
  NTrack();

  void Play(int note,int duration, int volume = 127);

  void On(int note, int volume = 127);
  void Off(int note);
  void Wait(int duration);

  vector<string> GetData();

private:
  vector<string> msgQueue;
};

#endif // NTRACK_H
