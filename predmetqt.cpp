#include "predmetqt.h"
#include <QIODevice>
#include <QTextStream>
#include "ui_predmetqt.h"
#include "mainwindow.h"

PredmetQt::PredmetQt (QWidget* roditelj) :
        QWidget(roditelj),
        ui(new Ui::PredmetQt)
{
    ui->setupUi(this);
    this->setWindowTitle("Welcome!");
    ui->Nastavi->setEnabled(false);
}


PredmetQt::~PredmetQt() {
    delete ui;
}

void PredmetQt::pokreni() {
    QFile file("predmeti.txt");
       if (!file.open(QIODevice::ReadOnly |QIODevice::Text))
           return;
       QString pred_str = "";
       Predmet pred;
       QTextStream in(&file);
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

       file.close();
       ui->Pokreni->setEnabled(false);
       ui->Nastavi->setEnabled(true);
}

void PredmetQt::nastavi() {
    //ui->retranslateUi(this);

    QFile file("out.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    for(QVector<Predmet>::const_iterator i=predmeti.cbegin(); i!=predmeti.cend(); i++)
        out << i->pisi() << endl;
    file.close();
    MainWindow *nw = new MainWindow();
    this->hide();
    nw->show();
    nw->setWindowTitle("Theon");



}
