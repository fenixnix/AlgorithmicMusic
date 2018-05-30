#ifndef NSFX_H
#define NSFX_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class NWavWriter
{
public:
    NWavWriter();
    static void Save(string fileName,vector<float> data);
};

#endif // NSFX_H
