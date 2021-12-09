#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "terrain.h"
#include <QComboBox>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QDebug>
#include <QValidator>
#include <QIntValidator>
#include <QSystemTrayIcon>
#include <QDate>
#include <QTextDocument>
#include "notification.h"
#include <QPrinter>
#include <QtPrintSupport/QPrinter>
#include <QPrintDialog>
#include <QDate>
#include<QFileDialog>
#include <QTextDocument>
#include <QTextStream>
#include <QPdfWriter>


//hi
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(t.afficher());
    ui->capacite_TU->setInputMask("99999");

}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_ajouter_clicked()
{

    Notification N;
    int capacite=ui->capacite_TU->text().toInt();
    QString type_T=ui->type_TU->currentText();
    QString nom_T=ui->nom_TU->currentText();
    QString etat_T=ui->etat_TU->currentText();
    qDebug()<< nom_T;
    Terrain t(capacite,nom_T,type_T,etat_T);
    bool test=t.ajouter();
    QMessageBox msgbox;

    if(test)
    {

        msgbox.setText("ajout avec succes.");
         N.notification_ajoutterrain();
    ui->tableView->setModel(t.afficher());
    }
    else
        msgbox.setText("echec d'ajout");
        msgbox.exec();


}



void MainWindow::on_supprimer_clicked()
{   QModelIndex index;
    Notification N;
    index=on_tableView_activated(index);
    QVariant value=ui->tableView->model()->data(index);
    QString S=value.toString();

    Terrain t1;
    bool test=t1.supprimer(S);
    QMessageBox msgbox;

    if(test)
    {N.notification_supprimerterrain();
        ui->tableView->setModel(t.afficher());
        msgbox.setText("suppression avec succes.");
    }
    else
        msgbox.setText("echec de suppression");
        msgbox.exec();
}

QModelIndex MainWindow::on_tableView_activated( QModelIndex index)
{
    index=ui->tableView->currentIndex();
    return index;

}


void MainWindow::on_pushButton_2_clicked()//modifier
{
    Notification N;
    QModelIndex index;
    index=on_tableView_activated(index);
    QVariant value=ui->tableView->model()->data(index);
    QString S=value.toString();
    QString etat_T=ui->etat_TU->currentText();
    int capacite=ui->capacite_TU->text().toInt();
    qDebug()<< capacite;


    Terrain t(capacite,S,"piscine",etat_T);
    qDebug()<< S;
   bool test=t.modifier(S);
   QMessageBox msgbox;
   if(test)
   {N.notification_modifierterrain();
       msgbox.setText("modification avec succes.");
   ui->tableView->setModel(t.afficher());
   }
else
      msgbox.setText("echec de modification.");
}


void MainWindow::on_rechercher_clicked()
{
    Terrain t;
      ui->tableView->setModel(t.rechercher(ui->rechercher_TU->text()));
}



void MainWindow::on_trier_clicked()
{
    Terrain t;
       if(ui->radioButton->isChecked())
       {ui->tableView->setModel(t.trier_n());}
       else if(ui->radioButton_2->isChecked())
       {ui->tableView->setModel(t.trier_t());}
       else if(ui->radioButton_3->isChecked())
       {ui->tableView->setModel(t.trier_c());}

}



void MainWindow::on_imprimerpdf_clicked()
{
    QString strStream;
                         QTextStream out(&strStream);

                         const int rowCount = ui->tableView->model()->rowCount();
                         const int columnCount = ui->tableView->model()->columnCount();
                         QString TT = QDate::currentDate().toString("yyyy/MM/dd");
                         out <<"<html>\n"
                               "<head>\n"
                                "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                             << "<title>ERP - terrain <title>\n "
                             << "</head>\n"
                             "<body bgcolor=#ffffff link=#5000A0>\n"
                             "<h1 style=\"text-align: center;\"><strong> ******LISTE des terrains ******"+TT+" </strong></h1>"
                             "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
                               "</br> </br>";
                         // headers
                         out << "<thead><tr bgcolor=#d6e5ff>";
                         for (int column = 0; column < columnCount; column++)
                             if (!ui->tableView->isColumnHidden(column))
                                 out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
                         out << "</tr></thead>\n";

                         // data table
                         for (int row = 0; row < rowCount; row++) {
                             out << "<tr>";
                             for (int column = 0; column < columnCount; column++) {
                                 if (!ui->tableView->isColumnHidden(column)) {
                                     QString data =ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                                     out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                 }
                             }
                             out << "</tr>\n";
                         }
                         out <<  "</table>\n"
                             "</body>\n"
                             "</html>\n";

                         QTextDocument *document = new QTextDocument();
                         document->setHtml(strStream);

                         QPrinter printer;

                         QPrintDialog *dialog = new QPrintDialog(&printer, nullptr);
                         if (dialog->exec() == QDialog::Accepted) {
                             document->print(&printer);
                         }

                         delete document;


}

