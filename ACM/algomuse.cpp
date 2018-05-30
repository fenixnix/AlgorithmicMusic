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
    initAllMode();
}

void AlgoMuse::PlayWindChime()
{
#define BASENOTE 57
    midi.Open();
    midi.tracks[0].Wait(48*2*4);	/* Handshake */
    int pentatonic[] = { BASENOTE , BASENOTE +3 , BASENOTE + 5, BASENOTE +7 , BASENOTE +10, BASENOTE +12 };
    int volume = 0x7f;
    int note[8];
    int j[8];
    /* need as many channel arrays as layers */
    int ins[] = {14,14,14,14,14,14,14,14};
    midi.tracks[0].instrumentsSetup(ins);

    for(int k = 0;k<8;k++){
        for (int i = 0; i < 7; ++i)
        {
            note[i] = rand () % 6;
            note[i] = (pentatonic[note[i]]);
            j[i] = rand () % 8;

            midi.tracks[0].SetChannel(j[i]);
            midi.tracks[0].On(note[i], volume);
            midi.tracks[0].Wait(rand () % (600) + 1);
        }
        midi.tracks[0].Wait(200);

        for (int i = 0; i < 7; ++i){
            midi.tracks[0].SetChannel(j[i]);
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
                    auto pitch= measure[m][j][i][p];
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
        midi.tracks[4].Play(measure[m][j][0][0]+0-12,tempo*6,0x30);
    }
    midi.Close();
}

void AlgoMuse::PlayMotivic()
{
    motivic.Test();
}

void AlgoMuse::ChordTest()
{
    initAllMode();
    midi.Open();
    int tempo = 48;


    midi.tracks[0].SetInstrument(0,0);
    midi.tracks[0].Wait(tempo*2*4);

    //midi.tracks[0].PlayTune(60);

    NMidiTrack *mainTrack = &midi.tracks[0];


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

    NTonic tonic;
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


    //tonic.SetMode(0);
    midi.tracks[0].Play(tempo*4,tonic.Note(0)-12);
    midi.tracks[0].Play(tempo*4,tonic.Note(3)-12);
    midi.tracks[0].Play(tempo*4,tonic.Note(4)-12);
    midi.tracks[0].Play(tempo*4,tonic.Note(0)-12);


    midi.tracks[0].Chord(tempo*4,tonic.Note(0-7));
    midi.tracks[0].Chord(tempo*4,tonic.Note(3-7));
    midi.tracks[0].Chord(tempo*4,tonic.Note(4-7),major,4);
    midi.tracks[0].Chord(tempo*4,tonic.Note(0-7));


    midi.tracks[0].Chord2(tempo*4,tonic.Note(0));

    for(int i = 0;i<4;i++){
        midi.tracks[0].Play(tempo/2,tonic.Note(i));
    }


    midi.tracks[0].Chord2(tempo*4,tonic.Note(-2));
    for(int i = 0;i<4;i++){
        midi.tracks[0].Play(tempo/2,tonic.Note(-2+i));
    }

    midi.tracks[0].Chord2(tempo*4,tonic.Note(3));
    for(int i = 0;i<4;i++){
        midi.tracks[0].Play(tempo/2,tonic.Note(3+i));
    }

    midi.tracks[0].Chord2(tempo*4,tonic.Note(4));
    for(int i = 0;i<4;i++){
        midi.tracks[0].Play(tempo/2,tonic.Note(4+i));
    }

    midi.tracks[0].Chord2(tempo*4,tonic.Note(0));

    for(int i = 0;i<4;i++){
        midi.tracks[0].Play(tempo/2,tonic.Note(i));
    }

    midi.tracks[0].Wait(tempo*6);

    midi.tracks[0].Chord(tempo*4,tonic.Note(-2));
    midi.tracks[0].Chord(tempo*4,tonic.Note(1));
    midi.tracks[0].Chord(tempo*4,tonic.Note(-3));
    midi.tracks[0].Chord(tempo*4,tonic.Note(0));

    midi.tracks[0].Wait(tempo*6);

    midi.tracks[0].Chord(tempo*4,tonic.Note(1),minor,4);
    midi.tracks[0].Chord(tempo*4,tonic.Note(-3),mixolydian,4);
    midi.tracks[0].Chord(tempo*4,tonic.Note(0),mixolydian,4);
    midi.tracks[0].Chord(tempo*4,tonic.Note(-2),minor,4);

    midi.tracks[0].Wait(tempo*6);

    midi.tracks[0].Chord(tempo*4,tonic.Note(-3));
    midi.tracks[0].Chord(tempo*4,tonic.Note(1));
    midi.tracks[0].Chord(tempo*4,tonic.Note(-2));
    midi.tracks[0].Chord(tempo*4,tonic.Note(0));

    for(int i = 0;i<8;i++){
        for(int j = 0;j<8;j++){
            midi.tracks[0].Play(tempo/2,tonic.Note(i+j));
        }
    }
    tonic.SetMode(MINOR);
    for(int i = 0;i<8;i++){
        for(int j = 0;j<8;j++){
            midi.tracks[0].Play(tempo/2,tonic.Note(i+j));
        }
    }

    //  for(int i = 0;i<8;i++){
    //      midi.tracks[0].Play(tempo*4,0,ModeTune(i,mixolydian));
    //      for(int j = 0;j<5;j++){
    //          midi.tracks[0].Play(tempo,0,ModeTune((i+j)*2,major));
    //        }
    //      for(int j = 3;j>=0;j--){
    //          midi.tracks[0].Play(tempo,0,ModeTune((i+j)*2,major));
    //        }
    //      midi.tracks[0].Chord(tempo,0,ModeTune(i,mixolydian),major,3);
    //    }

    //  for(int i = 0;i<8;i++){
    //      midi.tracks[0].Chord(tempo,0,ModeTune(i,major),major,3);
    //    }

    //  for(int i = 0;i<8;i++){
    //      midi.tracks[0].Chord(tempo*2,0,ModeTune(i,dorian),dorian,3);
    //    }

    //  for(int i = 0;i<8;i++){
    //      midi.tracks[0].Chord(tempo*2,0,ModeTune(i,phrygian),phrygian,3);
    //    }

    //  for(int i = 0;i<8;i++){
    //      midi.tracks[0].Chord(tempo*2,0,ModeTune(i,lydian),lydian,3);
    //    }

    //  for(int i = 0;i<8;i++){
    //      midi.tracks[0].Chord(tempo*2,0,ModeTune(i,mixolydian),mixolydian,3);
    //    }

    for(int i = 0;i<8;i++){
        midi.tracks[0].Chord(tempo,ModeTune(i,minor),minor,3);
    }

    //  for(int i = 0;i<8;i++){
    //      midi.tracks[0].Chord(tempo*2,0,ModeTune(i,locrian),locrian,3);
    //    }

    midi.Close();
}
