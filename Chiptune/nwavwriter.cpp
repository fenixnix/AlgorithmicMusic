#include "nwavwriter.h"

typedef unsigned char bit8;

NWavWriter::NWavWriter()
{

}

int wav_bits=8;
int wav_freq=22050;

void NWavWriter::Save(string fileName, vector<float> data)
{
    ofstream file(fileName,ios::binary);

    unsigned int dword=0;
    unsigned short word=0;

    file.write("RIFF",4);
    dword = 44+ data.size();file.write((char*)&dword,4);// remaining file size
    file.write("WAVE",4);
    file.write("fmt ",4);
    dword=16;file.write((char*)&dword,4);// chunk size
    word=1;file.write((char*)&word,2);// compression code
    word=1;file.write((char*)&word,2);// channels
    dword=wav_freq;file.write((char*)&dword,4);// sample rate
    dword=wav_freq*wav_bits/8;file.write((char*)&dword,4);// bytes/sec
    word=wav_bits/8;file.write((char*)&word,2);// block align
    word=wav_bits;file.write((char*)&word,2);// bits per sample
    file.write("data",4); // "data"
    dword=data.size();file.write((char*)&dword,4);// chunk size


    for(int i = 0;i<data.size();i++){
        bit8 isample = data[i]*127+128;
        file.write((char*)&isample, 1);
    }
    file.close();
}
