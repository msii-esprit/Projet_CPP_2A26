#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logement.h"
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <QValidator>
#include "facture.h"
#include <QFileDialog>
#include <QPrinter>
#include <QTextDocument>
#include <QDateTime>
#include <QPrinter>
#include <QtPrintSupport/QPrinter>
#include <QPrintDialog>
#include <QDate>
#include<QFileDialog>
#include <QTextDocument>
#include <QTextStream>
#include <QPdfWriter>
#include "envoiefactureparmail.h"
#include <QUrl>
#include "exel.h"
#include <QFileDialog>
#include <QtSql>
//#include "SmtpMime"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    Facture F ;
    ui->setupUi(this);
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



void MainWindow::on_pb_ok_clicked()
{
    QString nom_logement=ui->nom_logement->text();
    int Nbr_etoile=ui->nbr_etoile->text().toInt();
    QString adresse_l=ui->adresse->currentText();
    int Nbr_ch=ui->nbr_ch->text().toInt();
    QString disponibilite=ui->disponibilite->currentText();
    QString type_l=ui->type->currentText();
    QString in_out=ui->in_out->text();
    L.setin_out(ui->in_out->text());
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
    ui->tab_log->setModel(L.afficher());
}

void MainWindow::on_Supprimer_clicked()
{
    Logement L1 , L2;
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


void MainWindow::on_pushButton_9_clicked()
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
  int somme = F.CalculSomme(150,duree);
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



void MainWindow::on_pushButton_clicked()
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

    Smtp* smtp = new Smtp("hazemkechiche@gmail.com","09281154","smtp.gmail.com",465);

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

void MainWindow::on_pushButton_2_clicked()
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
