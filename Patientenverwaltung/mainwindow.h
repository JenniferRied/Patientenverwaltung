#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "speicher.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public Beobachter
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    virtual void patient_updated() override;
public slots:
    void hinzufuegen_buttonclick();
    void aendern_buttonclick();
    void loeschen_buttonclick();
    void suchen_buttonclick();
    void export_buttonclick();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
