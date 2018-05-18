#include "algomuse.h"
#include "convert3.h"
#include "mozartdicetable.h"

#define GENERAL_MIDI_ON 1
#define PROGRAM_NUMBERS_ON 1
#define PENTATONIC_SCALE 1

#define GENERAL_MIDI_ON 1
#define PROGRAM_NUMBERS_ON 1

#define MIXOLYDIAN_DIATONIC   0
#define MIXOLYDIAN_CHROMATIC  1

#define DORIAN_DIATONIC 2
#define DORIAN_CHROMATIC 3

#define HYPODORIAN_DIATONIC 4
#define HYPODORIAN_CHROMATIC 5

#define PHRYGIAN_DIATONIC 6
#define PHRYGIAN_CHROMATIC 7

#define HYPOPHRYGIAN_DIATONIC 8
#define HYPOPHRYGIAN_CHROMATIC 9

#define LYDIAN_DIATONIC 10
#define LYDIAN_CHROMATIC 11

#define HYPOLYDIAN_DIATONIC 12
#define HYPOLYDIAN_CHROMATIC 1

#define FIRST_DOCHMAIAC 0
#define FIRST_DOCHMAIAC_REVERSED 1
#define FIRST_DOCHMAIAC_AND_REVERSED_COMBINED 2
#define SECOND_DOCHMAIAC 3
#define PAEONIC_WITH_TWO_TROCHAICS 4
#define SPONDEIOS_PLUS_PYRRIC 5
#define PYRRIC_PLUS_SPONDEIOS 6
#define SECOND_BACCHEIOS 7
#define BACCHEIOS 8
#define A_TRIPODIES 9
#define ONE_TETRAPODIES 10
#define SIMPLE_DACTYL 11
#define REVERSE_DACTYL 12
#define SIMPLE_IAMBIC 13
#define SIMPLE_TROCHAICS 14
#define SIMPLE_PAEONIC 15


#define LOW_E_MIDI   52
#define F_MIDI       53
#define F_SHARP_MIDI 54
#define G_MIDI       55
#define G_SHARP_MIDI 56
#define A_MIDI       57
#define A_SHARP_MIDI 58
#define B_MIDI       59
#define C_MIDI       60
#define C_SHARP_MIDI 61
#define D_MIDI       62
#define D_SHARP_MIDI 63
#define HIGH_E_MIDI  64
#define F_MIDI_SECOND_OCTAVE 65
#define F_SHARP_MIDI_SECOND_OCTAVE 66
#define G_MIDI_SECOND_OCTAVE 67
#define G_SHARP_MIDI_SECOND_OCTAVE 68
#define A_MIDI_SECOND_OCTAVE 69
#define A_SHARP_MIDI_SECOND_OCTAVE 70
#define B_MIDI_SECOND_OCTAVE 71
#define C_MIDI_SECOND_OCTAVE 72
#define C_SHARP_MIDI_SECOND_OCTAVE 73
#define D_MIDI_SECOND_OCTAVE 74
#define D_SHARP_MIDI_SECOND_OCTAVE 75
#define HIGHEST_E_MIDI_SECOND_OCTAVE 76

int melody[64];
int rhythm[64];
int melodic_counter;
int previous_melodic_counter;
int product; //product = temp_rhythmopoeia.repeat_this_cycle * temp_rhythmopoeia.rhythmic_one_cycle_counter_length
int number_of_modes = 14;
int number_of_rhythmic_patterns = 16;
int mode_number;
int rhythm_pattern_number;
//int play_entire_mode_counter = 1;
int mese;
int pivot_note; // 0 to 7


int pentatonic[] = { 45-12, 48-12, 50-12, 52-12, 55-12, 57-12 };
//int program_number[8];

struct mode_stuff
{
  char *ptr;
  int mode_number;
  int tethic_mese;
  int dynamic_mese;
  int pitches[25];
}modes[14], temp_mode;


struct rhythmic_stuff
{
  char *ptr;
  int rhythmic_one_cycle_counter_length;
  int time_length;
  int repeat_this_cycle;
  int rhythmic_unit[10];
}rhythmopoeia[16], temp_rhythmopoeia;



AlgoMuse::AlgoMuse()
{
  time_t t;
  srand ((unsigned) time (&t));
}

void AlgoMuse::play_notes()
{
  int counter;
  int volume = 127;
  int note[8];
  int i, j[8];
  int channel[] = { 144, 145, 146, 147, 148, 149, 150, 151};
  /* need as many channel arrays as layers */
  for(int i = 0;i<8;i++){
      program_number[i] = 14;//tubular bells
    }

#if PROGRAM_NUMBERS_ON
  program_setup ();
#endif

  counter = 0;
  do
    {
      for (i = 0; i < 7; ++i)
        {
          note[i] = rand () % 6;
          note[i] = (pentatonic[note[i]]) + octave;
          j[i] = rand () % 8;
          play (0, channel[j[i]], note[i], volume);
          play (rand () % (600) + 1, 152 - 16, 60, 0);
        }
      play (200, 152 - 16, 60, 0);
      for (i = 0; i < 7; ++i)
        play (0, channel[j[i]] - 16, note[i], 0);
      ++counter;
    }
  while (counter < 7);
}

void AlgoMuse::PlayWindChime()
{
  open_midfiles ();
  general_midi ();
  play (48 * 2 * 4, 152 - 16, 100, 0);	/* Handshake */
  play_notes ();
  close_midfiles ();
}

void AlgoMuse::PlayGreekMusic()
{

}

void AlgoMuse::PlayMozartDiceGame()
{
  int i, m, j, k, p;
  /* Write all eighth notes as sixteenth*/
  /* notes followed by sixteenth rest (-1).*/
  /* Also Quarter notes as Sixteenth note*.
/* and three sixteenth rests -1-1-1 */
  /* Play command then is (0,148,pitch,100)*/
  /* then (length*tempo,148-16,same pitch,0)*/
  /* then next note. and if no note (0,148-16,pitch =1,0)*/
  /* followed by length*temp[,148-16,1.0) */
  time_t t;
  open_midfiles ();
#if GENERAL_MIDI_ON
  general_midi ();
#endif
  srand ((unsigned) time (&t));
  for (i = 0; i < 8; ++i)
    program_number[i] = 0;
  program_setup ();
  int tempo = 48;
  play (48 * 2 * 4, 152 - 16, 100, 0);	/* Handshake */
  for (m = 0; m < MEASURES; ++m)
    {
      j = rand () % ALTERNATES;
      {
        for (p = 0; p < PITCHES; ++p)
          {
            if (measure[m][j][0][p] != -1)
              play (0, 148, measure[m][j][0][p], 100);
            if (measure[m][j][1][p] != -1)
              play (0, 148, measure[m][j][1][p], 100);
            if (measure[m][j][2][p] != -1)
              play (0, 148, measure[m][j][2][p], 100);

            play (tempo, 152 - 16, 100, 100);

            if (measure[m][j][0][p] != -1)
              play (0, 148 - 16, measure[m][j][0][p], 0);
            if (measure[m][j][1][p] != -1)
              play (0, 148 - 16, measure[m][j][1][p], 0);
            if (measure[m][j][2][p] != -1)
              play (0, 148 - 16, measure[m][j][2][p], 0);
          }
      }
    }
  close_midfiles ();
}
