#include "mainwindow.h"
#include "ui_provjera_obavezaqt.h"
#include "predmet.h"
#include "predmetqt.h"
#include "provjera_obavezaqt.h"
#include <QWidget>
#include <QMessageBox>
#include <QTextEdit>

ProvjeraObavezaQt::ProvjeraObavezaQt(QString s, QWidget *parent) :
    QWidget(parent), obaveze(s), ui(new Ui::ProvjeraObavezaQt)
{
    ui->setupUi(this);
    this->setWindowTitle("Provjera obaveza");
}

ProvjeraObavezaQt::~ProvjeraObavezaQt () {
    delete ui;
}

void ProvjeraObavezaQt::ispisi() {
    ui->obavezeText->setPlainText(obaveze);
}
