#ifndef SPECTATEURS_H
#define SPECTATEURS_H
#include <QString>
#include<QSqlQueryModel>
#include <QRegularExpression>
#include<QSqlTableModel>

class Spectateurs
{
public:
    Spectateurs();
    Spectateurs(int,QString,int,int);
    int getcin();
    int getage();
    int getnum();
    QString getnom();
    void setcin(int);
     void setage(int);
      void setnum(int);
    void setnom(QString);
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
bool modifier();
private:
    int cin,age ,num;
    QString  nom ;
};

#endif // SPECTATEURS_H
