#ifndef NTONIC_H
#define NTONIC_H

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
  int Note(int index);

private:
  static int modes[OCTAVE_SCALE][OCTAVE_SCALE];
  int mode = 0;
  void initMode();
  int baseNote = MID_C;
};

#endif // NTONIC_H
