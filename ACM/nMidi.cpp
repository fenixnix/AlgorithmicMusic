#include "nMidi.h"

using namespace std;

//#include "convert3.h"

int midiOctave (int pitch);
int midiNote (int pitch);
string noteStr (int pitch);

NMidi::NMidi()
{
  //initAllMode();
  //PrintAllMode();
}

void long2hexs (unsigned long d, unsigned char byte[4])
/* breaks long number up into four bytes. */
{

}

void hexbyte_varbyte (unsigned char byte[4], unsigned char varbyte[4])
/* first it shifts all the bits past the 7th (8th) bit
of each byte */
{

}

void NMidi::Open(int trackCount)
{
    tracks.clear();
    for(int i = 0;i<trackCount;i++){
        tracks.push_back(NMidiTrack());
    }
    tracks[0].Open();
}

void NMidi::Close()
{
    for(int i = 0;i<tracks.size();i++){
        tracks[i].Close();
    }
    createMidiFile("music.mid");
}

void NMidi::long2hexs(unsigned long d, unsigned char byte[])
{
    unsigned long temp;
    temp = d;
    temp = temp >> 8 * 3;
    byte[0] = (unsigned char) temp;
    temp = d;
    temp = temp << 8;
    temp = temp >> 8 * 3;
    byte[1] = (unsigned char) temp;
    temp = d;
    temp = temp << 8 * 2;
    temp = temp >> 8 * 3;
    byte[2] = (unsigned char) temp;
    temp = d;
    temp = temp << 8 * 3;
    temp = temp >> 8 * 3;
    byte[3] = (unsigned char) temp;
}

void NMidi::hexbyte_varbyte(unsigned char byte[], unsigned char varbyte[])
{
    unsigned char oldbuffer;
    unsigned char newbuffer;
    unsigned char temp1;
    oldbuffer = (unsigned char) (byte[3] >> 7);
    temp1 = byte[3];
    temp1 = (unsigned char) (temp1 << 1);
    temp1 = (unsigned char) (temp1 >> 1);
    varbyte[3] = temp1;

    newbuffer = (unsigned char) (byte[2] >> 6);
    temp1 = byte[2];
    temp1 = (unsigned char) (temp1 << 2);
    temp1 = (unsigned char) (temp1 >> 1);
    temp1 = temp1 | oldbuffer;
    oldbuffer = newbuffer;
    varbyte[2] = temp1;

    newbuffer = (unsigned char) (byte[1] >> 5);
    temp1 = byte[1];
    temp1 = (unsigned char) (temp1 << 3);
    temp1 = (unsigned char) (temp1 >> 1);
    temp1 = temp1 | oldbuffer;
    oldbuffer = newbuffer;
    varbyte[1] = temp1;

    /* newbuffer = (unsigned char) byte[0] >> 4; */
    temp1 = byte[0];
    temp1 = (unsigned char) (temp1 << 4);
    temp1 = (unsigned char) (temp1 >> 1);
    temp1 = temp1 | oldbuffer;
    /* oldbuffer = newbuffer; */
    varbyte[0] = temp1;

    /* now set the 7th bit */
    if (varbyte[0] > 0)
        varbyte[0] = (unsigned char) (varbyte[0] | 0x80);
    if (varbyte[0] > 0 || varbyte[1] > 0)
        varbyte[1] = (unsigned char) (varbyte[1] | 0x80);
    if (varbyte[0] > 0 || varbyte[1] > 0 || varbyte[2] > 0)
        varbyte[2] = (unsigned char) (varbyte[2] | 0x80);
}

void NMidi::SelfTest()
{
    for(int i = 0;i<12;i++){
        cout<<noteStr(60+i);
        if(i%2){
            cout<<endl;
        }
    }
    cout<<endl;
}

void NMidi::writeMidiHeader(ofstream &file)
{
    file<<"MThd";
    char head[] = { 0, 0, 0, 6, //head Size
                    0, 1,//type
                    0, tracks.size(),//track number
                    0, 96};//divition
    file.write(head,sizeof(head));
}

void NMidi::writeTrackHeader(ofstream &file)
{
    file<<"MTrk";
}

void NMidi::createMidiFile(const char *fileName)
{
    ofstream midFile(fileName,ios_base::out|ios_base::binary);
    writeMidiHeader(midFile);

    for(int i = 0;i<tracks.size();i++){
        string d = tracks[i].Data();
        writeTrackHeader(midFile);
        unsigned char byte[4];
        long2hexs (d.size(), byte);
        midFile.write((char*)byte,4);
        midFile.write(d.data(),d.size());
    }

    midFile.close();
}

int nMidiNote (int pitch)
{
    return pitch % 12;
}

int nMidiOctave (int pitch)
{
    return (int)(pitch / 12);
}

string noteStr (int pitch)
{
    int note = nMidiNote(pitch);
    int octave = nMidiOctave(pitch);
    stringstream ss;
    ss<<octave;
    switch (note)
    {
    case 0: ss<<"C  ";break;
    case 1: ss<<"Db ";break;
    case 2: ss<<"D  ";break;
    case 3: ss<<"Eb ";break;
    case 4: ss<<"E  ";break;
    case 5: ss<<"F  ";break;
    case 6: ss<<"Gb ";break;
    case 7: ss<<"G  ";break;
    case 8: ss<<"Ab ";break;
    case 9: ss<<"A  ";break;
    case 10: ss<<"Bb ";break;
    case 11: ss<<"B  ";break;
    default: ss<<"###";break;
    }
    return ss.str();
}
