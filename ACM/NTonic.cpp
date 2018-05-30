#include "NTonic.h"
#include "qmath.h"
#include "QDebug"
#include <QDomDocument>
#include <QFile>

QDomDocument dom;
QMap<QString,vector<int>> modes;

NTonic::NTonic()
{
  Init();
  LoadModeFile(":/TuneMode.xml");
  auto mods = GetModes();
  qDebug()<<"modes:"<<mods.size();
  for(int i = 0;i<mods.size();i++){
      qDebug()<<"mode:"<<QString::fromStdString(mods[i]);
    }
  SetMode();
}

int NTonic::PitchFreq(int pitch)
{
  int i = pitch%(int)freqs.size();
  if(pitch<0){
      i= (freqs.size()+i)%freqs.size();
    }
  int octave = floor((float)pitch/(float)freqs.size());
  //qDebug()<<"index:"<<index<<"i:"<<i<<"d:"<<d;
  return freqs[i]*pow(2,octave);
}

int NTonic::NotePitch(int note)
{
  int i = note%(int)mode.size();
  if(note<0){
      i= (mode.size()+i)%mode.size();
    }
  int octave = floor((float)note/(float)mode.size());
  return mode[i]+octave*freqs.size() + midiBasePitch;
}

int NTonic::NoteFreq(int note)
{
  return PitchFreq(NotePitch(note) - midiBasePitch);
}

void NTonic::SetMode(string modeName)
{
  mode.clear();

  QString qModeName = QString::fromStdString(modeName);

  if(modes.contains(qModeName)){
    vector<int> mod = modes[qModeName];
    for(int i = 0;i<mod.size();i++){
        mode.push_back(mod[i]);
      }
    }
}

void NTonic::SetBasePitch(int pitch)
{
  midiBasePitch = pitch;
}

int NTonic::GetModeNoteCnt()
{
  return mode.size();
}

void NTonic::Init(float base, int div)
{
  baseFreq = base;
  freqs.clear();
  for(int i = 0;i<div;i++){
      freqs.push_back(baseFreq*pow(2,(float)i/(float)div));
    }
}

vector<int> SyncModeData(QDomNode node){
  vector<int> pitchs;
  QString pitchsData = node.firstChildElement().firstChild().toText().data();
  foreach(QString d,pitchsData.split(',')){
      pitchs.push_back(d.toInt());
    }
  return pitchs;
}

void SyncData(){
  modes.clear();
  auto root = dom.documentElement();
  for(int i = 0;i<root.childNodes().count();i++){
      auto name = root.childNodes().at(i).nodeName();
      modes.insert(name,SyncModeData(root.childNodes().at(i)));
    }
//  foreach(QDomNode node,root.childNodes()){
//      auto modeName = node.nodeName();
//      modes.insert(modeName,SyncModeData(node));
//    }
}

void NTonic::LoadModeFile(string fileName)
{
  dom.clear();
  QFile file(QString::fromStdString(fileName));
  if(!file.exists()){
      qDebug()<<"file not exists!!!";
    }
  file.open(QIODevice::ReadOnly);
  if(!dom.setContent(&file)){
      file.close();
    }
  SyncData();
  file.close();
}

vector<string> NTonic::GetModes()
{
  vector<string> names;
  foreach(QString name , modes.keys()){
      names.push_back(name.toStdString());
    }
  return names;
}
/*
int ChinaScale[] = {0,2,4,7,9};
int China2Scale[] = {0,3,5,7,10};
int Japan1Scale[] = {0,4,5,9,11};//日本音阶
int Japan2Scale[] = {0,4,5,7,11};
int GypsyScale[] = {0,3,6,7,8,10};//吉普赛音阶（Gypsy）
int OriScale[] = {0,1,4,5,6,9,10};//东方音阶
int ArabicScale[] = {1,2,4,6,7,9,11};//阿拉伯音阶
int Arabic2Scale[] = {0,1,4,5,7,8,10};
int FlamencoScale[] = {0,1,4,6,7,8,10};//弗拉门戈音阶
int HinduScale[] = {0,2,4,5,7,8,10};//印度音阶
int HungarianScale[] = {0,3,4,6,7,9,10};//匈牙利音阶
int HungarianMinorScale[] = {0,2,3,6,7,8,11};//匈牙利音阶小调
int RussiaScale[] = {0,2,4,5,6,7,8,9,10,11};//俄罗斯音阶
int NapoliScale[] = {0,1,3,5,7,9,11};
int NapoliMinorScale[] = {0,1,3,5,7,8,11};
int LydianDominant[] = {0,2,4,6,7,9,10};//大利底亚音阶
int SuperLocrianp[] = {0,1,3,4,6,8,10};//超级洛克里亚音阶

int BlusScale[] = {0,3,5,6,7,10};//布鲁斯音阶
int MixelBluesScale[] = { 0,3,4,5,6,7,10};//混合布鲁斯音阶
int JazzMinor[] = {0,2,3,5,7,9,11};//爵士小调音阶：

int scale0[] = {0,2,4,6,8,9,11};//和声小调
int scale1[] = {0,2,3,5,6,8,10};//减音阶
int scale2[] = {0,1,3,4,6,7,9,10};//半—全减音阶
int scale3[] = {0,2,4,6,8,10};//全音音阶


// ⑿旋律大调音阶: [/B]1 2 3 4 5 b6 7 1 b7 b6 5 4 3 2 1
// ⒀旋律小调音阶： [/B]6 7 1 2 3 #4 #5 6 5 4 3 2 1 7 6

int NTonic::modes[OCTAVE_SCALE][OCTAVE_SCALE];

void NTonic::initMode()
{
    char baseMode[] = {2,2,1,2,2,2,1};
    for(int j = 0;j<OCTAVE_SCALE;j++){
            modes[j][0] = 0;
            for(int i = 0;i<OCTAVE_SCALE-1;i++){
                    modes[j][i+1] = modes[j][i]+baseMode[i];
                }
            //mov array
            int tmp = baseMode[0];
            for(int i = 0;i<OCTAVE_SCALE-1;i++){
                    baseMode[i] = baseMode[i+1];
                }
            baseMode[6] = tmp;
        }
}
*/
