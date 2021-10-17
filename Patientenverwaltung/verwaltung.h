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
    explicit Verwaltung(QWidget *parent = nullptr);
    ~Verwaltung();
    QString title;
    QString lastname;
    QString firstname;
    QString place;
    QString street;
    QString phone;
    QDate geb;
    int housenumber;
    int id;
    int region_code;
    QString sex;


public slots:
    void save();
    void change();
    void textchange(QString);
    void datechange(QDate);

private:
    Ui::Verwaltung *ui;
    Patient* patient;
};

#endif // VERWALTUNG_H
