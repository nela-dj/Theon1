#ifndef OBAVEZAQT_H
#define OBAVEZAQT_H

#include <QWidget>
#include "predmet.h"
#include "ui_obavezaqt.h"
#include <QVector>

class ObavezaQt : public QWidget
{
    Q_OBJECT
public:
    explicit ObavezaQt(QVector<Predmet>::iterator i, QWidget *parent = 0);
    ~ObavezaQt();
    QVector<Predmet>::iterator predmet_it;
private:
    Ui::ObavezaQt *ui;
private slots:
    void dodaj();
};


#endif // OBAVEZAQT_H
