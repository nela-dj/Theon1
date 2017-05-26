#ifndef PROVJERA_OBAVEZAQT_H
#define PROVJERA_OBAVEZAQT_H

#include <QWidget>
#include "predmet.h"
#include "ui_provjera_obavezaqt.h"
#include <QVector>

class ProvjeraObavezaQt : public QWidget
{
    Q_OBJECT
public:
    explicit ProvjeraObavezaQt(QString s="", QWidget *parent = 0);
    ~ProvjeraObavezaQt();
    QString obaveze;
private:
    Ui::ProvjeraObavezaQt *ui;
private slots:
    void ispisi();
};


#endif // PROVJERA_OBAVEZAQT_H
