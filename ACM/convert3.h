/* header file convert3.h that must be in all of these programs
to convert delta variables and write files. Uses shifiting bits.
This produces a format 0 midi file */

#include <iostream>
#include <fstream>

int program_number[8];
unsigned long place = 0L;
FILE *fp1;

void convertlong_4hexs (unsigned long d, unsigned char byte[4])
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

void convert_hexbyte_varbyte (unsigned char byte[4], unsigned char varbyte[4])
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

void writeByte(unsigned char byteData)
{
    int tmp = byteData;
    fwrite (&tmp, 1, 1, fp1);
    ++place;
}

void program_setup (void)
{
    for (int j = 0; j < 8; ++j)
    {
        writeByte(0);
        writeByte(j+192);
        writeByte(program_number[j]);
    }
}

void program_setup (int prog[8])
{
    for (int j = 0; j < 8; ++j)
    {
        writeByte(0);
        writeByte(j+192);
        writeByte(prog[j]);
    }
}

void general_midi (void)
{
    unsigned char buffer[] = {0,240,5,126,127,9,1,247};
    fwrite(buffer,1,sizeof(buffer),fp1);
    place += sizeof(buffer);
}

void createDatTail(){
    unsigned char end[] = { 0, 255, 47, 0};
    fwrite(end,1,4,fp1);
    place+=4;
    fclose (fp1);
}

void createMidiFile(const char* fileName,const char* srcFile, long size){
    FILE* midFile = fopen (fileName, "wb");
    char head[] = { 'M', 'T', 'h', 'd',
                    0, 0, 0, 6, 0, 0, 0, 1, 0, 96,
                    'M','T','r','k'};
    fwrite(head,1,18,midFile);

    unsigned char byte[4];
    convertlong_4hexs (size, byte);
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

void close_midfiles (void)
{
    createDatTail();
    createMidiFile("music.mid","tempfile",place);
}

void play (unsigned long int l, int c, int p = 60, int v = 127)
{
    unsigned long number;
    unsigned char varbyte[4];
    unsigned char byte[4];
    number = l;
    convertlong_4hexs (number, byte);
    convert_hexbyte_varbyte (byte, varbyte);

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

void wait(unsigned long int l){
    play(l,152 - 16);
}

void playChord3(unsigned long int l, int c, int p, int v = 127){
    play(l,c,p,v);
    play(l,c,p+3,v);
    play(l,c,p+7,v);
}

void open_midfiles (void)
{
    fp1 = fopen ("tempfile", "wb");
}

int midiNote (int midinumber)
{
    int note;
    note = midinumber % 12;
    return (note);
}

int midiOctave (int midinumber)
{
    int octave;
    octave = midinumber / 12;
    return (octave);
}

void printit (int midinumber)
{
    int midinote = midinumber % 12;
    int octave = (midinumber / 12) - 1;
    printf ("%d", octave);
    switch (midinote)
    {
    case 0:
        printf ("C  ");
        break;
    case 1:
        printf ("Db ");
        break;
    case 2:
        printf ("D  ");
        break;
    case 3:
        printf ("Eb ");
        break;
    case 4:
        printf ("E  ");
        break;
    case 5:
        printf ("F  ");
        break;
    case 6:
        printf ("Gb ");
        break;
    case 7:
        printf ("G  ");
        break;
    case 8:
        printf ("Ab ");
        break;
    case 9:
        printf ("A  ");
        break;
    case 10:
        printf ("Bb ");
        break;
    case 11:
        printf ("B  ");
        break;
    }
}
