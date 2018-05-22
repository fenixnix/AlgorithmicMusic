#ifndef NMIDITRACK_H
#define NMIDITRACK_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <ostream>

#include "ntunemode.h"
#include "nTonic.h"
#include "percussionsound.h"

#define WAITNOTE 0x88

using namespace std;

class NMidiTrack
{
public:
    NMidiTrack();
    void Open();
    void Close();
    void SetInstrument(int ch, int type);
    void instrumentsSetup(int program[]);
    void Message(unsigned long int l, int c = WAITNOTE, int p = MID_C, int v = 0x7f);
    void Play(unsigned long int l, int c = WAITNOTE, int p = MID_C, int v = 0x7f);
    void Chord(unsigned long int l, int c = WAITNOTE, int p = MID_C, char* mode = ionian, int level = 3, int v = 0x7f);
    void Chord2(unsigned long int l, int c = WAITNOTE, int p = MID_C, int v = 0x7f);
    void Beat(unsigned long int l, int p, int v = 0x7f);
    void On(int c = 0, int p = MID_C, int v = 0x7f);
    void Off(int c = 0, int p = MID_C);
    void Wait(unsigned long int l);
    string Data();
private:
    ostringstream data;
    void writeByte(unsigned char byteData);
};

#endif // NMIDITRACK_H
