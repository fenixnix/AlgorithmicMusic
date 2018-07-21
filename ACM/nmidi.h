#ifndef NMIDIAUTHER_H
#define NMIDIAUTHER_H

#include "nmiditrack.h"

class NMidi
{
public:
  NMidi();
  void Open(int trackCount = 1);
  void Close();

  static void long2hexs (unsigned long d, unsigned char byte[4]);
  static void hexbyte_varbyte (unsigned char byte[4], unsigned char varbyte[4]);
  static void SelfTest();
    vector<NMidiTrack> tracks;
private:
  void writeMidiHeader(ofstream &file);
  void writeTrackHeader(ofstream &file);
  void createMidiFile(const char* fileName);
};

#endif // NMIDIAUTHER_H
