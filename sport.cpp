#include "sport.h"

Sport::Sport()
{

}

Sport::Sport(int Id,QString Nom,QString Type,int Nbr_p,int Duree)
{
    id=Id;
    nom=Nom;
    type=Type;
    nbr_p=Nbr_p;
    duree=Duree;
}

bool Sport::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO SPORT (ID,NOM,TYPE,NBR_P,Duree) "
                        "VALUES (:id,:nom,:type,:nbr_p,:duree)");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":type", type);
    query.bindValue(":nbr_p", nbr_p);
    query.bindValue(":duree", duree);
    return    query.exec();
}

QSqlQueryModel * Sport::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from SPORT");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPE"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("NOMBRE PARTICIPANTS"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("DUREE"));

return model;
}

bool Sport::supprimer(int id)
{
    QSqlQuery query;
  //  QString res= QString::number(idd);
    query.prepare("Delete from SPORT where ID = :id ");
    query.bindValue(":id", id);
    return    query.exec();
}

bool Sport::modifier()
{
       QSqlQuery query;
        query.prepare( "UPDATE SPORT SET ID=:id,NOM=:nom,TYPE=:type,NBR_P=:nbr_p ,:DUREE=:duree WHERE ID=:id;");
        query.bindValue(":id", id);
        query.bindValue(":nom", nom);
        query.bindValue(":type", type);
        query.bindValue(":nbr_p", nbr_p);
        query.bindValue(":duree", duree);




     return query.exec();
}





