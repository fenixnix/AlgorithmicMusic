#include "nMidiTrack.h"

NMidiTrack::NMidiTrack()
{
    initAllMode();
    tunes = vector<int>{0,1,2,3,4,5,6,7};
    intervals = vector<int>{48,24,24,24,32,28,24,20};
    levels = vector<int>{40,50,60,70,80,90,100,110};
}

NMidiTrack::NMidiTrack(int channel)
{
    NMidiTrack();
    SetChannel(channel);
}

void NMidiTrack::Open()
{
    //track header
    char buff[] = {0,0xf0,5,0x7e,0x7f,9,1,0xf7};
    data.write(buff,sizeof(buff));
}

void NMidiTrack::Close()
{
    //track tail
    char buff[] = { 0, 0xff, 0x2f, 0};
    data.write(buff,4);
}

void NMidiTrack::SetInstrument(int ch, int type)
{
    writeByte(0);
    writeByte(0xC0+ch);
    writeByte(type);
}

void NMidiTrack::SetChannel(int channel)
{
    this->channel = channel;
}

void NMidiTrack::SetTempo(unsigned long tempo)
{
    this->tempo = tempo;
}

void NMidiTrack::SetVolume(int volume)
{
    this->volume = volume;
}

void NMidiTrack::instrumentsSetup(int program[])
{
    for (int i = 0; i < sizeof(program); ++i)
        {
            cout<<"CH:"<<i<<" Set:"<<program[i]<<endl;
            SetInstrument(i,program[i]);
        }
}

#include "nMidi.h"
void NMidiTrack::Message(unsigned long l,int channel, int p, int v)
{
    unsigned long number;
    unsigned char varbyte[4];
    unsigned char byte[4];
    number = l;
    NMidi::long2hexs (number, byte);
    NMidi::hexbyte_varbyte (byte, varbyte);

    //  for(int i = 0;i<4;i++){
    //      cout<<"V:"<<l<<"|"<<(int)varbyte[0]<<"*"<<(int)varbyte[1]<<"*"<<(int)varbyte[2]<<"*"<<(int)varbyte[3]<<endl;
    //    }

    if (varbyte[0] == 0 && varbyte[1] == 0 && varbyte[2] == 0)
        {
            writeByte(varbyte[3]);
        }
    else if (varbyte[0] == 0 && varbyte[1] == 0)
        {
            writeByte(varbyte[2]);
            writeByte(varbyte[3]);
        }
    else if (varbyte[0] == 0)
        {
            writeByte(varbyte[1]);
            writeByte(varbyte[2]);
            writeByte(varbyte[3]);
        }
    else
        {
            writeByte(varbyte[0]);
            writeByte(varbyte[1]);
            writeByte(varbyte[2]);
            writeByte(varbyte[3]);
        }
    writeByte(channel);
    writeByte(p);
    writeByte(v);
}

void NMidiTrack::Play(int p, unsigned long l, int v)
{
    On(p,v);
    Message(l,channel+0x80,p);
}

void NMidiTrack::Note(int note, unsigned long tempo, int lv)
{
    this->tempo = tempo;
    this->volume = lv;
    int pitch = tonic.Note(note);
    On(pitch, lv);
    Message(tempo, channel+0x80, pitch);
}

void NMidiTrack::Note(int note, unsigned long tempo)
{
    Note(note,tempo,volume);
}

void NMidiTrack::Note(int note)
{
    Note(note,tempo);
}

void NMidiTrack::PlayTune(int startPitch)
{
    tonic.SetBase(startPitch);
    for(int i = 0;i<tunes.size();i++){
        Note(tunes[i],intervals[i],levels[i]);
    }
}

void NMidiTrack::Chord(unsigned long l, int p, char *mode, int level, int v)
{
    for(int i = 0;i<level;i++){
            On(p+mode[i*2],v);
            //cout<<(int)mode[i*2]<<"*";
        }
    //cout<<endl;
    Wait(l);
    for(int i = 0;i<level;i++){
            Off(p+mode[i*2]);
        }
}

void NMidiTrack::Chord2(unsigned long l, int p, int v)
{
    On(p,v);
    On(p+4,v);
    On(p+7,v);
    //On(c,p+11,v);

    Wait(l);

    Off(p);
    Off(p+4);
    Off(p+7);
    //Off(c,p+11);
}

void NMidiTrack::Beat(int p, unsigned long l, int v)
{
    Message(0,0x99,p);
    Message(l,0x89,p);
}

void NMidiTrack::RandomTune()
{
    tunes = vector<int>{0,0,5,2,3};
    intervals = vector<int>{72+48,48,48,48,72*2,28,24,20};
    levels = vector<int>{40,50,60,70,80,90,100,110};
}

void NMidiTrack::On(int p, int v)
{
    Message(0,channel+0x90,p,v);
}

void NMidiTrack::Off(int p)
{
    Message(0,channel+0x80,p);
}

void NMidiTrack::Wait(unsigned long l)
{
    Message(l,WAITNOTE);
}

string NMidiTrack::Data()
{
    return data.str();
}

void NMidiTrack::writeByte(unsigned char byteData)
{
    char t = byteData;
    data.write(&t,1);
}
