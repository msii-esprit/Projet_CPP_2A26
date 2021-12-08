#ifndef FACTURE_H
#define FACTURE_H



#include <QMainWindow>

#include <QSqlQueryModel>



class Facture
{

public:
    Facture();
    Facture(int,QString,QString,int,int,int,QString);
    int getcin();
    void setcin(int cin);
    QString getnom();
    void setnom(QString);
    QString getprenom();
    void setprenom(QString);
    int getnbr();
    void setnbr(int);
    int getduree();
    void setduree(int);
    float getsomme();
    void setsomme(int);
    QString getemail();
    void setemail(QString);

    bool ajouter();
    QSqlQueryModel* afficher();
    float CalculSomme(int,int );
    float rowlast(int ,const int);

private:
   int cin,nbr,duree;
   QString nom,prenom,email;
   int somme;
};

#endif // FACTURE_H


