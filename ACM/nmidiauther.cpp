#include "nmidiauther.h"

int midiOctave (int pitch);
int midiNote (int pitch);
string noteStr (int pitch);

NMidiAuther::NMidiAuther()
{

}

void NMidiAuther::Open(string fileName)
{
  tmpFile = fopen(fileName.data(),"wb");
  string midiFileName = fileName + ".mid";
  midiFile = fopen(midiFileName.data(),"wb");
}

void NMidiAuther::Close()
{

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

void NMidiAuther::programSetup()
{
  programSetup();
}

void NMidiAuther::generalMidi()
{
  unsigned char buffer[] = {0,240,5,126,127,9,1,247};
  fwrite(buffer,1,sizeof(buffer),midiFile);
  place += sizeof(buffer);
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
