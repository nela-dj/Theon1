#include "predmetqt.h"
#include <QIODevice>
#include <QTextStream>
#include "ui_predmetqt.h"
#include "mainwindow.h"
#include "provjera_obavezaqt.h"
#include "provjera_sajtovaqt.h"
#include <algorithm>

PredmetQt::PredmetQt (QWidget* roditelj) :
        QWidget(roditelj),
        ui(new Ui::PredmetQt)
{
    ui->setupUi(this);
    this->setWindowTitle("Dobrodosli u Theon!");
    ui->ProvjeraObaveza->setEnabled(false);
    ui->PromjeneSajtova->setEnabled(false);
    ui->UnosPredmeta->setEnabled(false);
    ui->VremenskPrognoza->setEnabled(false);
}


PredmetQt::~PredmetQt() {
    delete ui;
}

void PredmetQt::pokreni() {

    // otvaramo fajl za citanje predmeta
    QFile file("predmeti.txt");
    if (!file.open(QIODevice::ReadOnly |QIODevice::Text))
         return;
    QString pred_str = "";
    QTextStream in(&file);
    // citamo predmet po predmet i proslijedjujemo funkciji koja cita predmet
    while (!in.atEnd()) {
           //za sada pretpostavljamo da je fajl u ispravnom formatu
           QString line = in.readLine();
           pred_str.append(line).append("\n");
           if (line == "}") {
               //pred_str.append(line);
               Predmet pred;
               pred.citaj(pred_str);
               predmeti.push_back(pred);
               if(!in.atEnd())
                line = in.readLine();
               pred_str = "";
           }

       }
    //nakon sto smo procitali predmete u QVector<Predmet> predmeti zatvaramo fajl
    in.flush();
    file.close();

    ui->Pokreni->setEnabled(false);
    ui->PromjeneSajtova->setEnabled(true);
    ui->ProvjeraObaveza->setEnabled(true);
    ui->UnosPredmeta->setEnabled(true);
    ui->VremenskPrognoza->setEnabled(true);


    QFile file2("out.txt");
    if (!file2.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file2);
    for(QVector<Predmet>::const_iterator i=predmeti.cbegin(); i!=predmeti.cend(); i++)
        out << i->pisi() << endl;
    file2.close();

}

void PredmetQt::unosPredmeta() {
    MainWindow *nw = new MainWindow(this);
    nw->show();
    nw->setWindowTitle("Unos predmeta");
}

void PredmetQt::provjeraObaveza() {
    QVector<Predmet::Obaveza> obaveze;
    for (auto i=predmeti.begin(); i!=predmeti.end(); i++) {
        unsigned k=i->broj_obaveza();
        for (unsigned j=0; j<k; j++) {
            //ne dodajemo one obaveze za koje se ne znaju ni vrijeme ni rok
            //jer one vjerovatno nece biti uskoro, takodje izbacujemo obaveze
            //za koje su vrijeme ili rok manji od trenutnog vremena, one su vec prosle
            Predmet::Obaveza o(i->obaveza_i(j));
            if ((!(o.vreme()<Vreme(0)) && !(o.rok()<Vreme(0)))
                    || o.vreme()<Vreme() || o.rok()<Vreme())
                continue;
            obaveze.push_back(o);
        }
    }

    qSort(obaveze);
    QString s;
    for(int i=0; i<obaveze.size(); i++)
        s.append(obaveze[i].pisi_za_korisnika()).append("\n");
    ProvjeraObavezaQt *nw = new ProvjeraObavezaQt(s);
    nw->show();
    nw->setWindowTitle("Provjera obaveza");

}

void PredmetQt::provjeraSajtova() {
    ProvjeraSajtovaQt *nw = new ProvjeraSajtovaQt();
    nw->show();
    nw->setWindowTitle("Provjera sajtova");
}
