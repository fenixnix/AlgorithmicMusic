#include "algomuse.h"
#include "mozartdicetable.h"

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
#define BASENOTE 57
int pentatonic[] = {0,3,5,7,10,12};
    midi.Open();
    midi.tracks[0].Wait(96);	/* Handshake */
    midi.tracks[0].SetVolume(0x7f);

    /* need as many channel arrays as layers */
    midi.tracks[0].SetInstrument(0,14);

    int note[8];
    for(int k = 0;k<8;k++){
        for (int i = 0; i < 7; ++i)
        {
            note[i] = (pentatonic[rand () % 6]+ BASENOTE);
            midi.tracks[0].On(note[i]);
            midi.tracks[0].Wait(rand () % (600) + 1);
        }
        midi.tracks[0].Wait(200);

        for (int i = 0; i < 7; ++i){
            midi.tracks[0].Off(note[i]);
        }
    }
    midi.Close();
}

void AlgoMuse::PlayMozartDiceGame()
{
    midi.Open(5);
    int tempo = 48;

    for(int i = 0;i<5;i++){
        midi.tracks[i].SetInstrument(i,6);
        midi.tracks[i].Wait(tempo*2*4);
        midi.tracks[i].SetChannel(i);
    }
    midi.tracks[4].SetInstrument(4,19);

    for (int m = 0; m < MEASURES; ++m)
    {
        int j = rand () % ALTERNATES;
        {
            for (int p = 0; p < PITCHES; ++p)
            {
                for(int i = 0;i<3;i++){
                    auto pitch= mozart[m][j][i][p];
                    if(pitch!=-1){
                        midi.tracks[i].Play(pitch, tempo, 80);
                    }else{
                        midi.tracks[i].Wait(tempo);
                    }
                }
                if(p%6 == 0){
                    midi.tracks[3].Beat(Bass_Drum, tempo);
                }else{
                    if(p%2 == 0){
                        midi.tracks[3].Beat(Elec_Snare, tempo, 0x40);
                    }else{
                        midi.tracks[3].Beat(Closed_HH, tempo, 0x40);
                    }
                }
            }
        }
//        midi.tracks[4].Play(measure[m][j][0][0]+7-5,tempo*2,0x30);
//        midi.tracks[4].Play(measure[m][j][0][0]+4-5,tempo*2,0x30);
        midi.tracks[4].Play(mozart[m][j][0][0]+0-12,tempo*6,0x30);
    }
    midi.Close();
}

void AlgoMuse::PlayMotivic()
{
    motivic.Test();
}

void AlgoMuse::TonicTest(string mode)
{
    midi.Open();
    int tempo = 48;


    midi.tracks[0].SetInstrument(0,0);
    midi.tracks[0].Wait(tempo*2*4);

    //midi.tracks[0].PlayTune(60);

    NMidiTrack *mainTrack = &midi.tracks[0];
    mainTrack->SetTempo(24);
    mainTrack->tonic.SetMode(mode);

    for(int i = 0;i<15;i++){
        mainTrack->Note(i);
      }

    for(int i = 15;i>-15;i--){
        mainTrack->Note(i);
      }

/*
    mainTrack->RandomTune();
    mainTrack->PlayTune(0+60);
    mainTrack->Wait(12);
    mainTrack->PlayTune(5+60);
    mainTrack->Wait(12);
    mainTrack->PlayTune(2+60);
    mainTrack->Wait(12);
    mainTrack->PlayTune(3+60);
    mainTrack->PlayTune(0+60);
    mainTrack->Wait(12);
    mainTrack->PlayTune(5+60);
    mainTrack->Wait(12);
    mainTrack->PlayTune(2+60);
    mainTrack->Wait(12);
    mainTrack->PlayTune(3+60);

    midi.tracks[0].Wait(tempo*6);

    //NTonic tonic;
    midi.tracks[0].Play(70,tempo*2);
    midi.tracks[0].Play(71,tempo/2);
    midi.tracks[0].Play(70,tempo/2);
    midi.tracks[0].Play(68,tempo/2);

    midi.tracks[0].Play(70,tempo*2);
    midi.tracks[0].Play(68,tempo);
    midi.tracks[0].Play(70,tempo/2);
    midi.tracks[0].Play(71,tempo/2);
    midi.tracks[0].Play(73,tempo/2);

    midi.tracks[0].Wait(tempo*6);



    for(int i = 0;i<8;i++){
        midi.tracks[0].Chord(tempo,ModeTune(i,minor),minor,3);
    }
    */
    midi.Close();
}
