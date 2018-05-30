#ifndef NMUSIC_H
#define NMUSIC_H

#include <string>
#include <vector>
#include <map>

using namespace std;

#define OCTAVE_CNT 12
#define OCTAVE_SCALE 7
#define MID_C 60

class NTonic
{
public:
    NTonic();
    void Init(float base = 261.6f,int div = OCTAVE_CNT);
    void LoadModeFile(string fileName);
    void SetMode(string modeName = "Ionian");
    void SetBasePitch(int pitch);
    vector<string> GetModes();
    int GetModeNoteCnt();

    int PitchFreq(int pitch);
    int NotePitch(int note);
    int NoteFreq(int note);

private:
    float baseFreq = 261.6f;
    int midiBasePitch = MID_C;
    vector<int> freqs;
    vector<int> mode;
};

#endif // NMUSIC_H
