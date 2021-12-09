#ifndef SPORT_H
#define SPORT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QWidget>
#include <QtCharts/QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>

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
    QSqlQueryModel * triNom(QString);
    QSqlQueryModel * triNbr_p(QString);
    QSqlQueryModel * triType(QString);
    QSqlQueryModel * recherche(QString);
    void statistiques(QWidget*);
    bool ajouter_mod(int,QString,QDateTime);
    QSqlQueryModel * afficher_mod();
};

#endif // SPORT_H
