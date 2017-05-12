#ifndef PREDMET_H
#define PREDMET_H

#include <iostream>
#include <QString>
#include <QVector>
#include "vreme.h"

using namespace std;

class Predmet {

    /* ugnjezdena klasa Obaveza, koja postoji samo u okviru predmeta */
public:
    class Obaveza {

    public:
        /* svaka obaveza ima tip iz narednog skupa dopustivih vrijednosti */

        /* Da li zelimo da enum mora da se referise sa Obaveza::tip_obaveze,
            tj. sa Predmet::Obaveza::tip_obaveze van klase Predmet? */

        enum tip_obaveze {
            test,
            kolokvijum,
            seminarski_rad,
            pismeni_ispit,
            usmeni_ispit
        };

        QString pisi() const;
        void citaj(const QString &qs);

    private:
        tip_obaveze _tip;
        unsigned char _broj_mogucih_poena;
        unsigned char _broj_osvojenih_poena;
        Vreme _vreme;
        Vreme _rok;
        /* rok ce biti validno vrijeme samo za seminarski_rad,
        za ostale obaveze ce biti neko nepostojece vrijeme, npr.max vrijeme */
        QString _komentar;

        /* mozda dodati jos jedan tip obaveze "nepoznat" koji ce biti
            podrazumijevana vrijednost za tip u konstruktoru, jer
            nema smisla da bude neka od validnih obaveza */
        /* Da li konstruktor uopste treba da bude privatan ili to ne zelimo? */

        Obaveza(tip_obaveze tip=Obaveza::test, unsigned char broj_mogucih_poena = 0,
                unsigned char broj_osvojenih_poena = 0, Vreme vreme = 0, Vreme rok = 0,
                QString komentar="")
            : _tip(tip), _broj_mogucih_poena(broj_mogucih_poena),
              _broj_osvojenih_poena(broj_osvojenih_poena), _vreme(vreme), _rok(rok),
              _komentar(komentar)
        {}

        friend ostream& operator << (ostream & izlaz, const Obaveza & obaveza);
        friend class Predmet;
        friend class QVector<Obaveza>;

    };

    /* ocjena je 0 ako se ne navede, npr.ako predmet jos nije polozen;
    dakle, za sve predmete, ocjena je ili 0, ili izmedju 6 i 10;
    sve 0 se ignorisu prilikom racunanja prosjeka */
    Predmet (QString naziv="", unsigned char ocjena=0, QString profesor="", QString komentar="")
        :_naziv(naziv), _obaveze(), _ocjena(ocjena), _profesor(profesor), _literatura(),
          _komentar(komentar)
    {}

    /* metod dodaje obavezu u vektor _obaveze */
    void dodaj_obavezu (Obaveza::tip_obaveze tip, unsigned char broj_mogucih_poena=0,
                        unsigned char broj_osvojenih_poena=0, Vreme datum=0, Vreme rok=0,
                        QString komentar="");

    /* metod vraca i-tu obavezu, ako je i vece od duzine vektora vraca posljednju obavezu */
    Obaveza& obaveza_i (int i);

    /* metod vraca broj obaveza */
    unsigned broj_obaveza() const;

    /* metod dodaje knjigu u vektor literatura */
    void dodaj_knjigu (QString k);

    /* metod vraca i-tu knjigu iz preporucene literature, ako je i vece od duzine vektora
    vraca posljednju knjigu */
    QString& knjiga_i (int i);

    /* metod vraca broj knjiga */
    unsigned broj_knjiga() const;

    /* vraca se ocjena - get metod */
    unsigned char ocjena() const;

    QString pisi() const;
    void citaj(const QString &qs);

private:
    QString _naziv;
    QVector<Obaveza> _obaveze;
    unsigned char _ocjena;
    QString _profesor;
    QVector<QString> _literatura;
    QString _komentar;

    friend ostream& operator << (ostream & izlaz, const Predmet& predmet);

};

ostream& operator<< (ostream & izlaz, const Predmet::Obaveza & obaveza);
ostream& operator<< (ostream & izlaz, const Predmet& predmet);

#endif // PREDMET_H
