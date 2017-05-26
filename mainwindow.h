#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "predmetqt.h"
#include "ui_mainwindow.h"
namespace Ui {
class MainWindow;
}

static QString naziv;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
private slots:
    void dodajPredmet();
    void dodajObavezu();
    void dodajLiteraturu();
};

#endif // MAINWINDOW_H
