#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "Personnel.h"
#include "dumessengerconnectiondialog.h"
#include <QTcpSocket>

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
    void on_pushButton_Login_clicked();

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
    PERSONNEL P;
    QTcpSocket *mSocket;
};
#endif // MAINWINDOW_H
