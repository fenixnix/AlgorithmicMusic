#include "NTrack.h"

NTrack::NTrack()
{

}

void NTrack::Play(int note, int duration, int volume)
{
  On(note,volume);
  Wait(duration);
  Off(note);
}

void NTrack::On(int note, int volume)
{
  stringstream ss;
  ss<<"On:"<<note<<","<<volume;
  msgQueue.push_back(ss.str());
}

void NTrack::Off(int note)
{
  stringstream ss;
  ss<<"Off:"<<note;
  msgQueue.push_back(ss.str());
}

void NTrack::Wait(int duration)
{
  stringstream ss;
  ss<<"Wait:"<<duration;
  msgQueue.push_back(ss.str());
}

vector<string> NTrack::GetData()
{
  return msgQueue;
}
