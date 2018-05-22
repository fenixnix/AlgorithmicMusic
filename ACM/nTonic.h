#ifndef NTONIC_H
#define NTONIC_H

#include <vector>

#define OCTAVE_CNT 12
#define OCTAVE_SCALE 7
#define MID_C 60

#define MAJOR IONIAN
#define MINOR AEOLIAN
#define DOMINANT  MIXLYDIAN

enum MODE{IONIAN = 0,DORIAN, PHRYGIAN, LYDIAN, MIXLYDIAN, AEOLIAN, LOCRIAN};

class NTonic
{
public:
    NTonic(int baseNote = MID_C, MODE mode = MAJOR);
    void SetBase(int note);
    void SetMode(MODE mode);
    void SetMode(int array[],int size);
    void SetMode(int i);
    int Note(int index);

private:
    static int modes[OCTAVE_SCALE][OCTAVE_SCALE];
    std::vector<int> curMode;
    void initMode();
    int baseNote = MID_C;
    int octaveCnt = OCTAVE_CNT;
    int octaveScale = OCTAVE_SCALE;
};



#endif // NTONIC_H
