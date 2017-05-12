#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "predmet.h"
#include "predmetqt.h"
#include <QFile>
#include <QTextStream>

//QVector<Predmet> predmeti;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dodajPredmet() {
    Predmet p(ui->NazivEdit->text(), ui->OcjenaEdit->text().toUShort(),
              ui->ProfesorEdit->text(), ui->KomentarEdit->toPlainText());
    predmeti.push_back(p);
    /*
    QFile file("out.txt");
    if (!file.open(QIODevice::WriteOnly |QIODevice::Append | QIODevice::Text))
        return;

    QTextStream out(&file);
    out << p.pisi() << endl;
    file.close();
    */
}
