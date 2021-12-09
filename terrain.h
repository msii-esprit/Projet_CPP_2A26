#ifndef TERRAIN_H
#define TERRAIN_H
#include<QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlQueryModel>

class Terrain
{
public:
    Terrain();
    Terrain(int,QString,QString,QString);
    int getcapacite();
    QString getnom_T();
    QString gettype_T();
    QString getetat_T();
    void setcapacite(int);
    void setnom_T(QString);
    void settype_T(QString);
    void setetat_T(QString);

    bool ajouter();
    bool supprimer(QString);
    QSqlQueryModel* afficher();
    bool modifier(QString);
    QSqlQueryModel* rechercher(QString);
    QSqlQueryModel* trier_n();
    QSqlQueryModel* trier_t();
    QSqlQueryModel* trier_c();




private:

    int capacite;
    QString nom_T;
    QString type_T;
    QString etat_T;


};

#endif // TERRAIN_H
