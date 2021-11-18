#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sport.h"
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QTextDocument>
#include <QDebug>
#include <QtPrintSupport/QPrinter>

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
