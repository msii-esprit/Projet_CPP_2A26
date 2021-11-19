#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Personnel.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDate>
#include <QDebug>

#include <QAbstractSocket>

#include <QPrinter>
#include <QtPrintSupport/QPrinter>
#include <QPrintDialog>
#include <QDate>
#include<QFileDialog>
#include <QTextDocument>
#include <QTextStream>
#include <QPdfWriter>


#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QTextDocument>
#include <QDebug>
#include <QtPrintSupport/QPrinter>
#include<QIntValidator>
#include<QRegularExpression>


#include <QPainter>
#include <QDebug>
#include <QSqlQueryModel>

#include <QSystemTrayIcon>


#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

#include <QPrinter>
#include <QtPrintSupport/QPrinter>
#include <QPrintDialog>
#include <QDate>
#include<QFileDialog>
#include <QTextDocument>
#include <QTextStream>
#include <QPdfWriter>
#include <string>
#include <vector>
#include<QDirModel>
#include <qrcode.h>
#include <string>
#include <iostream>
#include <fstream>
#include <QtSvg/QSvgRenderer>
#include "qrcode.h"


using qrcodegen::QrCode;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) 
{
    ui->setupUi(this);
    //***********chat*************
    mSocket=new QTcpSocket(this);
    connect(mSocket,&QTcpSocket::readyRead,[&]()
    { QTextStream T(mSocket);
       auto text=T.readAll();
       ui->textEdit_2->append(text);
    });
    ui->le_CIN->setValidator ( new QIntValidator(0, 9999999, this));
    ui->le_Ntel->setInputMask("99999999");
    ui->le_Nom->setInputMask("A<AAAAAAAAAAAAA");
    ui->le_Prenom->setInputMask("A<AAAAAAA AAAAAAAA");
    ui->le_Email->setInputMask("NNNNNNNNNN@AAAAAAA.AA");
    ui->lineEdit_rechercher->setPlaceholderText(QString("Research"));
    ui->tableView_personnel->setModel(P.afficherPersonnel());
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
                        QObject::tr("echec.\n"
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
       { msgBox.setText("Modification successful.");
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

void MainWindow::on_pushButton_Trier_clicked()
{

      //  ui->tableView_personnel->setModel(P.trierPersonnel());


}


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
                        "<h1 style=\"text-align: center;\"><strong> "+TT+"</strong></h1>"
                        +"<img src=C:\\Users\\21650\\Desktop\\validation\\logo_project />"
                     "<h1 style=\"text-align: center;\"><strong> ******LISTE DES personnels ****** </strong></h1>"


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






void MainWindow::on_tableView_personnel_activated(const QModelIndex &index)
{

    ui->le_CIN->setText(ui->tableView_personnel->model()->data(ui->tableView_personnel->model()->index(index.row(),2)).toString());
    ui->le_Prenom->setText(ui->tableView_personnel->model()->data(ui->tableView_personnel->model()->index(index.row(),1)).toString());

    ui->le_Nom->setText(ui->tableView_personnel->model()->data(ui->tableView_personnel->model()->index(index.row(),0)).toString());
    ui->le_Ntel->setText(ui->tableView_personnel->model()->data(ui->tableView_personnel->model()->index(index.row(),5)).toString());

    ui->le_grade->setText(ui->tableView_personnel->model()->data(ui->tableView_personnel->model()->index(index.row(),3)).toString());
  //  ui->dateEdit->date(ui->tableView_personnel->model()->data(ui->tableView_personnel->model()->index(index.row(),5)).toString());

            ui->le_Adress->setText(ui->tableView_personnel->model()->data(ui->tableView_personnel->model()->index(index.row(),6)).toString());
              ui->le_Email->setText(ui->tableView_personnel->model()->data(ui->tableView_personnel->model()->index(index.row(),7)).toString());

}





void MainWindow::on_pb_envoyer_2_clicked()
{
    QTextStream T(mSocket);
    T<<ui->le_nickname_2->text()<<": "<<ui->le_message_2->text();
    mSocket->flush();
    ui->le_message_2->clear();
}

void MainWindow::on_pb_connecter_2_clicked()
{
    DuMessengerConnectionDialog D(this);
    if(D.exec()==QDialog::Rejected)
    {
        return;

    }
    mSocket->connectToHost(D.hostname(),D.port());
}






//login******************************
void MainWindow::on_pushButton_Login_clicked()
{
    QString username = ui->lineEdit_username->text();
           QString password = ui->lineEdit_password->text();

           if (username == "admin" && password == "admin") {
               QMessageBox::information(this, "Login", "Username and password are correct");
            ui->stackedWidget->setCurrentIndex(0);

           }
           else {
               QMessageBox::warning(this, "Login", "Username and password are not correct");
           }
}

void MainWindow::on_comboBox_activated()
{
    if(ui->comboBox_tri->currentText()=="tri par cin")
        ui->tableView_personnel->setModel(P.trierPersonnel());
    if(ui->comboBox_tri->currentText()=="tri par nom")
        ui->tableView_personnel->setModel(P.trierPersonnelNom());
    if(ui->comboBox_tri->currentText()=="tri par grade")
        ui->tableView_personnel->setModel(P.trierPersonnelGrade());

}

void MainWindow::on_comboBox_tri_activated()
{
    if(ui->comboBox_tri->currentText()=="tri par cin")
        ui->tableView_personnel->setModel(P.trierPersonnel());
    if(ui->comboBox_tri->currentText()=="tri par nom")
        ui->tableView_personnel->setModel(P.trierPersonnelNom());
    if(ui->comboBox_tri->currentText()=="tri par grade")
        ui->tableView_personnel->setModel(P.trierPersonnelGrade());
}



void MainWindow::on_pb_qrcode_clicked()
{


    PERSONNEL P;
        if(ui->tableView_personnel->currentIndex().row()==-1)
               QMessageBox::information(nullptr, QObject::tr("Suppression"),
                                        QObject::tr("Veuillez Choisir un PERSONNEL du Tableau.\n"
                                                    "Click Ok to exit."), QMessageBox::Ok);
           else
           {




                       P.setCIN(ui->le_CIN ->text().toInt());
                       P.setnom(ui->le_Nom ->text());
                       P.setN_tel(ui->le_Ntel ->text().toInt());
                       P.setemail(ui->le_Email ->text());
                       P.setgrade(ui->le_grade ->text());
                       P.setadress(ui->le_Adress ->text());
                       P.setprenom(ui->le_Prenom ->text());
                      // P.setdate_de_naissance(ui->dateEdit ->date());






             QString  rawQr = "CIN_P:%1 Nom_P:%2 PRENOM_P:%3 NUM_tel:%4 EMAIL:%5 GRADE:%6 ADRESSE:%7  " ;
                rawQr = rawQr.arg(P.getCIN()).arg(P.getnom()).arg(P.getprenom()).arg(P.getN_tel()).arg(P.getemail()).arg(P.getgrade()).arg(P.getadress());
                QrCode qr = QrCode::encodeText(rawQr.toUtf8().constData(), QrCode::Ecc::HIGH);



                std::ofstream myfile;
                myfile.open ("qrcode.svg") ;
                myfile << qr.toSvgString(1);
                myfile.close();
                QSvgRenderer svgRenderer(QString("qrcode.svg"));
                QPixmap pix( QSize(140, 140) );
                QPainter pixPainter( &pix );
                svgRenderer.render( &pixPainter );
                ui->label_qrcode->setPixmap(pix);

        }
}
