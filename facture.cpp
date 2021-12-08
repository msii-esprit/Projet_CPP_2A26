#include "facture.h"
#include <QSqlQuery>
#include <QSqlQueryModel>






Facture::Facture()
{
nbr = 0;
cin=0;
duree=0;
somme =0;
}

Facture::Facture(int cin,QString nom,QString prenom,int nbr,int duree,int somme,QString email)
{
this->cin=cin;
    this->nom=nom;
    this->prenom=prenom;
    this->nbr=nbr;
    this->duree=duree;
    this->somme=somme;
    this->email=email;
}
int Facture::getcin(){return cin;}
void Facture::setcin(int cin){this->cin=cin;}
QString Facture::getnom(){return nom;}
void Facture::setnom(QString nom){this->nom=nom;}
QString Facture::getprenom(){return prenom;}
void Facture::setprenom(QString prenom){this->prenom=prenom;}
int Facture::getnbr(){return nbr;}
void Facture::setnbr(int nbr){this->nbr=nbr;}
int Facture::getduree(){return duree;}
void Facture::setduree(int duree){this->duree=duree;}
float Facture::getsomme(){return somme;}
void Facture::setsomme(int somme){this->somme=somme;}
QString Facture::getemail(){return email;}
void Facture::setemail(QString email) {this->email=email;}
bool Facture::ajouter()
{

    QSqlQuery query;
    QString cinS = QString::number(cin);
    QString nbrS= QString::number(nbr);
    QString dureeS= QString::number(duree);
    QString sommeS = QString::number(somme);
          query.prepare("INSERT INTO facture (cin,nom ,prenom,num_ch,duree,somme,mail ) "
                        "VALUES ( :1, :2,:3,:4,:5,:6,:7)");
          query.bindValue(":1", cinS );
          query.bindValue(":2", nom);
          query.bindValue(":3", prenom);
          query.bindValue(":4", nbrS );
          query.bindValue(":5", dureeS );
          query.bindValue(":6",somme);
          query.bindValue(":7",email);


          return query.exec();}
QSqlQueryModel* Facture::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel;
          model->setQuery("SELECT cin , nom,prenom,num_ch,duree,somme,mail  FROM Facture");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM  "));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("NUM CHAMBRE"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("DUREE"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("SOMME(DT)"));
          model->setHeaderData(6, Qt::Horizontal, QObject::tr("Email"));

         // QTableView *view = new QTableView;
             //  view->setModel(model);
             //  view->show();
          return model ;
}
float Facture::CalculSomme( int prix,int duree)
{

   somme = (duree * prix) ;
   return somme;
}
