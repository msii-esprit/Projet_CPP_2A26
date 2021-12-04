#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sport.h"
#include "Personnel.h"
#include "dumessengerconnectiondialog.h"
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void refresh();

private slots:
    void on_pushButton_17_clicked();

    //louay
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_comboBox_type_currentTextChanged(const QString &arg1);

    void on_spinBox_nbr_p_valueChanged(int arg1);

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_lineEdit_5_returnPressed();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_tabWidget_currentChanged(int index);

    //Syrine////////////////////

    void on_pb_ajouter_clicked();


    void on_pushButton_afficher_clicked();

    void on_pushButtonSupprimer_clicked();

    void on_pushButton_mise_a_jour_clicked();

    bool search(int);

    void on_pushButton_Trier_clicked();

    void on_lineEdit_rechercher_textChanged();

    void on_pushButton_PDF_clicked();

    void on_pb_qrcode_clicked();

    void on_tableView_personnel_activated(const QModelIndex &index);

    void on_pb_envoyer_2_clicked();

    void on_pb_connecter_2_clicked();

    void on_comboBox_activated();

    void on_comboBox_tri_activated();

private:
    Ui::MainWindow *ui;
    //louay
    Sport sp;

    //Syrine
    PERSONNEL P;
    QTcpSocket *mSocket;
};
#endif // MAINWINDOW_H
