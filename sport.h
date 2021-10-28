#ifndef SPORT_H
#define SPORT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Sport
{
private:
    int id,nbr_p,duree;
    QString nom,type;
public:
    Sport();
    Sport(int,QString,QString,int,int);
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier();

};

#endif // SPORT_H
