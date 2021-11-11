#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "Personnel.h"


//Test Tutoriel Git

#include <QMainWindow>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_ajouter_clicked();
    //void on_pushButtonSupprimer_clicked();

    void on_pushButton_afficher_clicked();

    void on_pushButtonSupprimer_clicked();

    void on_pushButton_mise_a_jour_clicked();
bool search(int);
private:
    Ui::MainWindow *ui;
    PERSONNEL P;
};
#endif // MAINWINDOW_H
