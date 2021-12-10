#include "spectateurs.h"
#include<QString>
#include<QSqlQuery>
#include<QtDebug>
#include<QSqlQueryModel>
#include<QObject>
#include <QRegularExpression>
#include"mainwindow.h"
Spectateurs::Spectateurs()
{
cin=0;
age=0;
num=0;
nom="";

}
Spectateurs::Spectateurs(int cin,QString nom,int age,int num)
{
    this->cin=cin;

    this->nom=nom;
    this->age=age;
    this->num=num;

}
int Spectateurs::getcin(){return cin;}
QString Spectateurs::getnom(){return nom;}
int Spectateurs::getage(){return age;}
int Spectateurs::getnum(){return num;}
void Spectateurs::setcin(int cin){this->cin=cin; }
void Spectateurs::setnom(QString nom){this->nom=nom; }
void Spectateurs::setage(int age){this->age=age; }
void Spectateurs::setnum(int num){this->num=num; }

bool Spectateurs::ajouter()
{

    QString cin_string=QString::number(cin);
    QString age_string=QString::number(age);
    QString num_num=QString::number(num);

    QSqlQuery query;
    query.prepare("INSERT INTO SPECTATEUR (CIN, NOM, AGE,NUM) "
                  "VALUES (:0, :1, :2, :3)");
    query.bindValue(0, cin_string);
    query.bindValue(1, nom);
    query.bindValue(2, age_string);
    query.bindValue(3, num_num);

  return  query.exec();

}
bool Spectateurs:: supprimer(int cin)
{
    QSqlQuery query;
    query.prepare(" Delete from SPECTATEUR where CIN=:0");
    query.bindValue(0, cin);

  return  query.exec();

}

QSqlQueryModel * Spectateurs::afficher()
{

    QSqlQueryModel* model=new QSqlQueryModel();
         model->setQuery("SELECT* FROM SPECTATEUR ");
         model->setHeaderData(0, Qt::Horizontal,QObject::tr("CIN"));
         model->setHeaderData(1, Qt::Horizontal,QObject::tr("NOM"));
         model->setHeaderData(2, Qt::Horizontal,QObject::tr("AGE"));
         model->setHeaderData(3, Qt::Horizontal,QObject::tr("NUM"));

    return  model;

}

bool Spectateurs::modifier()
{

    QString cin_string=QString::number(cin);

    QString age_string=QString::number(age);
    QString num_num=QString::number(num);

       QSqlQuery query;
       query.prepare("UPDATE  SPECTATEUR SET  CIN=:0,NOM=:1,AGE=:2,NUM=:3 WHERE CIN=:0;");
       query.bindValue(":0", cin_string);
        query.bindValue(":1", nom);
        query.bindValue(":2", age_string);
        query.bindValue(":3", num_num);


        return  query.exec();
}



