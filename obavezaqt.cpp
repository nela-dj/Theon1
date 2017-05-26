#include "mainwindow.h"
#include "ui_obavezaqt.h"
#include "predmet.h"
#include "predmetqt.h"
#include "obavezaqt.h"
#include <QWidget>
#include <QMessageBox>
ObavezaQt::ObavezaQt(QVector<Predmet>::iterator i, QWidget *parent) :
    QWidget(parent), predmet_it(i), ui(new Ui::ObavezaQt)
{
    ui->setupUi(this);
    this->setWindowTitle("Unos obaveze");
}

ObavezaQt::~ObavezaQt () {
    delete ui;
}

void ObavezaQt::dodaj() {
    QString tip=ui->TipEdit->text();
    Predmet::Obaveza::tip_obaveze t;
    if (tip == "test")
        t = Predmet::Obaveza::test;
    else if(tip=="kolokvijum")
        t = Predmet::Obaveza::kolokvijum;
    else if(tip=="seminarski")
        t = Predmet::Obaveza::seminarski_rad;
    else if(tip=="pismeni")
        t = Predmet::Obaveza::pismeni_ispit;
    else if(tip=="usmeni")
        t = Predmet::Obaveza::usmeni_ispit;
    else {
        QMessageBox::warning(this, "Neispravan tip",
                             "Tip mora biti: test, kolokvijum, seminarski, pismeni ili usmeni!",
                                      QMessageBox::Ok);
                return;
    }
    Vreme v(0);
    if (ui->VrijemeEdit->text() != "")
        v.citaj(ui->VrijemeEdit->text());

    Vreme r(0);
    if (ui->RokEdit->text() != "")
        r.citaj(ui->RokEdit->text());

    predmet_it->dodaj_obavezu(t, ui->MoguciEdit->text().toUShort(), ui->OsvojeniEdit->text().toUShort(),
                              v, r, ui->KomentarEdit->text());

    QMessageBox::about(this, "Uspjesno dodavanje", "Obaveza koju ste unijeli je dodata!");
    this->hide();

}
