#include "algomuse.h"
#include "mozartdicetable.h"
//#include "convert3.h"

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

void AlgoMuse::PlayWindChime()
{
    midi.Open();
    midi.tracks[0].Wait(48*2*4);	/* Handshake */
    int pentatonic[] = { 45-12, 48-12, 50-12, 52-12, 55-12, 57-12 };
    int counter;
    int volume = 127;
    int note[8];
    int j[8];
    int channel[] = { 144, 145, 146, 147, 148, 149, 150, 151};
    /* need as many channel arrays as layers */
    int ins[] = {14,14,14,14,14,14,14,14};
    midi.tracks[0].instrumentsSetup(ins);

    counter = 0;
    do
    {
        for (int i = 0; i < 7; ++i)
        {
            note[i] = rand () % 6;
            note[i] = (pentatonic[note[i]]) + octave;
            j[i] = rand () % 8;

            midi.tracks[0].On(j[i], note[i], volume);
            midi.tracks[0].Wait(rand () % (600) + 1);
        }
        midi.tracks[0].Message(200, 152 - 16, 60, 0);

        for (int i = 0; i < 7; ++i)
            midi.tracks[0].Off(j[i], note[i]);
        ++counter;
    }
    while (counter < 7);
    midi.Close();
}

void AlgoMuse::PlayGreekMusic()
{

}

void AlgoMuse::PlayMozartDiceGame()
{
    midi.Open(3);
    int tempo = 48;

    for(int i = 0;i<3;i++){
        midi.tracks[i].SetInstrument(i,6);
        midi.tracks[i].Wait(tempo*2*4);
    }

    for (int m = 0; m < MEASURES; ++m)
    {
        int j = rand () % ALTERNATES;
        {
            for (int p = 0; p < PITCHES; ++p)
            {
                for(int i = 0;i<midi.tracks.size();i++){
                    auto pitch= measure[m][j][i][p];
                    if(pitch!=-1){
                        midi.tracks[i].Play(tempo,i,pitch);
                    }else{
                        midi.tracks[i].Wait(tempo);
                    }
                }
            }
        }
    }
    midi.Close();
}

void AlgoMuse::PlayMotivic()
{
    motivic.Test();
}
