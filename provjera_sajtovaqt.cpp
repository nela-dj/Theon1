#include "mainwindow.h"
#include "ui_provjera_sajtovaqt.h"
#include "predmet.h"
#include "predmetqt.h"
#include "provjera_sajtovaqt.h"
#include <QWidget>
#include <QMessageBox>
#include <QTextEdit>

ProvjeraSajtovaQt::ProvjeraSajtovaQt(QWidget *parent) :
    QWidget(parent), ui(new Ui::ProvjeraSajtovaQt)
{
    ui->setupUi(this);
    this->setWindowTitle("Provjera sajtova");
}

ProvjeraSajtovaQt::~ProvjeraSajtovaQt () {
    delete ui;
}

void ProvjeraSajtovaQt::ispisi() {
    QVector<QString> sajtovi;
    // otvaramo fajl za ucitavanje sajtova

    QFile file1("sajtovi.txt");
    if (!file1.open(QIODevice::ReadOnly |QIODevice::Text))
         return;
    QTextStream in1(&file1);

    // citamo sajtove u QVector<QString> sajtovi

    while (!in1.atEnd())
        sajtovi.push_back(in1.readLine());

    //zatvaramo fajl

    file1.close();

    //sada treba provjeriti jedan po jedan sajt
    //i ispisati one na kojima ima promjena od posljednje posjete korisnika
    //i naravno sacuvati nove html-ove
}
