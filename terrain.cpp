#include "terrain.h"
#include <QSqlQuery>
#include <iostream>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QObject>



Terrain::Terrain()
{

   capacite=0;
   nom_T="";
   type_T="";
   etat_T="";

}

Terrain::Terrain(int capacite,QString nom_T,QString type_T,QString etat_T)
{

 this->capacite=capacite,
 this->nom_T=nom_T,
 this->type_T=type_T,
 this->etat_T=etat_T;
}


int Terrain::getcapacite(){return capacite;}
QString Terrain::getnom_T(){return nom_T;}
QString Terrain::gettype_T(){return type_T;}
QString Terrain::getetat_T(){return etat_T;}
void Terrain::setcapacite(int capacite){this->capacite=capacite;}
void Terrain::setnom_T(QString nom_T){this->nom_T=nom_T;}
void Terrain::settype_T(QString type_T){this->type_T=type_T;}
void Terrain::setetat_T(QString etat_T){this->etat_T=etat_T;}

bool Terrain::ajouter()
{
    QSqlQuery query;
    QString capacite_string= QString::number(capacite);
    query.prepare("INSERT INTO TERRAIN (nom_T,type_T,etat_T,capacite) VALUES (:nom_T,:type_T,:etat_T,:capacite)");

          query.bindValue(":nom_T", nom_T);
          query.bindValue(":type_T", type_T);
          query.bindValue(":etat_T", etat_T );
          query.bindValue(":capacite", capacite_string);
          return query.exec();
}

bool Terrain::supprimer(QString nom_T)
{
    QSqlQuery query;
    query.prepare("delete from terrain where nom_T=:nom_T");

          query.bindValue(":nom_T", nom_T);

          return query.exec();
}


QSqlQueryModel* Terrain::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery("SELECT* FROM terrain");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom_T"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("type_T"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("etat_T"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("capacite"));

    return model;
}

bool Terrain::modifier(QString s)
{ QSqlQuery query;
    query.prepare("UPDATE terrain set etat_t=:etat,capacite= :capacite WHERE nom_T= :nom_T");
    query.bindValue(":nom_T",s);
    query.bindValue(":etat",etat_T);
    query.bindValue(":capacite",capacite);
    return query.exec();


}

QSqlQueryModel* Terrain::rechercher(QString search)
  {
      QSqlQueryModel * model=new QSqlQueryModel();

model->setQuery("SELECT* FROM terrain where nom_T like '%"+search+"%' or type_T like '%"+search+"%' or etat_T like '%"+search+"%' ");

      model->setHeaderData(0,Qt::Horizontal, QObject::tr("nom_T"));
      model->setHeaderData(1,Qt::Horizontal, QObject::tr("type_T"));
      model->setHeaderData(2,Qt::Horizontal, QObject::tr("etat_T"));
      model->setHeaderData(3,Qt::Horizontal, QObject::tr("capacite"));

      return model;
  }

QSqlQueryModel* Terrain::trier_n()
{
    QSqlQueryModel * model=new QSqlQueryModel();

model->setQuery("SELECT* FROM terrain ORDER BY nom_T  ");

    model->setHeaderData(0,Qt::Horizontal, QObject::tr("nom_T"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("type_T"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("etat_T"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("capacite"));


    return model;
}


QSqlQueryModel* Terrain::trier_t()
{
    QSqlQueryModel * model=new QSqlQueryModel();

model->setQuery("SELECT* FROM terrain ORDER BY type_T  ");

    model->setHeaderData(0,Qt::Horizontal, QObject::tr("nom_T"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("type_T"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("etat_T"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("capacite"));


    return model;
}


QSqlQueryModel* Terrain::trier_c()
{
    QSqlQueryModel * model=new QSqlQueryModel();

model->setQuery("SELECT* FROM terrain ORDER BY capacite ");

    model->setHeaderData(0,Qt::Horizontal, QObject::tr("nom_T"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("type_T"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("etat_T"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("capacite"));


    return model;
}







