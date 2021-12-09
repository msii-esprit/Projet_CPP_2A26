#ifndef LOGEMENT_H
#define LOGEMENT_H
#include <QSqlQuery>

#include <QString>
#include <QSqlQueryModel>
class Logement
{
public:
    Logement();
    Logement(int,int,QString,QString,QString,QString,QString);
    int getNbr_etoile();
    void setNbr_etoile(int);
    int getNbr_ch();
    void setNbr_ch(int);
    QString getnom_logement();
    void setnom_logement(QString);
    QString getdisponibilite();
    void setdisponibilite(QString);
    QString gettype_l();
    void settype_l(QString);
    QString getin_out();
    void setin_out(QString);
    QString getadresse_l();
    void setadresse_l(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(QString );
    bool EmailValide(QString);
    bool modifier(QString);
    QSqlQueryModel* trieLogement();
    QSqlQueryModel* trienbetoile();
    QSqlQueryModel* trienbch();
     QSqlQueryModel* recherche(const QString);
private :
    QString nom_logement ;

    int Nbr_etoile;
    QString adresse_l;
    int Nbr_ch;
    QString disponibilite;
    QString type_l;
    QString in_out;


};

#endif // LOGEMENT_H
