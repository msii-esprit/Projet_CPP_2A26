#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sport.h"
#include <QMessageBox>

Sport sp;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(sp.afficher());
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::refresh()
{
    ui->tableView->setModel(sp.afficher());
}

void MainWindow::on_pushButton_clicked()
{
    int id = ui->lineEdit_id->text().toInt();
    QString nom = ui->lineEdit_nom->text();
    QString type = ui->comboBox_type->currentText();
    int nbr_p = ui->spinBox_nbr_p->text().toInt();
    int duree = ui->spinBox_duree->text().toInt();

    Sport S(id,nom,type,nbr_p,duree);
    bool test=S.ajouter();
    if(test)
    {

        QMessageBox::information(nullptr, QObject::tr("succes"),
                    QObject::tr("sport ajouté."), QMessageBox::Ok);
        refresh();


}
    else
        QMessageBox::critical(nullptr, QObject::tr("erreur"),
                    QObject::tr("erreur d'ajout."), QMessageBox::Ok);


}


void MainWindow::on_pushButton_4_clicked()
{
    int id = ui->lineEdit_id2->text().toInt();
    QString nom = ui->lineEdit_nom2->text();
    QString type = ui->comboBox_type2->currentText();
    int nbr_p = ui->spinBox_nbr_p2->text().toInt();
    int duree = ui->spinBox_duree_2->text().toInt();

    Sport S(id,nom,type,nbr_p,duree);
    bool test=S.modifier();
    if(test)
    {

        QMessageBox::information(nullptr, QObject::tr("succes"),
                    QObject::tr("sport modifié."), QMessageBox::Ok);
        refresh();


}
    else
        QMessageBox::critical(nullptr, QObject::tr("erreur"),
                    QObject::tr("erreur de modification."), QMessageBox::Ok);

}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    int id=ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),0)).toInt();
    QString res= QString::number(id);
    ui->lineEdit_id2->setText(res);
}

void MainWindow::on_comboBox_type_currentTextChanged(const QString &arg1)
{
    if (ui->comboBox_type->currentText()=="individuel") ui->spinBox_nbr_p->setValue(1);
    else  ui->spinBox_nbr_p->setValue(2);
}


void MainWindow::on_spinBox_nbr_p_valueChanged(int arg1)
{
    if (arg1 == 1) ui->comboBox_type->setCurrentText("individuel");
    else ui->comboBox_type->setCurrentText("collectif");
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEdit_id->setText("");
    ui->lineEdit_nom->setText("");
    ui->spinBox_nbr_p->setValue(1);
}

void MainWindow::on_pushButton_3_clicked()
{
    if(ui->tableView->currentIndex().row()==-1)
        QMessageBox::information(nullptr, QObject::tr("Suppression"),
                                 QObject::tr("Veuillez Choisir un sport du Tableau.\n"
                                             "Click Ok to exit."), QMessageBox::Ok);
    else
    {   int id=ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),0)).toInt();



        QString str = " Vous voulez vraiment supprimer \n le Visiteur :";
        int ret = QMessageBox::question(this, tr("Visiteur"),str,QMessageBox::Ok|QMessageBox::Cancel);

        switch (ret) {
        case QMessageBox::Ok:
            if (sp.supprimer(id)){


                QMessageBox::information(0, qApp->tr("Suppression"),

                                         qApp->tr("sport suprimée"), QMessageBox::Ok);

            }
            else
            {

                QMessageBox::critical(0, qApp->tr("Suppression"),
                                      qApp->tr("sport non trouvé "), QMessageBox::Ok);
            }



            break;
        case QMessageBox::Cancel:

            break;
        default:
            // should never be reached
            break;
        }

refresh();
    }
}
