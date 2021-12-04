#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "connection.h"
#include <QFile>
#include <QFileDialog>
#include <QTextDocument>
#include <QDebug>
#include <QtPrintSupport/QPrinter>
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
    //appel connection////////////////////////////////////////////////////////////////////////////////////////////////
    Connection c;
    bool test=c.createconnect();
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    //louay////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ui->tableView->setModel(sp.afficher());

    //Syrine////////////////////////////////////////////////////////
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


void MainWindow::on_pushButton_17_clicked()
{
    QStackedWidget stackedWidget;
                        connect(ui->stackedWidget, SIGNAL(clicked()), this, SLOT(viewData));
                        QString username=ui->utilisateur->text();
                                QString password = ui->mdp->text();
                                if(username == "louay" && password == "louay")
                                { QMessageBox::information(this, "Login", "Username and password is correct, welcome louay");
                               //connect(ui->MainWindow->page_3, SIGNAL(on_connecter_clicked()), this, SLOT(viewData));
                                ui->stackedWidget->setCurrentIndex(1);
                                }
                                    //hide(); mainwindow = new MainWindow(this); mainwindow->show(); }
                                    else if(username == "syrine" && password == "syrine")
                                { QMessageBox::information(this, "Login", "Username and password is correct, welcome syrine");
                                   ui->stackedWidget->setCurrentIndex(2);
                                }
                                        //hide(); mainwindow = new MainWindow(this); mainwindow->show(); }
                                        else if(username == "amine" && password == "amine")
                                        { QMessageBox::information(this, "Login", "Username and password is correct, welcome amine");
                                   ui->stackedWidget->setCurrentIndex(3);
                                }
                                            //hide(); mainwindow = new MainWindow(this); mainwindow->show(); }
                                            else if(username == "yomna" && password == "yomna")
                                            { QMessageBox::information(this, "Login", "Username and password is correct, welcome yomna");
                                   ui->stackedWidget->setCurrentIndex(4);
                                }
                                else if(username == "hazem" && password == "hazem")
                            { QMessageBox::information(this, "Login", "Username and password is correct, welcome hazem");
                               ui->stackedWidget->setCurrentIndex(5);
                            }
                                                //hide(); mainwindow = new MainWindow(this); mainwindow->show(); }
                                             else if(username == "omar" && password == "omar")
                                                { QMessageBox::information(this, "Login", "Username and password is correct, welcome omar"
                                                                                          ""
                                                                                          ""
                                                                                          "");
                                   ui->stackedWidget->setCurrentIndex(6);
                                }
}

//louay///////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
        test=sp.ajouter_mod(id,"ajout",QDateTime::currentDateTime());
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
        test=sp.ajouter_mod(id,"modification",QDateTime::currentDateTime());
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
                bool test=sp.ajouter_mod(id,"suppression",QDateTime::currentDateTime());

                QMessageBox::information(0, qApp->tr("Suppression"),

                                         qApp->tr("sport suprimée"), QMessageBox::Ok);
              //  refresh();

            }
            else
            {

                QMessageBox::critical(0, qApp->tr("Suppression"),
                                      qApp->tr("sport non supprimé "), QMessageBox::Ok);
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

void MainWindow::on_pushButton_5_clicked()
{
    QString cls;
    if (ui->radioButton->isChecked()) cls=" ASC";
    else if (ui->radioButton_2->isChecked()) cls=" DESC";
    ui->tableView->setModel(sp.triNom(cls));
}

void MainWindow::on_pushButton_6_clicked()
{
    QString cls;
    if (ui->radioButton->isChecked()) cls=" ASC";
    else if (ui->radioButton_2->isChecked()) cls=" DESC";
    ui->tableView->setModel(sp.triNbr_p(cls));

}




void MainWindow::on_lineEdit_5_returnPressed()
{
    ui->tableView->setModel(sp.recherche(ui->lineEdit_5->text()));
}

void MainWindow::on_pushButton_8_clicked()
{
    QString strStream;
                          QTextStream out(&strStream);

                           const int rowCount = ui->tableView->model()->rowCount();
                           const int columnCount = ui->tableView->model()->columnCount();
                          out <<  "<html>\n"
                          "<head>\n"
                                           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                           <<  QString("<title>%1</title>\n").arg("strTitle")
                                           <<  "</head>\n"
                                           "<body bgcolor=#ffffff link=#5000A0>\n"

                                          //     "<align='right'> " << datefich << "</align>"
                                           "<center> <H1>Liste des Sports</H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                                       // headers
                                       out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                                       out<<"<cellspacing=10 cellpadding=3>";
                                       for (int column = 0; column < columnCount; column++)
                                           if (!ui->tableView->isColumnHidden(column))
                                               out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
                                       out << "</tr></thead>\n";

                                       // data table
                                       for (int row = 0; row < rowCount; row++) {
                                           out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                                           for (int column = 0; column < columnCount; column++) {
                                               if (!ui->tableView->isColumnHidden(column)) {
                                                   QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                                                   out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                               }
                                           }
                                           out << "</tr>\n";
                                       }
                                       out <<  "</table> </center>\n"
                                           "</body>\n"
                                           "</html>\n";

                                 QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
                                   if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

                                  QPrinter printer (QPrinter::PrinterResolution);
                                   printer.setOutputFormat(QPrinter::PdfFormat);
                                  printer.setPaperSize(QPrinter::A4);
                                 printer.setOutputFileName(fileName);

                                  QTextDocument doc;
                                   doc.setHtml(strStream);
                                   doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                                   doc.print(&printer);
}





void MainWindow::on_pushButton_9_clicked()
{
    QString cls;
    if (ui->radioButton->isChecked()) cls=" ASC";
    else if (ui->radioButton_2->isChecked()) cls=" DESC";
    ui->tableView->setModel(sp.triType(cls));
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    sp.statistiques(ui->widget);
    ui->tableView_2->setModel(sp.afficher_mod());
}

//Syrine///////////////////////////////////////////////////////////////////////
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
