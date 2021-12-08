#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "logement.h"
#include "ui_mainwindow.h"
#include "facture.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Logement L;
    Facture F;

private slots:


    void on_pb_ok_clicked();

    void on_bta_clicked();

    void on_Supprimer_clicked();

    void on_pushButton_9_clicked();

    void on_trielog_clicked();

    void on_trienbetoile_clicked();

    void on_triechambre_clicked();

    void on_recherche_clicked();

    void on_tab_log_doubleClicked(const QModelIndex &index);

    void on_pushButton_clicked();
    
    void on_add_clicked();

    void on_mailing_clicked();

    void on_tab_facture_doubleClicked(const QModelIndex &index);

    void on_pushButton_2_clicked();

    void on_recherche_pressed();

    void on_browse_clicked();

private:
    Ui::MainWindow *ui;
    QStringList files;
};

#endif // MAINWINDOW_H
