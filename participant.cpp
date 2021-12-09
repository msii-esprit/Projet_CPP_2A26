#include "participant.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQueryModel>
#include <QObject>
#include <QAbstractItemModel>
#include "mainwindow.h"
#include <QSqlRecord>

participant::participant(int id,QString nom,QString prenom,QString equipe,QString etat,QString type,QString nationalite,QDate date_nais,int medaille)
{this->id=id;
 this->nom=nom;
 this->prenom=prenom;
 this->etat=etat;
 this->type=type;
 this->nationalite=nationalite;
 this->date_nais=date_nais;
 this->medaille=medaille;
 this->equipe=equipe;


}
bool participant::ajouter()
{
 QSqlQuery query;
 query.prepare("insert into participant(id,nom,prenom,equipe,etat,type,nationalite,date_nais,medaille)""values(:id,:nom,:prenom,:equipe,:etat,:type,:nationalite,:date_nais,:medaille)");
 query.bindValue(":id",id);
 query.bindValue(":nom",nom);
 query.bindValue(":prenom",prenom);
 query.bindValue(":equipe",equipe);
 query.bindValue(":nationalite",nationalite);
 query.bindValue(":type",type);
 query.bindValue(":etat",etat);
query.bindValue(":medaille",medaille);
query.bindValue(":date_nais",date_nais);

if (query.lastError().isValid())
    qDebug() << query.lastError();


return query.exec();
}
QSqlQueryModel * participant::afficher()
{
QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select * from PARTICIPANT");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("EQUIPE"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("ETAT"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("TYPE"));
model->setHeaderData(6,Qt::Horizontal,QObject::tr("NATIONALITE"));
model->setHeaderData(7,Qt::Horizontal,QObject::tr("DATE_NAIS"));
model->setHeaderData(8,Qt::Horizontal,QObject::tr("MEDAILLE"));
return model;
}

bool participant::supprimer(int i)
{QSqlQuery q;

/*
QDate d;
        if(s.userType()==QMetaType::Int)
        {
            i=s.toInt();
        }
        else if(s.userType()==QMetaType::QString)
        {
            s.toString();
        }
        else if(s.userType()==QMetaType::QDate)
        {
            d=s.toDate();
       }
*/







    q.prepare("delete from participant where id= :id ");
    q.bindValue(":id",i);
    /*
    q.bindValue(":nom",s);
    q.bindValue(":prenom",s);
    q.bindValue(":equipe",s);
    q.bindValue(":nationalite",s);
    q.bindValue(":type",s);
    q.bindValue(":etat",s);
     q.bindValue(":date_nais",d);
   q.bindValue(":medaille",i);
*/

    return q.exec();


}
bool participant::search(int a)
{
    QSqlQuery  q;
    q.prepare("select id from PARTICIPANT where id== :id");
q.bindValue(":id",a);

QSqlRecord t=q.record();
qDebug() << q.record();

return q.exec();
}
bool participant::modifier(int v)
{ QSqlQuery query;
    query.prepare("UPDATE participant set id= :id,nom= :nom,prenom= :prenom,equipe= :equipe,etat= :etat,type= :type,nationalite =:nationalite,date_nais= :date_nais,medaille= :medaille WHERE id= :v");
    query.bindValue(":v",v);
    query.bindValue(":id",id);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":equipe",equipe);
    query.bindValue(":nationalite",nationalite);
    query.bindValue(":type",type);
    query.bindValue(":etat",etat);
   query.bindValue(":medaille",medaille);
   query.bindValue(":date_nais",date_nais);

   if (query.lastError().isValid())
       qDebug() << query.lastError();


   return query.exec();
}
QSqlQueryModel * participant::afficherL()
{
QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select * from LOGMENT");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("NOM_LOG"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("NBR_ETOILE"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("ADRESSE_L"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("NBR_CH"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("DISPONIBILITE"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("TYPE_L"));
model->setHeaderData(6,Qt::Horizontal,QObject::tr("IN_OUT"));

return model;
}
QSqlQueryModel * participant::afficherPL()
{
QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select * from LOGPAR");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("NOM_LOG"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("ID"));


return model;
}
bool participant::affecter(int id_log,QString nom_log)
{
 QSqlQuery query;
 query.prepare("insert into LOGPAR(ID,NOMM_LOG)""values(:id,:nom)");
 query.bindValue(":id",id_log);
 query.bindValue(":nom",nom_log);


if (query.lastError().isValid())
    qDebug() << query.lastError();


return query.exec();
}
