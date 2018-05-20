#include "nmidiauther.h"
#include <iostream>
#include <fstream>

using namespace std;

//#include "convert3.h"

int midiOctave (int pitch);
int midiNote (int pitch);
string noteStr (int pitch);

NMidiAuther::NMidiAuther()
{

}

void long2hexs (unsigned long d, unsigned char byte[4])
/* breaks long number up into four bytes. */
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

void hexbyte_varbyte (unsigned char byte[4], unsigned char varbyte[4])
/* first it shifts all the bits past the 7th (8th) bit
of each byte */
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

void NMidiAuther::Open(string fileName)
{
  datFile = fopen("tmp","wb");
  place = 0;
  //data header
  unsigned char buffer[] = {0,240,5,126,127,9,1,247};
  fwrite(buffer,1,sizeof(buffer),datFile);
  place += sizeof(buffer);
}

void NMidiAuther::Close()
{
  //data tail
  unsigned char end[] = { 0, 255, 47, 0};
  fwrite(end,1,4,datFile);
  place+=4;
  fclose (datFile);
  //createMidiFile
  createMidiFile("music.mid","tmp",place);
}

void NMidiAuther::Message(unsigned long l, int c, int p, int v)
{
  unsigned long number;
  unsigned char varbyte[4];
  unsigned char byte[4];
  number = l;
  long2hexs (number, byte);
  hexbyte_varbyte (byte, varbyte);

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

void NMidiAuther::Play(unsigned long l, int c, int p, int v)
{
    On(c,p,v);
    Message(l,c-16,p);
}

void NMidiAuther::On(int c, int p, int v)
{
    Message(0,c,p,v);
}

void NMidiAuther::Off(int c, int p)
{
    Message(0,c-16,p);
}

void NMidiAuther::Wait(unsigned long l)
{
    Message(l,WAITNOTE);
}

void NMidiAuther::SelfTest()
{
  for(int i = 0;i<12;i++){
      cout<<noteStr(60+i);
      if(i%2){
          cout<<endl;
        }
    }
  cout<<endl;
}

void NMidiAuther::instrumentsSetup(int program[])
{
  for (int i = 0; i < 8; ++i)
    {
      writeByte(0);
      writeByte(i+192);
      writeByte(program[i]);
    }
}

void NMidiAuther::generalMidi()
{
  unsigned char buffer[] = {0,240,5,126,127,9,1,247};
  fwrite(buffer,1,sizeof(buffer),datFile);
  place += sizeof(buffer);
}

void NMidiAuther::writeByte(unsigned char byteData)
{
  int tmp = byteData;
  fwrite (&tmp, 1, 1, datFile);
  ++place;
}

void NMidiAuther::createMidiFile(const char *fileName, const char *srcFile, long size)
{
  FILE* midFile = fopen (fileName, "wb");
  char head[] = { 'M', 'T', 'h', 'd',
                  0, 0, 0, 6, 0, 0, 0, 1, 0, 96,
                  'M','T','r','k'};
  fwrite(head,1,18,midFile);

  unsigned char byte[4];
  long2hexs (size, byte);
  fwrite (byte, 1, 4, midFile);

  int i;
  FILE* datFile = fopen (srcFile, "rb");
  do
    {
      fread (&i, 1, 1, datFile);
      if (!feof (datFile))
        fwrite (&i, 1, 1, midFile);
    }
  while (!feof (datFile));

  fclose (midFile);
  fclose (datFile);
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
