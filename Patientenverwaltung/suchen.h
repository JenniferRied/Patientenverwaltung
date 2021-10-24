#ifndef SUCHE_H
#define SUCHE_H
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMainWindow>

class QLineEdit;
class QPushButton;

class Suchen : public QDialog
{
    Q_OBJECT

public:
     Suchen(QWidget *parent = 0);
     QString get_suchen_text();

public slots:
     void button_gedrueckt();

private:
     QPushButton *button;
     QLineEdit *suchleiste;
     QString suchen_text;
     Suchen *suche;
};

#endif // SUCHE_H
