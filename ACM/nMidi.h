#ifndef NMIDIAUTHER_H
#define NMIDIAUTHER_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <ostream>

#include "percussionsound.h"

#define WAITNOTE 0x88
#define MID_C 60

using namespace std;

class NMidi
{
public:
  NMidi();
  void Open(int trackCount = 1);
  void Close();
  void SetInstrument(int ch, int type);
  void instrumentsSetup(int program[]);
  void Message(unsigned long int l, int c = WAITNOTE, int p = MID_C, int v = 0x7f);
  void Play(unsigned long int l, int c = WAITNOTE, int p = MID_C, int v = 0x7f);
  void Beat(unsigned long int l, int p, int v = 0x7f);
  void On(int c = 0, int p = MID_C, int v = 0x7f);
  void Off(int c = 0, int p = MID_C);
  void Wait(unsigned long int l);

  static void SelfTest();

private:

  void writeByte(unsigned char byteData);
  void writeMidiHeader(ofstream &file);
  void writeTrackHeader(ofstream &file);
  void createMidiFile(const char* fileName);

  vector<ostringstream> dats;
};

#endif // NMIDIAUTHER_H
