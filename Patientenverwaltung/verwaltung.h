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

private:
    Ui::Verwaltung *ui;
};

#endif // VERWALTUNG_H
