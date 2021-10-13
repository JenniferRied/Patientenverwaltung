#ifndef VERWALTUNG_H
#define VERWALTUNG_H

#include <QDialog>
#include <QLabel>

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
    int housenumber;
    int id;
    int region_code;
    char sex;
    double phone;

public slots:
    void save();
    void control();

private:
    Ui::Verwaltung *ui;
};

#endif // VERWALTUNG_H
