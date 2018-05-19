#ifndef NMIDIAUTHER_H
#define NMIDIAUTHER_H

#include <string>
#include <iostream>
#include <sstream>

#define WAITNOTE 136
#define MID_C 60

using namespace std;

class NMidiAuther
{
public:
  NMidiAuther();
  void Open(string fileName);
  void Close();
  void instrumentsSetup(int program[8]);
  void Message(unsigned long int l, int c = WAITNOTE, int p = MID_C, int v = 127);
  void Play(unsigned long int l, int c = WAITNOTE, int p = MID_C, int v = 127);
  void On(int c, int p = MID_C, int v = 127);
  void Off(int c, int p);
  void Wait(unsigned long int l);

  static void SelfTest();
private:

  void generalMidi();
  void writeByte(unsigned char byteData);

  static void createMidiFile(const char* fileName,const char* srcFile, long size);

  FILE *datFile;
  unsigned long place = 0L;
  int program_number[8];
};

#endif // NMIDIAUTHER_H
