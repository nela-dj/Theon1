#ifndef _PREDMETQT_H_
#define _PREDMETQT_H_

#include <QWidget>
#include "predmet.h"
#include <QVector>
#include <stdexcept>
#include <QFile>
#include "ui_predmetqt.h"
using namespace std;
//mozda ce trebati da se ukljuci <qsignalmapper.h>

static QVector<Predmet> predmeti;

class PredmetQt : public QWidget {
    Q_OBJECT
public:
    explicit PredmetQt(QWidget *roditelj = 0);
    ~PredmetQt();
private:
    Ui::PredmetQt *ui;
    QFile fajl;
private slots:
    void pokreni();
    void nastavi();

};






#endif // _PREDMETQT_H_
