#ifndef PARTICIPANT_H
#define PARTICIPANT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>

class participant
{int id,medaille;
  QString nom,prenom,equipe,etat,type,nationalite;
QDate date_nais;

public:
participant(){};
    participant(int,QString,QString,QString,QString,QString,QString,QDate,int);
    QString getnom(){return nom;}
    QString getprenom(){return prenom;}
    QString getequipe(){return equipe;}
    QString getetat(){return etat;}
    QString getnationalite(){return nationalite;}
    QString getype(){return type;}
    int getid(){return id;}
    int getmedaille(){return medaille;}
    QDate getdate(){return date_nais;}

    void setnom(QString n){nom=n;}
    void setprenom(QString p){prenom=p;}
    void setequipe(QString eq){equipe=eq;}
    void setetat(QString e){etat=e;}
    void settype(QString t){type=t;}
    void setnationalite(QString na){nationalite=na;}
    void setid(int ID){id=ID;}
    void setmedaille(int m){medaille=m;}

    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * afficherL();
bool affecter(int,QString);
    QSqlQueryModel * afficherPL();
    bool supprimer(int);
    bool search(int);
    bool modifier(int);


};

#endif // PARTICIPANT_H
