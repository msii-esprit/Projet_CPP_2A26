#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "terrain.h"
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

    void on_ajouter_clicked();


    void on_supprimer_clicked();

    QModelIndex on_tableView_activated(QModelIndex index);

    void on_pushButton_2_clicked();

    void on_rechercher_clicked();

    void on_trier_clicked();

    void on_imprimerpdf_clicked();


private:
    Ui::MainWindow *ui;
    Terrain t;
};
#endif // MAINWINDOW_H
