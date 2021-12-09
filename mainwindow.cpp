#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include "participant.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDateEdit>
#include <QDate>
#include <QComboBox>
#include <QDebug>
#include <QDesktopWidget>
#include <QString>
#include <QList>
#include <QAbstractItemModel>
#include <QIntValidator>
#include <QValidator>
#include <QStandardItem>
#include <QColor>
#include <QStyledItemDelegate>
#include <QStyleOptionViewItem>
#include <QPainter>
#include "LinearRegressionModel.h"
#include <bits/stdc++.h>
#include "utils.h"
#include "Dataset.h"
#include "Weights.h"
#include <QListView>
#include <QAbstractItemModel>
#include "dialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

ui->setupUi(this);
this->setStyleSheet(" background-image: url(C:/AMOUNI/test.png);");
    ui->tableView->setModel(p.afficher());
  ui->tableView_3->setModel(p.afficherL());
    ui->tableView_4->setModel(p.afficherPL());


    QObject::connect(ui->button,SIGNAL(clicked()),this,SLOT(on_pushButtonajouterclicked()));
    QObject::connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(on_pushButton_modifier_clicked()));
    QObject::connect(ui->pushButton_predict,SIGNAL(clicked()),this,SLOT(on_pushButton_predict_clicked()));
    QObject::connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(on_pushButton_tirage5_clicked()));

     QMetaObject::connectSlotsByName(ui->tableWidget_5);

ui->lineEdit->setInputMask("999999");
ui->lineEdit_2->placeholderText();
ui->lineEdit_2->setInputMask("A<AAAAAAAAAAAAA");
ui->lineEdit_3->setInputMask("A<AAAAAAA AAAAAAA");
ui->comboBox_3->model()->sort(0);
ui->pushButton->setStyleSheet("font: bold;background-color: red;font-size: 36px;height: 48px;width: 120px;");
ui->button->setStyleSheet("font: bold;background-color: green;font-size: 36px;height: 48px;width: 120px;");
ui->pushButton_2->setStyleSheet("font: bold;background-color: rgb(85, 170, 255);font-size: 36px;height: 48px;width: 120px;");
QStandardItem item;
item.setBackground(QColor(Qt::green));
item.setForeground(QColor(Qt::red));
int t=ui->tableView->model()->rowCount();
ui->lcdNumber->display(t);
ui->lineEdit_ID->setInputMask("999999");
ui->lineEdit_nom->placeholderText();
ui->lineEdit_nom->setInputMask("A<AAAAAAAAAAAAA");
ui->lineEdit_prenom->setInputMask("A<AAAAAAA AAAAAAA");
ui->widget->hide();
QValidator  *v= new QIntValidator(0,100,this);
ui->lineEdit_6->setValidator(v);
ui->lineEdit_M->setValidator(v);
ui->widget_2->hide();

 ui->tableView_2->setModel(p.afficher());





}


MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::connectEquipe()
{ QString v=ui->comboBox_3->currentText();
     QString    t1="Tunisia Algerie Mali Maroc Cameroon Ghana Egypt South Africa Nigeria";
  QString  t="Germany France Italie Danemark Holland Portugal Belgium Suede Spain Russia Turkey";
  QString t2="Qatar Japan UAE India Korea China Saudia Oman Palestine Lebanon";
  QString t3="Australia New-zeland";
     if(t.contains(v)==true)
     ui->comboBox_4->setCurrentText("Europe");


           else if (t1.contains(v)==true)
            ui->comboBox_4->setCurrentText("Africa");
       else if(t2.contains(v)==true)
              ui->comboBox_4->setCurrentText("Asie");
     else if(t3.contains(v)==true)
         ui->comboBox_4->setCurrentText("Oceanie");
     else
         ui->comboBox_4->setCurrentText("Amerique");

}
void MainWindow::connectEquipeM()
{ QString v=ui->comboBox_n->currentText();
     QString    t1="Tunisia Algerie Mali Maroc Cameroon Ghana Egypt South Africa Nigeria";
  QString  t="Germany France Italie Danemark Holland Portugal Belgium Suede Spain Russia Turkey";
  QString t2="Qatar Japan UAE India Korea China Saudia Oman Palestine Lebanon";
  QString t3="Australia New-zeland";
     if(t.contains(v)==true)
     ui->comboBox_c->setCurrentText("Europe");

           else if (t1.contains(v)==true)
            ui->comboBox_c->setCurrentText("Africa");
       else if(t2.contains(v)==true)
              ui->comboBox_c->setCurrentText("Asie");
     else if(t3.contains(v)==true)
         ui->comboBox_c->setCurrentText("Oceanie");
     else
         ui->comboBox_c->setCurrentText("Amerique");

}




void MainWindow::on_pushButtonajouterclicked()
{

int id=ui->lineEdit->text().toInt();
QString nom=ui->lineEdit_2->text();
QString prenom=ui->lineEdit_3->text();
connectEquipe();
QString nationalite=ui->comboBox_4->currentText();
QString etat;
QString equipe;
QString type;

type=ui->comboBox->currentText();
etat=ui->comboBox_2->currentText();
equipe=ui->comboBox_3->currentText();


QDate date_nais;
date_nais=ui->dateEdit->date();
int medaille=ui->lineEdit_6->text().toInt();

bool c=search(id);
QString v=QString::number(id);
int v1=v.count();

if(v1!=6||c==true)
{if(v1!=6)
    {
            QMessageBox::critical(nullptr, QObject::tr("Incorrect ID"),
                                    QObject::tr("add failed.\n"
                                                "Please set minmum length of ID 6 numbers."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Incorrect ID"),
                                QObject::tr("add failed.\n"
                                            "this ID exist. Please choose another one ."), QMessageBox::Cancel);
    }
}
else {


int x;
int t=nom.count();
x=prenom.count();
if(x<3||t<3)
{ QMessageBox::critical(nullptr, QObject::tr("Incorrect prenom or nom"),
                        QObject::tr("add failed.\n"
                                    "Please set minmum length of prenom or nom 3 characters."), QMessageBox::Cancel);

}
else
{
participant p(id,nom,prenom,equipe,etat,type,nationalite,date_nais,medaille);
 bool test=p.ajouter();

 ui->lineEdit->clear();
 ui->lineEdit_2->clear();
 ui->lineEdit_3->clear();
 ui->lineEdit_6->clear();


if(test)
{ ui->tableView->setModel(p.afficher());
    int x=ui->tableView->model()->rowCount();
    ui->lcdNumber->display(x);
    qDebug()<< x;
    QMessageBox::information(nullptr, QObject::tr("ok"),
                          QObject::tr("added successful.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);

      }
else
{
    QMessageBox::critical(nullptr, QObject::tr("add failed"),
                QObject::tr("add failed.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);


}
}
}
}

QModelIndex  MainWindow::on_tableView_activated( QModelIndex index)
{

     index = ui->tableView->currentIndex();
    return(index);

}


void MainWindow::on_pushButton_clicked()
{   QModelIndex index;

    index=on_tableView_activated(index);
   QVariant value=ui->tableView->model()->data(index);
QString v=QVariant(value).toString();
int v1=v.count();

if((value.userType()!=QMetaType::QString)&&(v1>3))
{
    int x=value.toInt();
    bool test=p.supprimer(x);


    if(test)
    { ui->tableView->setModel(p.afficher());
        int t=ui->tableView->model()->rowCount();
        ui->lcdNumber->display(t);
        QMessageBox::information(nullptr, QObject::tr("ok"),
                              QObject::tr("suppression successful.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);

          }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("suppresion"),
                    QObject::tr("supression failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


    }
}
else
{
    QMessageBox::critical(nullptr, QObject::tr("suppresion"),
                QObject::tr("supression failed. Please Select ID\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);


}

}
bool MainWindow::search(int t)
{bool test=false;

       for (int var = 0; var < ui->tableView->model()->rowCount(); ++var) {
           if(ui->tableView->model()->index(var,0).data().toInt()==t){
              ;
              test=true;
           }
       }
       return test;
}




void MainWindow::on_pushButton_modifier_clicked()
{QModelIndex index;
    index=on_tableView_activated(index);

    int row=index.row();
QVariant v=index.sibling(row,1).data();
QString  v1=v.toString();
QVariant f=index.sibling(row,2).data();
QString  f1=f.toString();
QVariant s=index.sibling(row,0).data();
QString  s1=s.toString();
QVariant n=index.sibling(row,3).data();
QString  n1=n.toString();
QVariant e=index.sibling(row,4).data();
QString  e1=e.toString();
QVariant t=index.sibling(row,5).data();
QString  t1=t.toString();
QVariant m=index.sibling(row,8).data();
QString  m1=m.toString();
QVariant c=index.sibling(row,6).data();
QString  c1=c.toString();
QVariant d=index.sibling(row,7).data();
QDate d1=d.toDate();
     ui->widget->show();
    ui->lineEdit_ID->setText(s1);
    ui->lineEdit_nom->setText(v1);
    ui->lineEdit_prenom->setText(f1);
    ui->lineEdit_M->setText(m1);
    ui->comboBox_n->setCurrentText(n1);
    ui->comboBox_e->setCurrentText(e1);
    ui->comboBox_t->setCurrentText(t1);
    ui->dateEdit_2->setDate(d1);
    ui->comboBox_c->setCurrentText(c1);





}

void MainWindow::on_buttonBox_accepted()
{
    QModelIndex index;
        index=on_tableView_activated(index);

        int row=index.row();
        QVariant h=index.sibling(row,0).data();
        int h1=h.toInt();
    connectEquipeM();
    int id=ui->lineEdit_ID->text().toInt();
    QString nom=ui->lineEdit_nom->text();
    QString prenom=ui->lineEdit_prenom->text();

    QString nationalite=ui->comboBox_c->currentText();
    QString etat;
    QString equipe;
    QString type;

    type=ui->comboBox_t->currentText();
    etat=ui->comboBox_e->currentText();
    equipe=ui->comboBox_n->currentText();


    QDate date_nais;
    date_nais=ui->dateEdit_2->date();
    int medaille=ui->lineEdit_M->text().toInt();

    bool c;
    QString v=QString::number(id);
    int v1=v.count();
if(id==h1)
     c=false;
else
      c=search(id);

    if(v1!=6||c==true)
    {if(v1!=6)
        {
                QMessageBox::critical(nullptr, QObject::tr("Incorrect ID"),
                                        QObject::tr("add failed.\n"
                                                    "Please set minmum length of ID 6 numbers."), QMessageBox::Cancel);
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Incorrect ID"),
                                    QObject::tr("add failed.\n"
                                                "this ID exist. Please choose another one ."), QMessageBox::Cancel);
        }
    }
    else {


    int x;
    int t=nom.count();

    x=prenom.count();
    qDebug()<<x;
    if(x<4 || t<3)
    { QMessageBox::critical(nullptr, QObject::tr("Incorrect prenom or nom"),
                            QObject::tr("add failed.\n"
                                        "Please set minmum length of prenom or nom 3 characters."), QMessageBox::Cancel);

    }
    else
    {
    participant p(id,nom,prenom,equipe,etat,type,nationalite,date_nais,medaille);
     bool test=p.modifier(h1);




    if(test)
    { ui->tableView->setModel(p.afficher());
        int x=ui->tableView->model()->rowCount();
        ui->widget->hide();
        ui->lcdNumber->display(x);
        qDebug()<< x;
        QMessageBox::information(nullptr, QObject::tr("ok"),
                              QObject::tr("added successful.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);

          }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("add failed"),
                    QObject::tr("add failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


    }
    }
    }
}


void MainWindow::on_buttonBox_rejected()
{
  ui->widget->hide();
}




void MainWindow::on_lineEdit_R_returnPressed()
{
     for (int var = 0; var < ui->tableView->model()->rowCount(); ++var) {
         ui->tableView->showRow(var);
     }
}




void MainWindow::on_pushButton_predict_clicked()
{  float X_test[4];

  QString a=ui->lineEdit_eq1->text();
    for (int var = 0; var < ui->tableWidget_5->model()->rowCount(); ++var) {
        if(ui->tableWidget_5->model()->index(var,0).data().toString()==a){
            X_test[0]=ui->tableWidget_5->model()->index(var,1).data().toFloat();
           X_test[2]=ui->tableWidget_5->model()->index(var,2).data().toFloat();

        }
    }

    QString a1=ui->lineEdit_eq2->text();
      for (int var = 0; var < ui->tableWidget_5->model()->rowCount(); ++var) {
          if(ui->tableWidget_5->model()->index(var,0).data().toString()==a1){
              X_test[1]=ui->tableWidget_5->model()->index(var,1).data().toFloat();
               X_test[3]=ui->tableWidget_5->model()->index(var,2).data().toFloat();


          }
      }
    const char* filename = "C:\\PorjetCPP\\particpant\\testdata.csv";
     std::cout << "Reading CSV \n";
     Dataset data = read_csv(filename);

     // Regression Variables
     int max_iteration = 1000;
     float learning_rate = 0.1;

     // Training
     std::cout << "Making LinearRegressionModel \n";
     LinearRegressionModel linear_reg = LinearRegressionModel(data);
     std::cout << "Training \n";
     linear_reg.train(max_iteration, learning_rate);

     std::cout << "Testing \n";


     // Testing

   //  X_test[0] = 2.4;
   //  X_test[1] = 1.8;
    // X_test[2] = 1.5;
    // X_test[3] = 2.5
     float y_test = linear_reg.predict(X_test);
     linear_reg.print_weights();
     std::cout << "Testing for X0 = " << X_test[0] << ", X1 = " << X_test[1] << "\n";
     std::cout << "y = " << y_test << "\n";
     if (y_test>0.3)
    ui->label_RS->setText(ui->lineEdit_eq1->text());
     else if(y_test<-0.3)
          ui->label_RS->setText(ui->lineEdit_eq2->text());
     else
         ui->label_RS->setText("NULL");




}


void MainWindow::on_tableWidget_5_activated( QModelIndex index)
{



    y++;
    int row=index.row();
    QVariant t=index.sibling(row,0).data();
    QString t1=t.toString();
    if(y % 2==0)

     ui->lineEdit_eq2->setText(t1);
  else
    ui->lineEdit_eq1->setText(t1);



}



void MainWindow::on_comboBox_class1_1_currentIndexChanged(int index)
{int i;
    QListView* view =qobject_cast<QListView *>(ui->comboBox_class1_2->view());
    QListView* view1 =qobject_cast<QListView *>(ui->comboBox_class1_3->view());
    QListView* view2 =qobject_cast<QListView *>(ui->comboBox_class1_4->view());


    for (i=0;i<ui->comboBox_class1_1->model()->rowCount();i++)
     { if((ui->comboBox_class1_1->itemText(i)==ui->comboBox_class1_2->currentText())||(ui->comboBox_class1_1->itemText(i)==ui->comboBox_class1_3->currentText())||(ui->comboBox_class1_1->itemText(i)==ui->comboBox_class1_4->currentText()))
        {

        }
        else
        { view->setRowHidden(i,false);
            view1->setRowHidden(i,false);
            view2->setRowHidden(i,false);
        }
    }
view->setRowHidden(index,true);
view1->setRowHidden(index,true);
view2->setRowHidden(index,true);

}

void MainWindow::on_comboBox_class1_2_currentIndexChanged(int index)
{int i;
    QListView* view =qobject_cast<QListView *>(ui->comboBox_class1_1->view());
    QListView* view1 =qobject_cast<QListView *>(ui->comboBox_class1_3->view());
    QListView* view2 =qobject_cast<QListView *>(ui->comboBox_class1_4->view());
for (i=0;i<ui->comboBox_class1_1->model()->rowCount();i++)
 { if((ui->comboBox_class1_2->itemText(i)==ui->comboBox_class1_1->currentText())||(ui->comboBox_class1_2->itemText(i)==ui->comboBox_class1_3->currentText())||(ui->comboBox_class1_2->itemText(i)==ui->comboBox_class1_4->currentText()))
    {

    }
    else
    { view->setRowHidden(i,false);
        view1->setRowHidden(i,false);
        view2->setRowHidden(i,false);
    }
}
view->setRowHidden(index,true);
view1->setRowHidden(index,true);
view2->setRowHidden(index,true);
}


void MainWindow::on_comboBox_class1_3_currentIndexChanged(int index)
{
    int i;
        QListView* view =qobject_cast<QListView *>(ui->comboBox_class1_2->view());
        QListView* view1 =qobject_cast<QListView *>(ui->comboBox_class1_1->view());
        QListView* view2 =qobject_cast<QListView *>(ui->comboBox_class1_4->view());
        for (i=0;i<ui->comboBox_class1_1->model()->rowCount();i++)
         { if((ui->comboBox_class1_3->itemText(i)==ui->comboBox_class1_2->currentText())||(ui->comboBox_class1_3->itemText(i)==ui->comboBox_class1_1->currentText())||(ui->comboBox_class1_3->itemText(i)==ui->comboBox_class1_4->currentText()))
            {

            }
            else
            { view->setRowHidden(i,false);
                view1->setRowHidden(i,false);
                view2->setRowHidden(i,false);
            }
        }
    view->setRowHidden(index,true);
    view1->setRowHidden(index,true);
    view2->setRowHidden(index,true);

}


void MainWindow::on_comboBox_class1_4_currentIndexChanged(int index)
{
    int i;
        QListView* view =qobject_cast<QListView *>(ui->comboBox_class1_2->view());
        QListView* view1 =qobject_cast<QListView *>(ui->comboBox_class1_3->view());
        QListView* view2 =qobject_cast<QListView *>(ui->comboBox_class1_1->view());
        for (i=0;i<ui->comboBox_class1_1->model()->rowCount();i++)
         { if((ui->comboBox_class1_4->itemText(i)==ui->comboBox_class1_1->currentText())||(ui->comboBox_class1_4->itemText(i)==ui->comboBox_class1_3->currentText())||(ui->comboBox_class1_4->itemText(i)==ui->comboBox_class1_2->currentText()))
            {

            }
            else
            { view->setRowHidden(i,false);
                view1->setRowHidden(i,false);
                view2->setRowHidden(i,false);
            }
        }
    view->setRowHidden(index,true);
    view1->setRowHidden(index,true);
    view2->setRowHidden(index,true);

}

void MainWindow::on_comboBox_class2_1_currentIndexChanged(int index)
{
    int i;
        QListView* view =qobject_cast<QListView *>(ui->comboBox_class2_2->view());
        QListView* view1 =qobject_cast<QListView *>(ui->comboBox_class2_3->view());
        QListView* view2 =qobject_cast<QListView *>(ui->comboBox_class2_4->view());
        for (i=0;i<ui->comboBox_class2_1->model()->rowCount();i++)
         { if((ui->comboBox_class2_1->itemText(i)==ui->comboBox_class2_2->currentText())||(ui->comboBox_class2_1->itemText(i)==ui->comboBox_class2_3->currentText())||(ui->comboBox_class2_1->itemText(i)==ui->comboBox_class2_4->currentText()))
            {

            }
            else
            { view->setRowHidden(i,false);
                view1->setRowHidden(i,false);
                view2->setRowHidden(i,false);
            }
        }
    view->setRowHidden(index,true);
    view1->setRowHidden(index,true);
    view2->setRowHidden(index,true);
}

void MainWindow::on_comboBox_class2_2_currentIndexChanged(int index)
{
    int i;
        QListView* view =qobject_cast<QListView *>(ui->comboBox_class2_1->view());
        QListView* view1 =qobject_cast<QListView *>(ui->comboBox_class2_3->view());
        QListView* view2 =qobject_cast<QListView *>(ui->comboBox_class2_4->view());
        for (i=0;i<ui->comboBox_class2_1->model()->rowCount();i++)
         { if((ui->comboBox_class2_2->itemText(i)==ui->comboBox_class2_1->currentText())||(ui->comboBox_class2_2->itemText(i)==ui->comboBox_class2_3->currentText())||(ui->comboBox_class2_2->itemText(i)==ui->comboBox_class2_4->currentText()))
            {

            }
            else
            { view->setRowHidden(i,false);
                view1->setRowHidden(i,false);
                view2->setRowHidden(i,false);
            }
        }
    view->setRowHidden(index,true);
    view1->setRowHidden(index,true);
    view2->setRowHidden(index,true);
}

void MainWindow::on_comboBox_class2_3_currentIndexChanged(int index)
{
    int i;
        QListView* view =qobject_cast<QListView *>(ui->comboBox_class2_2->view());
        QListView* view1 =qobject_cast<QListView *>(ui->comboBox_class2_1->view());
        QListView* view2 =qobject_cast<QListView *>(ui->comboBox_class2_4->view());
        for (i=0;i<ui->comboBox_class2_1->model()->rowCount();i++)
         { if((ui->comboBox_class2_3->itemText(i)==ui->comboBox_class2_2->currentText())||(ui->comboBox_class2_3->itemText(i)==ui->comboBox_class2_1->currentText())||(ui->comboBox_class2_3->itemText(i)==ui->comboBox_class2_4->currentText()))
            {

            }
            else
            { view->setRowHidden(i,false);
                view1->setRowHidden(i,false);
                view2->setRowHidden(i,false);
            }
        }
    view->setRowHidden(index,true);
    view1->setRowHidden(index,true);
    view2->setRowHidden(index,true);
}

void MainWindow::on_comboBox_class2_4_currentIndexChanged(int index)
{
    int i;
        QListView* view =qobject_cast<QListView *>(ui->comboBox_class2_2->view());
        QListView* view1 =qobject_cast<QListView *>(ui->comboBox_class2_3->view());
        QListView* view2 =qobject_cast<QListView *>(ui->comboBox_class2_1->view());
        for (i=0;i<ui->comboBox_class2_1->model()->rowCount();i++)
         { if((ui->comboBox_class2_4->itemText(i)==ui->comboBox_class2_2->currentText())||(ui->comboBox_class2_4->itemText(i)==ui->comboBox_class2_3->currentText())||(ui->comboBox_class2_4->itemText(i)==ui->comboBox_class2_1->currentText()))
            {

            }
            else
            { view->setRowHidden(i,false);
                view1->setRowHidden(i,false);
                view2->setRowHidden(i,false);
            }
        }
    view->setRowHidden(index,true);
    view1->setRowHidden(index,true);
    view2->setRowHidden(index,true);
}

void MainWindow::on_comboBox_class3_1_currentIndexChanged(int index)
{int i;
    QListView* view =qobject_cast<QListView *>(ui->comboBox_class3_2->view());
    QListView* view1 =qobject_cast<QListView *>(ui->comboBox_class3_3->view());
    QListView* view2 =qobject_cast<QListView *>(ui->comboBox_class3_4->view());
    for (i=0;i<ui->comboBox_class3_1->model()->rowCount();i++)
     { if((ui->comboBox_class3_1->itemText(i)==ui->comboBox_class3_2->currentText())||(ui->comboBox_class3_1->itemText(i)==ui->comboBox_class3_3->currentText())||(ui->comboBox_class3_1->itemText(i)==ui->comboBox_class3_4->currentText()))
        {

        }
        else
        { view->setRowHidden(i,false);
            view1->setRowHidden(i,false);
            view2->setRowHidden(i,false);
        }
    }
view->setRowHidden(index,true);
view1->setRowHidden(index,true);
view2->setRowHidden(index,true);

}

void MainWindow::on_comboBox_class3_2_currentIndexChanged(int index)
{int i;
    QListView* view =qobject_cast<QListView *>(ui->comboBox_class3_1->view());
    QListView* view1 =qobject_cast<QListView *>(ui->comboBox_class3_3->view());
    QListView* view2 =qobject_cast<QListView *>(ui->comboBox_class3_4->view());
    for (i=0;i<ui->comboBox_class3_1->model()->rowCount();i++)
     { if((ui->comboBox_class3_2->itemText(i)==ui->comboBox_class3_1->currentText())||(ui->comboBox_class3_2->itemText(i)==ui->comboBox_class3_3->currentText())||(ui->comboBox_class3_2->itemText(i)==ui->comboBox_class3_4->currentText()))
        {

        }
        else
        { view->setRowHidden(i,false);
            view1->setRowHidden(i,false);
            view2->setRowHidden(i,false);
        }
    }
view->setRowHidden(index,true);
view1->setRowHidden(index,true);
view2->setRowHidden(index,true);

}

void MainWindow::on_comboBox_class3_3_currentIndexChanged(int index)
{
    int i;
        QListView* view =qobject_cast<QListView *>(ui->comboBox_class3_2->view());
        QListView* view1 =qobject_cast<QListView *>(ui->comboBox_class3_1->view());
        QListView* view2 =qobject_cast<QListView *>(ui->comboBox_class3_4->view());
        for (i=0;i<ui->comboBox_class3_1->model()->rowCount();i++)
         { if((ui->comboBox_class3_3->itemText(i)==ui->comboBox_class3_2->currentText())||(ui->comboBox_class3_3->itemText(i)==ui->comboBox_class3_1->currentText())||(ui->comboBox_class3_3->itemText(i)==ui->comboBox_class3_4->currentText()))
            {

            }
            else
            { view->setRowHidden(i,false);
                view1->setRowHidden(i,false);
                view2->setRowHidden(i,false);
            }
        }
    view->setRowHidden(index,true);
    view1->setRowHidden(index,true);
    view2->setRowHidden(index,true);
}

void MainWindow::on_comboBox_class3_4_currentIndexChanged(int index)
{
    int i;
        QListView* view =qobject_cast<QListView *>(ui->comboBox_class3_2->view());
        QListView* view1 =qobject_cast<QListView *>(ui->comboBox_class3_3->view());
        QListView* view2 =qobject_cast<QListView *>(ui->comboBox_class3_1->view());
        for (i=0;i<ui->comboBox_class3_1->model()->rowCount();i++)
         { if((ui->comboBox_class3_4->itemText(i)==ui->comboBox_class3_2->currentText())||(ui->comboBox_class3_4->itemText(i)==ui->comboBox_class3_3->currentText())||(ui->comboBox_class3_4->itemText(i)==ui->comboBox_class3_1->currentText()))
            {

            }
            else
            { view->setRowHidden(i,false);
                view1->setRowHidden(i,false);
                view2->setRowHidden(i,false);
            }
        }
    view->setRowHidden(index,true);
    view1->setRowHidden(index,true);
    view2->setRowHidden(index,true);
}

void MainWindow::on_comboBox_class4_1_currentIndexChanged(int index)
{
    int i;
        QListView* view =qobject_cast<QListView *>(ui->comboBox_class4_2->view());
        QListView* view1 =qobject_cast<QListView *>(ui->comboBox_class4_3->view());
        QListView* view2 =qobject_cast<QListView *>(ui->comboBox_class4_4->view());
        for (i=0;i<ui->comboBox_class4_1->model()->rowCount();i++)
         { if((ui->comboBox_class4_1->itemText(i)==ui->comboBox_class4_2->currentText())||(ui->comboBox_class4_1->itemText(i)==ui->comboBox_class4_3->currentText())||(ui->comboBox_class4_1->itemText(i)==ui->comboBox_class4_4->currentText()))
            {

            }
            else
            { view->setRowHidden(i,false);
                view1->setRowHidden(i,false);
                view2->setRowHidden(i,false);
            }
        }
    view->setRowHidden(index,true);
    view1->setRowHidden(index,true);
    view2->setRowHidden(index,true);
}

void MainWindow::on_comboBox_class4_2_currentIndexChanged(int index)
{
    int i;
        QListView* view =qobject_cast<QListView *>(ui->comboBox_class4_1->view());
        QListView* view1 =qobject_cast<QListView *>(ui->comboBox_class4_3->view());
        QListView* view2 =qobject_cast<QListView *>(ui->comboBox_class4_4->view());
        for (i=0;i<ui->comboBox_class4_1->model()->rowCount();i++)
         { if((ui->comboBox_class4_2->itemText(i)==ui->comboBox_class4_1->currentText())||(ui->comboBox_class4_2->itemText(i)==ui->comboBox_class4_3->currentText())||(ui->comboBox_class4_2->itemText(i)==ui->comboBox_class4_4->currentText()))
            {

            }
            else
            { view->setRowHidden(i,false);
                view1->setRowHidden(i,false);
                view2->setRowHidden(i,false);
            }
        }
    view->setRowHidden(index,true);
    view1->setRowHidden(index,true);
    view2->setRowHidden(index,true);
}

void MainWindow::on_comboBox_class4_3_currentIndexChanged(int index)
{
    int i;
        QListView* view =qobject_cast<QListView *>(ui->comboBox_class4_2->view());
        QListView* view1 =qobject_cast<QListView *>(ui->comboBox_class4_1->view());
        QListView* view2 =qobject_cast<QListView *>(ui->comboBox_class4_4->view());
        for (i=0;i<ui->comboBox_class4_1->model()->rowCount();i++)
         { if((ui->comboBox_class4_3->itemText(i)==ui->comboBox_class4_2->currentText())||(ui->comboBox_class4_3->itemText(i)==ui->comboBox_class4_1->currentText())||(ui->comboBox_class4_3->itemText(i)==ui->comboBox_class4_4->currentText()))
            {

            }
            else
            { view->setRowHidden(i,false);
                view1->setRowHidden(i,false);
                view2->setRowHidden(i,false);
            }
        }
    view->setRowHidden(index,true);
    view1->setRowHidden(index,true);
    view2->setRowHidden(index,true);
}

void MainWindow::on_comboBox_class4_4_currentIndexChanged(int index)
{ int i;
    QListView* view =qobject_cast<QListView *>(ui->comboBox_class4_2->view());
    QListView* view1 =qobject_cast<QListView *>(ui->comboBox_class4_3->view());
    QListView* view2 =qobject_cast<QListView *>(ui->comboBox_class4_1->view());
    for (i=0;i<ui->comboBox_class4_1->model()->rowCount();i++)
     { if((ui->comboBox_class4_4->itemText(i)==ui->comboBox_class4_2->currentText())||(ui->comboBox_class4_4->itemText(i)==ui->comboBox_class4_3->currentText())||(ui->comboBox_class4_4->itemText(i)==ui->comboBox_class4_1->currentText()))
        {

        }
        else
        { view->setRowHidden(i,false);
            view1->setRowHidden(i,false);
            view2->setRowHidden(i,false);
        }
    }
view->setRowHidden(index,true);
view1->setRowHidden(index,true);
view2->setRowHidden(index,true);

}


void MainWindow::on_pushButton_tirage5_clicked()
{ui->widget_2->show();
QVector <QString> tabC1;

QVector <QString> tabC2;
QVector <QString> tabC3;
QVector <QString> tabC4;

   tabC1.push_back(ui->comboBox_class1_4->currentText());
 tabC1.push_back(ui->comboBox_class1_2->currentText());
  tabC1.push_back(ui->comboBox_class1_1->currentText());
 tabC1.push_back(ui->comboBox_class1_3->currentText());

   tabC2.push_back(ui->comboBox_class2_4->currentText());
  tabC2.push_back(ui->comboBox_class2_2->currentText());
    tabC2.push_back(ui->comboBox_class2_1->currentText());
   tabC2.push_back(ui->comboBox_class2_3->currentText());

   tabC3.push_back(ui->comboBox_class3_4->currentText());
    tabC3.push_back(ui->comboBox_class3_2->currentText());
    tabC3.push_back(ui->comboBox_class3_1->currentText());
    tabC3.push_back(ui->comboBox_class3_3->currentText());

   tabC4.push_back(ui->comboBox_class4_4->currentText());
   tabC4.push_back(ui->comboBox_class4_2->currentText());
   tabC4.push_back(ui->comboBox_class4_1->currentText());
   tabC4.push_back(ui->comboBox_class4_3->currentText());
   int b=4;
   int c=rand() %  b;
   QTableWidgetItem *a3 = new QTableWidgetItem(tr("%1").arg(
         (3)*(1)));
   QTableWidgetItem *a5 = new QTableWidgetItem(tr("%1").arg(
         (3)*(0)));
   QTableWidgetItem *a7 = new QTableWidgetItem(tr("%1").arg(
         (3)*(0)));
   QTableWidgetItem *a1 = new QTableWidgetItem(tr("%1").arg(
         (3)*(0)));
   QTableWidgetItem *v1 = new QTableWidgetItem(tr("%1").arg(
         (2)*(0)));
   QTableWidgetItem *v3 = new QTableWidgetItem(tr("%1").arg(
         (2)*(0)));
   QTableWidgetItem *v5 = new QTableWidgetItem(tr("%1").arg(
         (2)*(0)));
     QTableWidgetItem *v7 = new QTableWidgetItem(tr("%1").arg(
                 (2)*(0)));
     QTableWidgetItem *n1 = new QTableWidgetItem(tr("%1").arg(
           (1)*(0)));
     QTableWidgetItem *n3 = new QTableWidgetItem(tr("%1").arg(
           (1)*(0)));
     QTableWidgetItem *n5 = new QTableWidgetItem(tr("%1").arg(
           (1)*(0)));
       QTableWidgetItem *n7 = new QTableWidgetItem(tr("%1").arg(
                   (1)*(0)));
       QTableWidgetItem *m1 = new QTableWidgetItem(tr("%1").arg(
             (1)*(0)));
       QTableWidgetItem *m3 = new QTableWidgetItem(tr("%1").arg(
             (1)*(0)));
       QTableWidgetItem *m5 = new QTableWidgetItem(tr("%1").arg(
             (1)*(0)));
         QTableWidgetItem *m7 = new QTableWidgetItem(tr("%1").arg(
                     (1)*(0)));



 QString v=tabC3.takeAt(c);
 QString a=tabC4.takeAt(c);
 QString n=tabC2.takeAt(c);
 QString m=tabC1.takeAt(c);

a1->setText(a);
v1->setText(v);
n1->setText(n);
m1->setText(m);
   ui->tableWidget->setItem(3,0,a1);
   ui->tableWidget->setItem(2,0,v1);
   ui->tableWidget->setItem(0,0,m1);
   ui->tableWidget->setItem(1,0,n1);
   b--;
   int c1=rand() %  b;


 QString a2=tabC4.takeAt(c1);
v=tabC3.takeAt(c1);
n=tabC2.takeAt(c1);
m=tabC1.takeAt(c1);

   a3->setText(a2);
   v3->setText(v);
   n3->setText(n);
   m3->setText(m);
   ui->tableWidget_2->setItem(3,0,a3);
   ui->tableWidget_2->setItem(2,0,v3);
   ui->tableWidget_2->setItem(0,0,m3);
   ui->tableWidget_2->setItem(1,0,n3);
   b--;
   int c2=rand() %  b;




 QString a4=tabC4.takeAt(c2);
 v=tabC3.takeAt(c2);
 n=tabC2.takeAt(c2);
 m=tabC1.takeAt(c2);
 a5->setText(a4);
 v5->setText(v);
 n5->setText(n);
 m5->setText(m);
   ui->tableWidget_3->setItem(0,0,m5);
   ui->tableWidget_3->setItem(1,0,n5);
   ui->tableWidget_3->setItem(2,0,v5);
   ui->tableWidget_3->setItem(3,0,a5);
   b=0;
   QString a6=tabC4.takeAt(b);
   v=tabC3.takeAt(b);
   n=tabC2.takeAt(b);
   m=tabC1.takeAt(b);
   v7->setText(v);
   a7->setText(a6);
   n7->setText(n);
   m7->setText(m);
   ui->tableWidget_4->setItem(3,0,a7);
   ui->tableWidget_4->setItem(2,0,v7);
   ui->tableWidget_4->setItem(1,0,n7);
   ui->tableWidget_4->setItem(0,0,m7);





}

void MainWindow::on_toolButton_clicked()
{
    ui->widget_2->hide();
}

void MainWindow::on_lineEdit_R_cursorPositionChanged(int arg1, int arg2)
{    QString i=ui->lineEdit_R->text();
    QVariant t=ui->lineEdit_R->text();
      if(t.canConvert<int>()==true)
      {
 for (int var = 0; var < ui->tableView->model()->rowCount(); ++var) {
     if(((ui->tableView->model()->index(var,0).data().toString().contains(i))==true)||((ui->tableView->model()->index(var,1).data().toString().contains(i))==true)||(ui->tableView->model()->index(var,3).data().toString().contains(i))==true){

        ui->tableView->showRow(var);

     }
     else
         ui->tableView->hideRow(var);
 }
}


}

/*void MainWindow::on_Statistique_clicked()
{





                         a=6;

                          q=7;

                          q1=8;


                        q2=9;







                         MainWindow::makePlot();


                /*          QLineSeries *series = new QLineSeries();
                          *series << QPointF(0, 6) << QPointF(9, 4) << QPointF(15, 20) << QPointF(25, 12) << QPointF(29, 26);
                          QChart *chart = new QChart();
                          chart->legend()->hide();
                          chart->addSeries(series);
                 if (age!=0)
                 {QPieSlice *slice = series->slices().at(0);
                  slice->setLabelVisible();
                  slice->setPen(QPen());}
                 if ( agee!=0)
                 {
                          // Add label, explode and define brush for 2nd slice
                          QPieSlice *slice1 = series->slices().at(1);
                          //slice1->setExploded();
                          slice1->setLabelVisible();
                 }
                 if(ageee!=0)
                 {
                          // Add labels to rest of slices
                          QPieSlice *slice2 = series->slices().at(2);
                          //slice1->setExploded();
                          slice2->setLabelVisible();
                 }
                         // Create the chart widget
                         QChart *chart = new QChart();
                         // Add data to chart with title and hide legend
                         chart->addSeries(series);
                         chart->setTitle("Pourcentage Par Age :Nombre Des Aimaux "+ QString::number(total));
                         chart->legend()->hide();
                         // Used to display the chart
                         QChartView *chartView = new QChartView(chart);
                         chartView->setRenderHint(QPainter::Antialiasing);
                         chartView->resize(1000,500);
                         chartView->show();
*/





void MainWindow::on_tableView_2_clicked(const QModelIndex &index)
{ QVariant s=index.data();
    int s1=s.toInt();
    if(index.column()==0)

     ui->log->setText( QString::number(s1));
      else
        qDebug()<<index.column();


}

void MainWindow::on_tableView_3_activated(const QModelIndex &index)
{QVariant s=index.data();
    QString s1=s.toString();
    if(index.column()==0)

     ui->log_2->setText( s1);
      else
        qDebug()<<index.column();


}

void MainWindow::on_button_2_clicked()
{
    int i=ui->log->text().toInt();
    QString s=ui->log_2->text();
    bool test;
    test=p.affecter(i,s) ;
    p.afficherPL();
}
