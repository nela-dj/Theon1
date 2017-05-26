#ifndef _PREDMETQT_H_
#define _PREDMETQT_H_

#include <QWidget>
#include "predmet.h"
#include <QVector>
#include <stdexcept>
#include <QFile>
#include "ui_predmetqt.h"

using namespace std;

static QVector<Predmet> predmeti;

class PredmetQt : public QWidget {
    Q_OBJECT
public:
    explicit PredmetQt(QWidget *roditelj = 0);
    ~PredmetQt();
private:
    Ui::PredmetQt *ui;
private slots:
    void pokreni();
    void unosPredmeta();
    void provjeraObaveza();
    void provjeraSajtova();
};






#endif // _PREDMETQT_H_
