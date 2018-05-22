#ifndef NCHORD_H
#define NCHORD_H

#include "ntonic.h"

class NChord
{
public:
    NChord(int baseNote = MID_C, MODE mode = MAJOR);
    void SetBase(int note);
    void SetMode(MODE mode);
    void SetLevel(int lv);
    vector<int> Chord(int index);

private:
    NTonic tonic;
    std::vector<int> curMode;
    int level = 3;

};

#endif // NCHORD_H
