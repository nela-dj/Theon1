#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "predmet.h"
#include "predmetqt.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QInputDialog>
#include <algorithm>
#include <QInputDialog>
#include "obavezaqt.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFile file("predmeti.txt");
    if (!file.open(QIODevice::ReadOnly |QIODevice::Text))
         return;
    QString pred_str = "";
    Predmet pred;
    QTextStream in(&file);
    // citamo predmet po predmet i proslijedjujemo funkciji koja cita predmet
    while (!in.atEnd()) {
           //za sada pretpostavljamo da je fajl u ispravnom formatu
           QString line = in.readLine();
           pred_str.append(line).append("\n");
           if (line == "}") {
               //pred_str.append(line);
               pred.citaj(pred_str);
               predmeti.push_back(pred);
               if(!in.atEnd())
                line = in.readLine();
               pred_str = "";
           }

       }
    //nakon sto smo procitali predmete u QVector<Predmet> predmeti zatvaramo fajl
    file.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dodajPredmet() {
    QString naziv;
    naziv = ui->NazivEdit->text();
    if (naziv=="")
    {
        QMessageBox::warning(this, "Neispravan naziv predmeta",
                             "Naziv predmeta ne moze biti prazan!", QMessageBox::Ok);
        return;
    }
    //dogovor je da korisnik u polje komenatara unese *
    //ako ne unosi novi predmet, vec dodaje obaveze/literaturu
    //predmetu koji vec postoji, tj. mijenja postojeci predmet

    if (!ui->KomentarEdit->toPlainText().startsWith("*"))
    {
        Predmet p(naziv, ui->OcjenaEdit->text().toUShort(),
                    ui->ProfesorEdit->text(), ui->KomentarEdit->toPlainText());

        predmeti.push_back(p);
        //upisujemo u fajl unijeti predmet
        QFile file("out.txt");
        if (!file.open(QIODevice::WriteOnly |QIODevice::Append | QIODevice::Text))
            return;

        QTextStream out(&file);
        out << p.pisi() << endl;
        file.close();

    }
    //ovo cu mozda kasnije da obrisem
    ui->dodajPredmet->setEnabled(false);

}

void MainWindow::dodajObavezu() {
    naziv = ui->NazivEdit->text();
    QVector<Predmet>::iterator i = predmeti.begin();
    for (; i!=predmeti.end(); i++)
        if (i->naziv()==naziv)
            break;
    if (i == predmeti.end()) {
        QMessageBox::warning(this, "Neispravan predmet",
                             "Predmet sa unijetim nazivom ne postoji!", QMessageBox::Ok);
        return;
    }

    ObavezaQt *nw = new ObavezaQt(i);
    nw->show();
    nw->setWindowTitle("Unos obaveze");

}

void MainWindow::dodajLiteraturu() {
    naziv=ui->NazivEdit->text();
    QVector<Predmet>::iterator i = predmeti.begin();
    for (;i!=predmeti.end() && naziv.trimmed()!=i->naziv(); i++)
        ;
    if (i == predmeti.end()) {
        QMessageBox::warning(this, "Neispravan predmet",
                             "Predmet sa unijetim nazivom ne postoji!", QMessageBox::Ok);
        return;
    }

    QString knjiga = QInputDialog::getText(this, "Unos literature", "Naziv knjige");

    // ako je unet naziv knjige, dodaje se u QVector literature
    if(!knjiga.isEmpty())
        i->dodaj_knjigu(knjiga);

    QMessageBox::about(this, "Uspjesno dodavanje", "Knjiga koju ste unijeli je dodata!");

}
