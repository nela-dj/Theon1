#include "vreme.h"
#include <QStringList>
#include <QRegExp>
#include <QChar>
using namespace std;

Vreme::Vreme(unsigned char dan,unsigned char mesec,short int godina,unsigned char sat, unsigned char minut):
    _dan(dan),_mesec(mesec),_godina(godina),_sat(sat),_minut(minut)
{
  if(dan == 0){
    _minut = UCHAR_MAX;
    _sat = UCHAR_MAX;
    _dan = UCHAR_MAX;
    _mesec = UCHAR_MAX;
    _godina = SHRT_MAX;
    return ;
  }
  if(_godina == 0){
    time_t pom;
    time(&pom);
    tm * pom1 = localtime(&pom);
    _godina = 1900 + pom1->tm_year;
    if(_mesec == 0) _mesec = pom1 -> tm_mon +1;
    if(_dan == UCHAR_MAX){
    _dan = pom1 -> tm_mday;
    _sat = pom1 -> tm_hour;
    _minut = pom1 -> tm_min;
    }
  }
}

bool inline Prestupna(const short int godina){
  return (godina % 400 == 0 || godina % 100 != 0) && godina % 4 == 0;
}

int inline DanaUMesecu(unsigned char mesec,bool prestupna){
  switch(mesec){
      case 4:
      case 6:
      case 9:
      case 11:
    return 30;
      case 2:
    return prestupna?29:28;
      default: return 31;
      }
}

int Vreme::Razlika(const Vreme & t) const
{
  if (*this<t) return -t.Razlika(*this);
  if(_godina == t._godina){
    if(_mesec == t._mesec){
      return ((_dan - t._dan)*24 + _sat - t._sat)*60 + _minut - t._minut;
    }
    int s = 0;
    for(short int i = t._mesec +1; i < _mesec; i++) s += DanaUMesecu(i,Prestupna(t._godina));
    s += _dan - t._dan + DanaUMesecu(t._mesec,Prestupna(t._godina));
    return (s*24 + _sat - t._sat)*60 + _minut - t._minut;
  }
  int s = 0;
  for(short int i = t._godina +1; i < _godina; i++) s += Prestupna(i)? 366 : 365;
  for(unsigned char i = 1; i < _mesec; i++) s += DanaUMesecu(i,Prestupna(_godina));
  for(unsigned char i = t._mesec +1; i <= 12; i++) s += DanaUMesecu(i,Prestupna(t._godina));
  s += _dan - t._dan + DanaUMesecu(t._mesec,Prestupna(t._godina));
  return (s*24 + _sat - t._sat)*60 + _minut - t._minut;
}

bool Vreme::operator<(const Vreme & t) const
{
  if(this->_godina < t._godina) return true;
  else if(this->_godina == t._godina) {
    if(this->_mesec < t._mesec) return true;

    else if(this->_mesec == t._mesec) {
        if(this->_dan < t._dan) return true;
        else if(this->_dan == t._dan) {
            if(this->_sat < t._sat) return true;
            else if(this->_sat == t._sat) return this->_minut < t._minut;
        }
    }
  }
  return false;
}


QString Vreme::pisi() const {
    QString str= QString("%1:%2 %3.%4.%5.").
            arg(int(_sat), 2, 10, QChar('0')).arg(int(_minut), 2, 10, QChar('0')).arg(_dan).arg(_mesec).arg(_godina);
    return str;
}

void Vreme::citaj(const QString& qs) {
    QStringList list = qs.split(QRegExp("\\W+"), QString::SkipEmptyParts);
    _sat = list[0].toUShort();
    _minut = list[1].toUShort();
    _dan = list[2].toUShort();
    _mesec = list[3].toUShort();
    _godina = list[4].toUShort();
}



ostream & operator << (ostream & izlaz, const Vreme & vreme){
    return izlaz<<setw(2)<<setfill('0')<<+vreme._sat<<":"<<setw(2)<<setfill('0')<<+vreme._minut<<"	"<<+vreme._dan<<"."<<+vreme._mesec<<"."<<vreme._godina<<".";
  }
