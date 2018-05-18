#ifndef NMIDIAUTHER_H
#define NMIDIAUTHER_H

#include <string>
#include <iostream>
#include <sstream>

using namespace std;

class NMidiAuther
{
public:
  NMidiAuther();
  void Open(string fileName);
  void Close();

  static void SelfTest();
private:
  void programSetup();
  void generalMidi();
  void wB2MidFile(unsigned char byteData);

  FILE *midiFile;
  FILE *tmpFile;
  long place = 0L;
  int program_number[8];
};

#endif // NMIDIAUTHER_H
