#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sport.h"
#include "Personnel.h"
#include "dumessengerconnectiondialog.h"
#include <QTcpSocket>
#include "participant.h"

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
public slots:
    void on_pushButtonajouterclicked();
public slots:

    void connectEquipe();
    void on_pushButton66_clicked();
    void connectEquipeM();

    QModelIndex on_tableView_activated( QModelIndex index);
bool search1(int);


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
    // hazem //////////// //

    void on_pb_ok_clicked();

    void on_bta_clicked();

    void on_Supprimer_clicked();

    void on_pushButton_10_clicked();

    void on_trielog_clicked();

    void on_trienbetoile_clicked();

    void on_triechambre_clicked();



    void on_tab_log_doubleClicked(const QModelIndex &index);

    void on_pushButton_11_clicked();

    void on_add_clicked();

    void on_mailing_clicked();

    void on_tab_facture_doubleClicked(const QModelIndex &index);

    void on_pushButton_7_clicked();

    void on_recherche_pressed();

    void on_browse_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_13_clicked();

    void on_comboBox1_activated(int index);
// ///////////////////////mohamed amine nouira ///////////////////:






void on_pushButton_modifier_clicked();



void on_buttonBox_accepted();

void on_buttonBox_rejected();





void on_lineEdit_R_returnPressed();




void on_pushButton_predict_clicked();


void on_tableWidget_5_activated( QModelIndex index);



void on_comboBox_class1_1_currentIndexChanged(int index);

void on_comboBox_class1_2_currentIndexChanged(int index);

void on_comboBox_class1_3_currentIndexChanged(int index);

void on_comboBox_class1_4_currentIndexChanged(int index);

void on_comboBox_class2_1_currentIndexChanged(int index);

void on_comboBox_class2_2_currentIndexChanged(int index);

void on_comboBox_class2_3_currentIndexChanged(int index);

void on_comboBox_class2_4_currentIndexChanged(int index);

void on_comboBox_class3_1_currentIndexChanged(int index);

void on_comboBox_class3_2_currentIndexChanged(int index);

void on_comboBox_class3_3_currentIndexChanged(int index);

void on_comboBox_class3_4_currentIndexChanged(int index);

void on_comboBox_class4_1_currentIndexChanged(int index);

void on_comboBox_class4_2_currentIndexChanged(int index);

void on_comboBox_class4_3_currentIndexChanged(int index);

void on_comboBox_class4_4_currentIndexChanged(int index);

void on_pushButton_tirage5_clicked();

void on_toolButton_clicked();

void on_lineEdit_R_cursorPositionChanged(int arg1, int arg2);



void on_tableView_2_clicked(const QModelIndex &index);

void on_tableView_3_activated(const QModelIndex &index);

void on_button_2_clicked();
void on_pushButton_19_clicked();

private:
    Ui::MainWindow *ui;
    //louay
    Sport sp;

    participant p;

    //Syrine
    PERSONNEL P;
    QTcpSocket *mSocket;
    QStringList files;
    int y;
};
#endif // MAINWINDOW_H
