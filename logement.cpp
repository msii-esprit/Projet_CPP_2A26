#include "logement.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QTableView>
#include <QMessageBox>
#include <ui_mainwindow.h>
using namespace std;
Logement::Logement()
{
     Nbr_etoile=0 ;
     Nbr_ch=0;




}
Logement::Logement(int Nbr_etoile,int Nbr_ch,QString nom_logement,QString disponibilite ,QString type_l,QString adresse_l,QString in_out)
{this->Nbr_etoile=Nbr_etoile; this->Nbr_ch=Nbr_ch,this->nom_logement=nom_logement;this->disponibilite=disponibilite;this->type_l=type_l;this->in_out=in_out;this->adresse_l=adresse_l;}
int Logement::getNbr_etoile(){return Nbr_etoile;}
void Logement::setNbr_etoile(int Nbr_etoile){this->Nbr_etoile=Nbr_etoile;}
int Logement::getNbr_ch(){return Nbr_ch;}
void Logement::setNbr_ch(int Nbr_ch){this->Nbr_ch=Nbr_ch;}
QString Logement::getnom_logement(){return nom_logement;}
void Logement::setnom_logement(QString nom_logement){this->nom_logement=nom_logement;}
QString Logement::getdisponibilite(){return disponibilite;}
void Logement::setdisponibilite(QString disponibilite){this->disponibilite=disponibilite;}
QString Logement::gettype_l(){return type_l;}
void Logement::settype_l(QString type_l){this->type_l=type_l;}
QString Logement::getin_out(){return in_out;}
void Logement::setin_out(QString in_out){this->in_out=in_out;}
QString Logement::getadresse_l(){return adresse_l;}
void Logement::setadresse_l(QString adresse_l){this->adresse_l=adresse_l;}
bool Logement::ajouter()
{

    QSqlQuery query;
    QString nbr_etoileString = QString::number(Nbr_etoile);
    QString nbr_chString= QString::number(Nbr_ch);
          query.prepare("INSERT INTO logment (nom_log,nbr_etoile ,adresse_l,nbr_ch,disponibilite,type_l,email ) "
                        "VALUES ( :1, :2,:3,:4,:5,:6,:7)");
          query.bindValue(":1", nom_logement );
          query.bindValue(":2", nbr_etoileString);
          query.bindValue(":3", adresse_l);
          query.bindValue(":4", nbr_chString );
          query.bindValue(":5", disponibilite );
          query.bindValue(":6", type_l );
          query.bindValue(":7", in_out );
          return query.exec();


}
QSqlQueryModel* Logement::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel;
          model->setQuery("SELECT*  FROM LOGMENT");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom logement"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("nombre detoile  "));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("adresse"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("nombre de chambre"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("disponibilite"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("type"));
          model->setHeaderData(6, Qt::Horizontal, QObject::tr("Email"));
         // model->setHeaderData(, Qt::Horizontal, QObject::tr("Salary"));
         // QTableView *view = new QTableView;
             //  view->setModel(model);
             //  view->show();
          return model ;
}
bool Logement::supprimer(QString)
{
    QSqlQuery Query ;
    Query.prepare(" Delete from logment where nom_log = :nom_log ") ;

    Query.bindValue(0, nom_logement );
    return Query.exec();
}
bool Logement::EmailValide(QString email)
{ bool mail = true;
qDebug() << email;
    QRegularExpression regex("^[0-9a-zA-Z]+([0-9a-zA-Z]*[-._+])*[0-9a-zA-Z]+@[0-9a-zA-Z]+([-.][0-9a-zA-Z]+)*([0-9a-zA-Z]*[.])[a-zA-Z]{2,6}$");

    if(!regex.match(email).hasMatch())
    {
        mail = false;
    }




    return mail;

}
bool Logement::modifier(QString )
{
    QSqlQuery query;
    QString nbr_etoileString = QString::number(Nbr_etoile);
    QString nbr_chString= QString::number(Nbr_ch);
          query.prepare("UPDATE LOGMENT SET  nom_log= :nom_logement ,nbr_etoile=:nbr_etoileString ,adresse_l = :adresse_l,nbr_ch= :nbr_chString ,disponibilite= :disponibilite ,type_l= :type_l ,email= :in_out  where nom_log = :nom_logement  ");

          query.bindValue(":nom_logement", nom_logement );
          query.bindValue(":nbr_etoileString", nbr_etoileString);
          query.bindValue(":adresse_l", adresse_l);
          query.bindValue(":nbr_chString", nbr_chString );
          query.bindValue(":disponibilite", disponibilite );
          query.bindValue(":type_l", type_l );
          query.bindValue(":in_out", in_out );
          return query.exec();


}
QSqlQueryModel* Logement::trieLogement()
{
    QSqlQueryModel* model = new QSqlQueryModel;
          model->setQuery("SELECT*  FROM LOGMENT ORDER BY nom_log DESC ");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom logement"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("nombre detoile  "));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("adresse"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("nombre de chambre"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("disponibilite"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("type"));
          model->setHeaderData(6, Qt::Horizontal, QObject::tr("Email"));
          return model;
}
QSqlQueryModel* Logement::trienbetoile()
{
    QSqlQueryModel* model = new QSqlQueryModel;
          model->setQuery("SELECT*  FROM LOGMENT ORDER BY nbr_etoile DESC ");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom logement"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("nombre detoile  "));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("adresse"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("nombre de chambre"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("disponibilite"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("type"));
          model->setHeaderData(6, Qt::Horizontal, QObject::tr("Email"));
          return model;
}
QSqlQueryModel* Logement::trienbch()
{
    QSqlQueryModel* model = new QSqlQueryModel;
          model->setQuery("SELECT*  FROM LOGMENT ORDER BY nbr_ch DESC ");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom logement"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("nombre detoile  "));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("adresse"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("nombre de chambre"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("disponibilite"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("type"));
          model->setHeaderData(6, Qt::Horizontal, QObject::tr("Email"));
          return model;
}
QSqlQueryModel* Logement::recherche(const QString aux)
{


    QSqlQueryModel* model = new QSqlQueryModel;

    QSqlQuery query;


    query.prepare("SELECT*  FROM logment  where  nom_log like '%"+aux+"%' ");
   model->setQuery("SELECT*  FROM logment  where  nom_log like '%"+aux+"%' ");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom logement"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("nombre detoile  "));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("adresse"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("nombre de chambre"));
   model->setHeaderData(4, Qt::Horizontal, QObject::tr("disponibilite"));
   model->setHeaderData(5, Qt::Horizontal, QObject::tr("type"));
   model->setHeaderData(6, Qt::Horizontal, QObject::tr("Email"));



      return model ;

      }







