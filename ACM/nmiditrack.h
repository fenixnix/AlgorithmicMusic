#ifndef NMIDITRACK_H
#define NMIDITRACK_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <ostream>

#include "ntonic.h"
#include "percussionsound.h"

#define WAITNOTE 0x88

using namespace std;

class NMidiTrack
{
public:
    NMidiTrack();
    NMidiTrack(int channel);
    void Open();
    void Close();
    void SetInstrument(int ch, int type);
    void SetChannel(int channel);
    void SetTempo(unsigned long tempo);
    void SetVolume(int volume);
    void instrumentsSetup(int program[]);

    void Play(int p = MID_C, unsigned long int tempo = 48, int v = 0x7f);
    void Note(int note,unsigned long int tempo,int lv);
    void Note(int note,unsigned long int tempo);
    void Note(int note);
    void PlayTune(int startPitch = 60);
    void Beat(int p, unsigned long int l, int v = 0x7f);

    void RandomTune();

//    void Chord(unsigned long int l, int p = MID_C, char* mode = ionian, int volume = 3, int v = 0x7f);
//    void Chord2(unsigned long int l, int p = MID_C, int v = 0x7f);

    void On(int p = MID_C, int v = 0x7f);
    void Off(int p = MID_C);
    void Wait(unsigned long int l);
    void Message(unsigned long int l, int channel, int p = MID_C, int v = 0x7f);
    string Data();

    NTonic tonic;
private:
    ostringstream data;    
    void writeByte(unsigned char byteData);

    int channel = 0;
    unsigned long int tempo = 48;
    int volume = 0x7f;

    vector<int> tunes;
    vector<int> intervals;
    vector<int> levels;
};

#endif // NMIDITRACK_H
