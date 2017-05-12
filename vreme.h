#ifndef VREME_H
#define VREME_H

#include <iostream>
#include <iomanip>
#include <climits>
#include <QWidget>
#include <QString>

/* ne vrse se nikakve provere da l' su data vremena realna*/
class Vreme
{
public:
  /*
   Vreme() daje trenutno vreme
   podrazumevane vrednosti za dan, mesec i godinu su zapravo trenutni dan, mesec i godina
   Vreme(0) daje max vreme
   */
  Vreme(unsigned char dan = UCHAR_MAX,unsigned char mesec = 0,short int godina = 0,unsigned char sat = 0, unsigned char minut = 0);

  /*t1.Razlika(t2) = t1 - t2*/
  int Razlika(const Vreme & t) const;

  /*koristi se kod sort funkcije*/
  bool operator<(const Vreme & t) const;

  QString pisi() const;
  void citaj(const QString& qs);

private:
  unsigned char _dan;
  unsigned char _mesec;
  short int _godina;
  unsigned char _sat;
  unsigned char _minut;

  friend std::ostream & operator << (std::ostream & izlaz, const Vreme & vreme);
};

std::ostream & operator << (std::ostream & izlaz, const Vreme & vreme);

#endif
