#ifndef PROVJERA_SAJTOVAQT_H
#define PROVJERA_SAJTOVAQT_H

#include <QWidget>
#include "predmet.h"
#include "ui_provjera_sajtovaqt.h"
#include <QVector>

class ProvjeraSajtovaQt : public QWidget
{
    Q_OBJECT
public:
    explicit ProvjeraSajtovaQt(QWidget *parent = 0);
    ~ProvjeraSajtovaQt();

private:
    Ui::ProvjeraSajtovaQt *ui;
private slots:
    void ispisi();
};

#endif // PROVJERA_SAJTOVAQT_H
