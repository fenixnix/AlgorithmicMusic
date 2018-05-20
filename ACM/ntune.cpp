#include "ntune.h"
#include <iostream>
#include <time.h>

NTune::NTune()
{
    time_t t;
    srand ((unsigned) time (&t));
}

void NTune::Random(int length)
{
    base.clear();
    int rndRange = div;
    vector<int> values;
    for(int i = 0; i<rndRange; i++){
        values.push_back(i);
    }
    cout<<__FUNCTION__<<": ";
    for(int i = 0;i<length;i++){
        if(values.size()<=0){
            break;
        }
        auto roll = rand()%values.size();
        base.push_back(values[roll]);
        cout<<values[roll]<<",";
        values.erase(values.begin()+roll);
    }
    cout<<endl;
    Motivic();
    baseAddNew = Add(1);
}

void vecRmv(vector<int> &vec,int v){
    for(auto iter = vec.begin(); iter != vec.end(); ++iter ) //遍历和删除一个对象
    {
        if( (*iter) == v ) {
            vec.erase(iter);
            break;
        }
    }
}

vector<int> NTune::Add(int count)
{
    vector<int> tmp;
    vector<int> values;
    for(int i = 0; i<div; i++){
        values.push_back(i);
    }

    for(int i = 0;i<base.size();i++){
        vecRmv(values,base[i]);
        tmp.push_back(base[i]);
    }

    cout<<__FUNCTION__<<": ";
    for(int i = 0;i<count;i++){
        if(values.size()<=0){
            break;
        }
        auto roll = rand()%values.size();
        tmp.push_back(values[roll]);
        cout<<values[roll]<<",";
        values.erase(values.begin()+roll);
    }
    cout<<endl;
    return tmp;
}

vector<int> NTune::RandomSel()
{
    int roll = rand()%9;
    switch(roll){
    case 0: return base;break;
    case 1: return retro;break;
    case 2: return mixed1;break;
    case 3: return mixed2;break;
    case 4:
    case 5: return mixed3;break;
    case 6:
    case 7:
    case 8: return baseAddNew;break;
    default:break;
    }
}

void NTune::SelfTest()
{
    NTune tune;
    tune.Random(6);
    tune.Add(3);
}

void NTune::Motivic()
{
    Inverse();
    Retro();
    RetroInver();
    mixed1 = Mixed(base);
    mixed2 = Mixed(mixed1);
    mixed3 = Mixed(mixed2);
    mixedinver1 = Mixed(inver);
    mixedinver2 = Mixed(mixedinver1);
    mixedinver3 = Mixed(mixedinver2);
}

void NTune::Inverse()
{
    cout<<__FUNCTION__<<": ";
    inver.clear();
    for(int i = 0;i<base.size();i++){
        auto v = (div-1) - base[i];
        inver.push_back(v);
        cout<<v<<",";
    }
    cout<<endl;
}

vector<int> NTune::Inver(vector<int> src)
{
    cout<<__FUNCTION__<<": ";
    vector<int> tmp;
    for(int i = 0;i<src.size();i++){
        auto v = (div-1) - base[i];
        inver.push_back(v);
        cout<<v<<",";
    }
    cout<<endl;
    return tmp;
}

void NTune::Retro()
{
    cout<<__FUNCTION__<<": ";
    retro.clear();
    for(int i = 0;i<base.size();i++){
        auto v = base[base.size()-i-1];
        retro.push_back(v);
        cout<<v<<",";
    }
    cout<<endl;
}

void NTune::RetroInver()
{
    cout<<__FUNCTION__<<": ";
    retroinver.clear();
    for(int i = 0;i<inver.size();i++){
        auto v = inver[inver.size()-i-1];
        retroinver.push_back(v);
        cout<<v<<",";
    }
    cout<<endl;
}

vector<int> NTune::Mixed(vector<int> src)
{
    cout<<__FUNCTION__<<": ";
    vector<int> tmp;
    for(int i = 0;i<src.size()-1;i++){
        auto v = src[i+1];
        tmp.push_back(v);
        cout<<v<<",";
    }
    tmp.push_back(src[0]);
    cout<<src[0];
    cout<<endl;
    return tmp;
}


