#include "nmuse.h"
#include "qmath.h"
#include "QDebug"
#include <QDomDocument>
#include <QFile>

QDomDocument dom;
QMap<QString,vector<int>> modes;

NMuse::NMuse()
{
  Init();
  LoadModeFile(":/TuneMode.xml");
  auto mods = GetModes();
  qDebug()<<"modes:"<<mods.size();
  for(int i = 0;i<mods.size();i++){
      qDebug()<<"mode:"<<QString::fromStdString(mods[i]);
    }
}

int NMuse::Pitch(int index)
{
  int i = index%(int)datas.size();
  if(index<0){
      i= (datas.size()+i)%datas.size();
    }
  int d = floor((float)index/(float)datas.size());
  //qDebug()<<"index:"<<index<<"i:"<<i<<"d:"<<d;
  return datas[i]*pow(2,d);
}

int NMuse::TunePitch(int index)
{
  int i = index%(int)tuneMode.size();
  if(index<0){
      i= (tuneMode.size()+i)%tuneMode.size();
    }
  int d = floor((float)index/(float)tuneMode.size());
  return Pitch(tuneMode[i]+d*datas.size());
}

void NMuse::SetMode(string modeName)
{
  tuneMode.clear();

  QString qModeName = QString::fromStdString(modeName);

  if(modes.contains(qModeName)){
    vector<int> mod = modes[qModeName];
    for(int i = 0;i<mod.size();i++){
        tuneMode.push_back(mod[i]);
      }
  }
}

int NMuse::TuneCount()
{
  return tuneMode.size();
}

void NMuse::Init(int base, int div)
{
  baseFreq = base;
  datas.clear();
  for(int i = 0;i<div;i++){
      datas.push_back(baseFreq*pow(2,(float)i/(float)div));
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

void NMuse::LoadModeFile(string fileName)
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

vector<string> NMuse::GetModes()
{
  vector<string> names;
  foreach(QString name , modes.keys()){
      names.push_back(name.toStdString());
    }
  return names;
}
