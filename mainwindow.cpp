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
#include "facture.h"
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
#include "envoiefactureparmail.h"
#include "exel.h"
#include "logement.h"
#include "facture.h"


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
    Facture F;
    Logement L;

    ui->tab_log->setModel(L.afficher());

    ui->tab_facture->setModel(F.afficher());
    //ui->nbr_etoile->setValidator(new QIntValidator (0,9,this));

    ui->nom_logement->setInputMask("AAAAAAAAAAAA");
    ui->nbr_ch->setInputMask("9999");
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
                                ui->stackedWidget->setCurrentIndex(2);
                                }
                                    //hide(); mainwindow = new MainWindow(this); mainwindow->show(); }
                                    else if(username == "syrine" && password == "syrine")
                                { QMessageBox::information(this, "Login", "Username and password is correct, welcome syrine");
                                   ui->stackedWidget->setCurrentIndex(3);
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
                               ui->stackedWidget->setCurrentIndex(1);
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

void MainWindow::on_pb_ok_clicked()
{
Logement L1;
    QString nom_logement=ui->nom_logement->text();
    int Nbr_etoile=ui->nbr_etoile->text().toInt();
    QString adresse_l=ui->adresse->currentText();
    int Nbr_ch=ui->nbr_ch->text().toInt();
    QString disponibilite=ui->disponibilite->currentText();
    QString type_l=ui->type->currentText();
    QString in_out=ui->in_out->text();
    L1.setin_out(ui->in_out->text());
    Logement L(Nbr_etoile,Nbr_ch, nom_logement,disponibilite , type_l, adresse_l,in_out);
     ui->nom_logement->setText("");
    // ui->nbr_etoile->setText("");
    bool mail = L.EmailValide(L.getin_out());
    if (mail)
    {

        bool test = L.ajouter();

        if(test)
        {
            QMessageBox::information(nullptr, QObject::tr("ajout "),
                        QObject::tr("ajout effectuer.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
            ui->tab_log->setModel(L.afficher());

    }
        else
            QMessageBox::critical(nullptr, QObject::tr("ajout"),
                        QObject::tr("erreur d'ajout.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

            }
                else
                    QMessageBox::critical(nullptr, QObject::tr("Email"),
                                QObject::tr("mail non valide.\n"
                                            "exemple@gmail.com\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);



}

void MainWindow::on_bta_clicked()
{
    Logement L;

    ui->tab_log->setModel(L.afficher());
}

void MainWindow::on_Supprimer_clicked()
{
    Logement L1 , L2;
    Logement L;
    L1.setnom_logement(ui->sup->text());
    bool test =L1.supprimer(L1.getnom_logement());
     if(test)
             {
                 QMessageBox::information(nullptr, QObject::tr("ajout "),
                             QObject::tr("suppresion effectuer.\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);
                 ui->tab_log->setModel(L.afficher());

         }
             else
                 QMessageBox::critical(nullptr, QObject::tr("ajout"),
                             QObject::tr("erreur de suppression.\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);
}


void MainWindow::on_pushButton_10_clicked()
{

    QString nom_logement=ui->nom_logement->text();
    int Nbr_etoile=ui->nbr_etoile->text().toInt();
    QString adresse_l=ui->adresse->currentText();
    int Nbr_ch=ui->nbr_ch->text().toInt();
    QString disponibilite=ui->disponibilite->currentText();
    QString type_l=ui->type->currentText();
    QString in_out=ui->in_out->text();
    Logement L(Nbr_etoile ,Nbr_ch, nom_logement,disponibilite , type_l, adresse_l,in_out);
    bool test = L.modifier(L.getnom_logement());
    if (test )
    {
        QMessageBox::information(nullptr, QObject::tr("update "),
                    QObject::tr("modification effectuer.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tab_log->setModel(L.afficher());

}
    else
        QMessageBox::critical(nullptr, QObject::tr("update"),
                    QObject::tr("erreur de modification.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_trielog_clicked()
{
    Logement L;
    ui->tab_log->setModel(L.trieLogement());
}

void MainWindow::on_trienbetoile_clicked()
{
    Logement L;
    ui->tab_log->setModel(L.trienbetoile());
}

void MainWindow::on_triechambre_clicked()
{
    Logement L;
    ui->tab_log->setModel(L.trienbch());
}

/*void MainWindow::on_recherche_clicked()
{
    Logement L;
   // QString aux;
   // QString no = ui->cherche->text();

  //  L.setnom_logement(aux);
//aux = ui->cherche->text();
    bool test = L.recherche(ui->cherche->text());
    QString no =ui->cherche->text();
       // ui->tab_log->setModel(L.recherche(ui->cherche->text()));

    if (test)
    {

        ui->tab_log->setModel(L.recherche(ui->cherche->text()));

}
    else
        QMessageBox::critical(nullptr, QObject::tr("recherche"),
                    QObject::tr("erreur de recherche.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}
*/
void MainWindow::on_tab_log_doubleClicked(const QModelIndex &index)
{
    QSqlQuery Query;
    QString nom=ui->tab_log->model()->data(index).toString();
    Query.prepare("SELECT* FROM LOGMENT WHERE nom_log = '"+nom+"'");
    if (Query.exec())
    {
        while   (Query.next())
        {
            ui->nom_logement->setText(Query.value(0 ).toString());
            ui->nbr_etoile->setValue(Query.value(1 ).toInt());
            ui->adresse->setCurrentText(Query.value(2 ).toString());
            ui->nbr_ch->setText(Query.value(3 ).toString());
            ui->disponibilite->setCurrentText(Query.value(4 ).toString());
            ui->type->setCurrentText(Query.value(5 ).toString());
            ui->in_out->setText(Query.value(6 ).toString());
            ui->sup->setText(Query.value(0).toString());

        }
    }
}







void MainWindow::on_add_clicked()
{
  int  cin =ui->cin->text().toInt();
  QString nom=ui->nom->text();
  QString prenom=ui->prenom->text();
  int nbr= ui->nbr->text().toInt();
  int duree = ui->duree->text().toInt();

//float prix=500;
  Logement L;
Facture F1;
  int somme = F1.CalculSomme(150,duree);
  QString email=ui->mailiiinf->text();
  Facture F(cin,nom,prenom,nbr,duree,somme,email);


  bool test = F.ajouter();
  ui->tab_facture->setModel(F.afficher());
  if (test)

      {
          QMessageBox::information(nullptr, QObject::tr("ajout "),
                      QObject::tr("ajout effectuer.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
          ui->tab_log->setModel(L.afficher());

  }
      else
          QMessageBox::critical(nullptr, QObject::tr("ajout"),
                      QObject::tr("erreur d'ajout.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);}



void MainWindow::on_pushButton_11_clicked()
{
    QString strStream;
        strStream = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
            if (QFileInfo(strStream).suffix().isEmpty()) { strStream.append(".pdf"); }

            QPrinter printer(QPrinter::PrinterResolution);
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setPaperSize(QPrinter::A4);
            printer.setOutputFileName(strStream);


                  QTextStream out(&strStream);

                  //const int rowCount = ui->tab_facture->model()->rowCount();
                  const int columnCount = ui->tab_facture->model()->columnCount();
                  QString TT = QDateTime::currentDateTime().toString();
                  out <<"<html>\n"
                        "<head>\n"
                         "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                      << "<title>ERP - COMmANDE LIST<title>\n "
                      << "</head>\n"
                      "<body bgcolor=#ffffff link=#5000A0>\n"
                      "<h1 style=\"text-align: center;\"><strong> ***** facture client  ***** </strong></h1>"
                         "<h1 style=\"text-align: center;\"><strong> "+TT+"</strong></h1>"
                      "<table style=\"text-align: center; font-size: 10px;\" border=1>\n "
                        "</br> </br>";
                  // headers
                  out << "<thead><tr bgcolor=#d6e5ff>";
                  for (int column = 0; column < columnCount; column++)
                      if (!ui->tab_facture->isColumnHidden(column))
                          out << QString("<th>%1</th>").arg(ui->tab_facture->model()->headerData(column, Qt::Horizontal).toString());
                  out << "</tr></thead>\n";

                  // data table
                  /*int rowlast(){
                  for (int row = 0; row < rowCount  ; row++) {
                  QSqlQuery Query;
                     row = rowCount;}}*/
                 //

               // }
                  QSqlQuery Query;

                  int cin = ui->fact->text().toInt();

//bool s = Query.prepare("SELECT* FROM Facture WHERE cin =  :cin");
Query.bindValue(":cin",cin);
                      out << "<tr>";
                      for (int column = 0; column < columnCount; column++) {
                          if (!ui->tab_facture->isColumnHidden(column)) {
                              QString data =ui->tab_facture->model()->data(ui->tab_facture->model()->index(cin-1, column)).toString().simplified();
                              out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                          }
                      }
                      out << "</tr>\n";

                  out <<  "</table>\n"
                      "</body>\n"
                      "</html>\n";

                  QTextDocument document;
                  document.setHtml(strStream);
                  document.print(&printer);
   }

void MainWindow::on_mailing_clicked()
{

    Smtp* smtp = new Smtp("hazemkechiche@gmail.com",ui->msgg->text(),"smtp.gmail.com",465);

        connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

        smtp->sendMail("hazemkechiche@gmail.com",ui->a_mail->text(),"Somme de logement",ui->msg->toPlainText(), files);


        QMessageBox::information(nullptr, QObject::tr("SENT"),
                                     QObject::tr("Email Sended Successfully.\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);

  }

void MainWindow::on_tab_facture_doubleClicked(const QModelIndex &index)
{
    QSqlQuery Query;
    QString nom=ui->tab_facture->model()->data(index).toString();
    Query.prepare("SELECT* FROM Facture WHERE cin = '"+nom+"'");
    if (Query.exec())
    {
        while   (Query.next())
        {
            ui->a_mail->setText(Query.value(8).toString());
            ui->msg->setText(Query.value(7).toString());


        }
    }
}

void MainWindow::on_pushButton_7_clicked()
{
    {
        try
        {
            const QString fileName = "g:\\temp\\kaka2.xlsx";

            ExcelExportHelper helper;

            helper.SetCellValue(1,1,"nom_logement");
            helper.SetCellValue(1,2,"nbr_etoile");
            helper.SetCellValue(1,3,"adresse");
            helper.SetCellValue(1,4,"nbr_ch");
            helper.SetCellValue(1,5,"disponibilite");
            helper.SetCellValue(1,6,"type");
            helper.SetCellValue(1,7,"email");
            int j=2;
            //int a=ui->DeliveryDetails->model()-index
            for(int i=0;i<ui->tab_log->model()->rowCount();i++)
            {
                helper.SetCellValue(j,1,ui->tab_log->model()->index(i,0).data().toString());
                helper.SetCellValue(j,2,ui->tab_log->model()->index(i,1).data().toString());
                helper.SetCellValue(j,3,ui->tab_log->model()->index(i,2).data().toString());
                helper.SetCellValue(j,4,ui->tab_log->model()->index(i,3).data().toString());
                helper.SetCellValue(j,5,ui->tab_log->model()->index(i,4).data().toString());
                helper.SetCellValue(j,6,ui->tab_log->model()->index(i,5).data().toString());
                helper.SetCellValue(j,7,ui->tab_log->model()->index(i,6).data().toString());
                j++;
;
            }
            helper.SaveAs(fileName);
        }
        catch(_exception ex)
        {}
}}

void MainWindow::on_recherche_pressed()
{
    Logement L;
    QString no =ui->cherche->text();
    bool test = L.recherche(ui->cherche->text());

       // ui->tab_log->setModel(L.recherche(ui->cherche->text()));

    if (test)
    {

        ui->tab_log->setModel(L.recherche(ui->cherche->text()));

}
    else
        QMessageBox::critical(nullptr, QObject::tr("recherche"),
                    QObject::tr("erreur de recherche.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_browse_clicked()
{

    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->msg->setText( fileListString );
}

void MainWindow::on_pushButton_12_clicked()
{
    QStackedWidget stackedWidget;
                        connect(ui->stackedWidget, SIGNAL(clicked()), this, SLOT(viewData));

                                ui->stackedWidget->setCurrentIndex(0);


}

void MainWindow::on_pushButton_14_clicked()
{
    QStackedWidget stackedWidget;
                        connect(ui->stackedWidget, SIGNAL(clicked()), this, SLOT(viewData));

                                ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_13_clicked()
{
    QStackedWidget stackedWidget;
                        connect(ui->stackedWidget, SIGNAL(clicked()), this, SLOT(viewData));

                                ui->stackedWidget->setCurrentIndex(0);

}

void MainWindow::on_comboBox1_activated(int index)
{Logement L;
    if(ui->comboBox1->currentText()=="nom logement")
        ui->tab_log->setModel(L.trieLogement());
    if(ui->comboBox1->currentText()=="nombre d'etoile")
        ui->tab_log->setModel(L.trienbetoile());
    if(ui->comboBox1->currentText()=="nombre de chambre")
        ui->tab_log->setModel(L.trienbch());
}
