#ifndef VERWALTUNG_H
#define VERWALTUNG_H

#include <QDialog>
#include <QLabel>
#include <QDate>
#include "patient.h"

namespace Ui {
class Verwaltung;
}

class Verwaltung : public QDialog
{
    Q_OBJECT

public:
    explicit Verwaltung(int patienten_id, QWidget *parent = nullptr);
    ~Verwaltung();

public slots:
    void change();
    void textchange(QString);
    void datechange(QDate);
    void ueberpruefen();
    void abgebrochen();

private:
    Ui::Verwaltung *ui;
    void patienten_editieren(int);
    int id = 0;
    void save();
};

#endif // VERWALTUNG_H
