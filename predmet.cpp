#include "predmet.h"
#include <QRegExp>
#include <QString>
#include <QStringList>
using namespace std;


bool Predmet::Obaveza::operator<(const Predmet::Obaveza &o) const {
    if (!(_vreme < Vreme(0)))
    {
        if (!(o._vreme < Vreme(0)))
            return _rok < o._rok;
        else
            return _rok < o._vreme;
    }

    if (!(o._vreme < Vreme(0)))
            return _vreme < o._rok;

    return _vreme < o._vreme;

}

Vreme Predmet::Obaveza::vreme() const {
    return _vreme;
}

Vreme Predmet::Obaveza::rok() const {
    return _rok;
}

void Predmet::dodaj_obavezu(Predmet::Obaveza::tip_obaveze tip, unsigned char broj_mogucih_poena,
                             unsigned char broj_osvojenih_poena, Vreme datum, Vreme rok, QString komentar) {

   _obaveze.push_back(Obaveza(tip, broj_mogucih_poena, broj_osvojenih_poena, datum, rok, komentar));
}

/* metod vraca i-tu obavezu */
Predmet::Obaveza& Predmet::obaveza_i (int i) {
    if (i < _obaveze.size())
        return _obaveze[i];
    return _obaveze.back();
}

/* metod vraca broj obaveza koje ima predmet */
unsigned Predmet::broj_obaveza() const {
    return _obaveze.size();
}

/* metod dodaje knjigu u vektor literatura */
void Predmet::dodaj_knjigu(QString k) {
    _literatura.push_back(k);
}

/* metod vraca i-tu knjigu iz preporucene literature */
QString& Predmet::knjiga_i (int i) {
    if (i < _literatura.size())
        return _literatura[i];
    return _literatura.back();
}


/* metod vraca broj knjiga */
unsigned Predmet::broj_knjiga() const {
    return _literatura.size();
}

unsigned char Predmet::ocjena() const {
    return _ocjena;
}

QString Predmet::naziv() const {
    return _naziv;
}

QString Predmet::Obaveza::pisi() const {
    QString qs = QString("%1\n%2\n%3\n%4\n%5\n%6\n").
            arg(_tip).arg(_broj_mogucih_poena).arg(_broj_osvojenih_poena).
            arg(_vreme.pisi()).arg(_rok.pisi()).arg(_komentar);
    return qs;
}

QString Predmet::Obaveza::pisi_za_korisnika() const {
    QString qs;
    if (_tip==Predmet::Obaveza::test)
        qs = "Test\n";
    else if (_tip==Predmet::Obaveza::kolokvijum)
        qs = "Kolokvijum\n";
    else if (_tip==Predmet::Obaveza::seminarski_rad)
        qs = "Seminarski rad\n";
    else if (_tip==Predmet::Obaveza::pismeni_ispit)
        qs = "Pismeni ispit\n";
    else
        qs = "Usmeni ispit\n";

    qs.append(QString("Broj mogucih poena: %2\nBroj osvojenih poena: %3\n"
                      "Vrijeme obaveze: %4\nRok za obavezu: %5\nKomentar: %6\n").
              arg(_broj_mogucih_poena).arg(_broj_osvojenih_poena).
              arg(_vreme.pisi()).arg(_rok.pisi()).arg(_komentar));
    return qs;
}

void Predmet::Obaveza::citaj(const QString &qs) {
    QStringList list = qs.split("\n");
    _tip = Predmet::Obaveza::tip_obaveze(list[0].toInt());
    _broj_mogucih_poena = list[1].toUShort();
    _broj_osvojenih_poena = list[2].toUShort();
    _vreme.citaj(list[3]);
    _rok.citaj(list[4]);
    _komentar = list[5];
}


QString Predmet::pisi() const {
    QString str = QString("{\n%1\n[\n").arg(_naziv);
    for(QVector<Obaveza>::const_iterator i = _obaveze.cbegin(); i!=_obaveze.cend(); i++)
        str.append(i->pisi());
    str.append(QString("]\n%1\n%2\n[\n").arg(_ocjena).arg(_profesor));
    for(QVector<QString>::const_iterator i = _literatura.cbegin(); i!=_literatura.cend(); i++)
        str.append(*i).append("\n");
    str.append(QString("]\n%1\n}\n").arg(_komentar));
    return str;
}

void Predmet::citaj(const QString& qs) {
    QStringList lista = qs.split("\n");
    if (!lista.contains("["))
        return;
    _naziv = lista[1];
    QStringList::iterator i = lista.begin()+3;
    while(*i != "]") {
        Predmet::Obaveza::tip_obaveze tip = Predmet::Obaveza::tip_obaveze(i->toInt());
        i++;
        unsigned char moguci_bod = i->toUShort();
        i++;
        unsigned char osvojeni_bod = i->toUShort();
        i++;
        Vreme vreme, rok;
        vreme.citaj(*i);
        i++;
        rok.citaj(*i);
        i++;
        this->dodaj_obavezu(tip, moguci_bod, osvojeni_bod, vreme, rok, *i);
        i++;
    }
    i++;
    _ocjena = i->toUShort();
    i++;
    _profesor = *i;
    i++; i++;
    for(; *i!= "]"; i++)
        this->dodaj_knjigu(*i);
    i++;
    _komentar = *i;
}

ostream& operator << (ostream& izlaz, const Predmet::Obaveza & obaveza) {
    izlaz << obaveza._tip << endl;
    izlaz << +obaveza._broj_mogucih_poena << endl;
    izlaz << +obaveza._broj_osvojenih_poena << endl;
    izlaz << obaveza._vreme << endl;
    izlaz << obaveza._rok << endl;
    izlaz << obaveza._komentar << endl;
    return izlaz;
}


ostream& operator << (ostream& izlaz, const Predmet& predmet) {
    izlaz << "{" << endl;
    izlaz << predmet._naziv << endl;

    izlaz << "[" << endl;
    for(QVector<Predmet::Obaveza>::const_iterator i = predmet._obaveze.begin();
        i!=predmet._obaveze.end(); i++)
        /* ako sam ovdje dodala novi red poslije obaveze, ne treba da ga stavim u operator <<
        za klasu obaveza */
            izlaz << (*i) << endl;
    izlaz << "]" << endl;

    izlaz << static_cast<unsigned>(predmet._ocjena) << endl;
    izlaz << predmet._profesor << endl;

    izlaz << "[" << endl;
    for(QVector<QString>::const_iterator i = predmet._literatura.begin();
        i!=predmet._literatura.end(); i++)
            izlaz << (*i) << endl;
    izlaz << "]" << endl;

    izlaz << predmet._komentar << endl;
    izlaz << "}" << endl;

    return izlaz;
}
