#ifndef VERWALTUNG_H
#define VERWALTUNG_H

#include <QDialog>

namespace Ui {
class Verwaltung;
}

class Verwaltung : public QDialog
{
    Q_OBJECT

public:
    explicit Verwaltung(QWidget *parent = nullptr);
    ~Verwaltung();
    std::string title;
    std::string lastname;
    std::string firstname;
    std::string place;
    std::string street;
    int housenumber;
    int id;
    int region_code;
    char sex;

public slots:
    void save();

private:
    Ui::Verwaltung *ui;
};

#endif // VERWALTUNG_H
