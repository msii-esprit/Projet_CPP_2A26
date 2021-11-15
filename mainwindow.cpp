#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Personnel.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDate>
#include <QDebug>


#include <QPrinter>
#include <QtPrintSupport/QPrinter>
#include <QPrintDialog>
#include <QDate>
#include<QFileDialog>
#include <QTextDocument>
#include <QTextStream>
#include <QPdfWriter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_CIN->setValidator ( new QIntValidator(0, 9999999, this));
    ui->le_Ntel->setInputMask("99999999");
    ui->le_Nom->setInputMask("A<AAAAAAAAAAAAA");
    ui->le_Prenom->setInputMask("A<AAAAAAA AAAAAAAA");
    ui->le_Email->setInputMask("NNNNNNNNNN@AAAAAAA.AA");


}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::search(int t)
{bool test=false;

       for (int var = 0; var < ui->tableView_personnel->model()->rowCount(); ++var) {
           if(ui->tableView_personnel->model()->index(var,2).data().toInt()==t){

              test=true;
           }
       }
       return test;
}

void MainWindow::on_pb_ajouter_clicked()
{
    QString nom=ui->le_Nom->text();
    QString prenom=ui->le_Prenom->text();
    int CIN=ui->le_CIN->text().toInt();
    QString grade=ui->le_grade->text();
    QDate date_de_naissance=ui->dateEdit->date();

    QString adress=ui->le_Adress->text();
    QString email=ui->le_Email->text();
    int  N_tel=ui->le_Ntel->text().toInt();


  PERSONNEL P(nom,prenom,CIN,grade,date_de_naissance,N_tel,adress,email);

     bool test=P.ajouter();

     if(test)
     {
         //Refresh affichage
             ui->tableView_personnel->setModel(P.afficherPersonnel());
         QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("ajout effectue\n"),QObject::tr("click cancel to exit"));
     }else
     {
         QMessageBox::critical(nullptr,QObject::tr("not ok"),QObject::tr("ajout non effectue"),QObject::tr("click cancel to exit"));
     }
 }


void MainWindow::on_pushButton_afficher_clicked()
{
    ui->tableView_personnel->setModel(P.afficherPersonnel());
}

void MainWindow::on_pushButtonSupprimer_clicked()
{
 QMessageBox msgBox;
    PERSONNEL P1;
        P1.setCIN(ui->le_CIN ->text().toInt());
        int c=P1.getCIN();
        bool t=search(c);
        qDebug() << t;
        if(t==false)
        {
            QMessageBox::critical(nullptr, QObject::tr("CIN exist"),
                        QObject::tr("supression failed.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }

        else
           {
        bool test=P1.supprimerPersonnel(P1.getCIN());



        if(test)
           { msgBox.setText("suppression  avec succes.");
            ui->tableView_personnel->setModel(P1.afficherPersonnel());
           }
        else
        {
            msgBox.setText("Echec de suppression.!!!");
            msgBox.exec();
            ui->le_CIN->clear();
            ui->le_Nom->clear();
            ui->le_Ntel->clear();
            ui->le_Email->clear();
            ui->le_grade->clear();
            ui->le_Prenom->clear();

            ui->le_Adress->clear();
        }
}
}

void MainWindow::on_pushButton_mise_a_jour_clicked()
{

    QString nom=ui->le_Nom->text();
    QString prenom=ui->le_Prenom->text();
    int CIN=ui->le_CIN->text().toInt();
    QString grade=ui->le_grade->text();
    QDate date_de_naissance=ui->dateEdit->date();
    int  N_tel=ui->le_Ntel->text().toInt();
    QString adress=ui->le_Adress->text();
    QString email=ui->le_Email->text();

    PERSONNEL P(nom,prenom,CIN,grade,date_de_naissance,N_tel,adress,email);


    bool test=P.modifierPersonnel(P.getnom(),P.getprenom(),P.getCIN(),P.getgrade(),P.getdate_de_naissance(),P.getN_tel(),P.getadress(),P.getemail());


    QMessageBox msgBox;

    if(test)
       { msgBox.setText("Modification avec succes.");
        ui->tableView_personnel->setModel(P.afficherPersonnel());
       }
    else
    {
        msgBox.setText("Echec de Modification.!!!");
        msgBox.exec();

        ui->le_CIN->clear();
        ui->le_Nom->clear();
        ui->le_Ntel->clear();
        ui->le_Email->clear();
        ui->le_grade->clear();
        ui->le_Prenom->clear();
        ui->le_Adress->clear();

}
}
/*

void MainWindow::on_pushButton_Trier_clicked()
{
    if(P.trierPersonnel())
    {
        ui->tableView_personnel->setModel(P.trierPersonnel());

    }
}



*/





void MainWindow::on_lineEdit_rechercher_textChanged()
{
    QString rech=ui->lineEdit_rechercher->text();
    ui->tableView_personnel->setModel(P.chercherPersonnel(rech));
}

void MainWindow::on_pushButton_PDF_clicked()
{
    QString strStream;
       strStream = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
           if (QFileInfo(strStream).suffix().isEmpty()) { strStream.append(".pdf"); }

           QPrinter printer(QPrinter::PrinterResolution);
           printer.setOutputFormat(QPrinter::PdfFormat);
           printer.setPaperSize(QPrinter::A4);
           printer.setOutputFileName(strStream);
          // printer.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/Ahmed.A.Hsouna/Desktop/Ahmed_Amin_Ben_Hsouna/logo.png"));


                 QTextStream out(&strStream);

                 const int rowCount = ui->tableView_personnel->model()->rowCount();
                 const int columnCount = ui->tableView_personnel->model()->columnCount();
                 QString TT = QDateTime::currentDateTime().toString();
                 out <<"<html>\n"
                       "<head>\n"
                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                     << "<title>ERP - COMmANDE LIST<title>\n "
                     << "</head>\n"
                     "<body bgcolor=#ffffff link=#5000A0>\n"
                     "<h1 style=\"text-align: center;\"><strong> ******LISTE DES personnels ****** "+TT+"</strong></h1>"
                    //   " <img src="logo.png" alt="Trulli" width="500" height="333">"
                     "<table style=\"text-align: center; font-size: 10px;\" border=1>\n "
                       "</br> </br>";
                 // headers
                 out << "<thead><tr bgcolor=#d6e5ff>";
                 for (int column = 0; column < columnCount; column++)
                     if (!ui->tableView_personnel->isColumnHidden(column))
                         out << QString("<th>%1</th>").arg(ui->tableView_personnel->model()->headerData(column, Qt::Horizontal).toString());
                 out << "</tr></thead>\n";

                 // data table
                 for (int row = 0; row < rowCount; row++) {
                     out << "<tr>";
                     for (int column = 0; column < columnCount; column++) {
                         if (!ui->tableView_personnel->isColumnHidden(column)) {
                             QString data =ui->tableView_personnel->model()->data(ui->tableView_personnel->model()->index(row, column)).toString().simplified();
                             out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                         }
                     }
                     out << "</tr>\n";
                 }
                 out <<  "</table>\n"
                     "</body>\n"
                     "</html>\n";

                 QTextDocument document;
                 document.setHtml(strStream);
                 document.print(&printer);

}
