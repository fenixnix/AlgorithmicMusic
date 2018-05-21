#include "nMidiTrack.h"

NMidiTrack::NMidiTrack()
{

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

void NMidiTrack::instrumentsSetup(int program[])
{
    for (int i = 0; i < sizeof(program); ++i)
    {
        cout<<"CH:"<<i<<" Set:"<<program[i]<<endl;
        SetInstrument(i,program[i]);
    }
}

#include "nMidi.h"
void NMidiTrack::Message(unsigned long l, int c, int p, int v)
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
    writeByte(c);
    writeByte(p);
    writeByte(v);
}

void NMidiTrack::Play(unsigned long l, int c, int p, int v)
{
    On(c,p,v);
    Message(l,c+0x80,p);
}

void NMidiTrack::Beat(unsigned long l, int p, int v)
{
    On(9,p,v);
    Message(l,0x89,p);
}

void NMidiTrack::On(int c, int p, int v)
{
    Message(0,c+0x90,p,v);
}

void NMidiTrack::Off(int c, int p)
{
    Message(0,c+0x80,p);
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
