#ifndef NTUNE_H
#define NTUNE_H

#include <vector>

using namespace std;

class NMelody
{
public:
  NMelody();
  void Random(int length);
  vector<int> Add(int cnt);
  vector<int> RandomSel();

  static void SelfTest();

  vector<int> base;
  vector<int> baseAddNew;
  vector<int> inver;
  vector<int> retro;
  vector<int> retroinver;

  vector<int> mixed1;
  vector<int> mixed2;
  vector<int> mixed3;
  vector<int> mixedinver1;
  vector<int> mixedinver2;
  vector<int> mixedinver3;
private:
  void Motivic();

  void Inverse();
  vector<int> Inver(vector<int> src);
  void Retro();
  void RetroInver();
  vector<int> Mixed(vector<int> src);
  void MixedInver();
  int div = 12;
};

#endif // NTUNE_H
