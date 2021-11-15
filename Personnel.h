#ifndef PERSONNEL_H
#define PERSONNEL_H

#include<QString>
#include<QSqlQueryModel>
#include <QDate>

class PERSONNEL
{
public :
    PERSONNEL();
    PERSONNEL(QString,QString,int,QString,QDate,int,QString,QString);
    int getCIN();
    QString getnom();
    QString getprenom();
    QDate getdate_de_naissance();
    QString getgrade();
    QString getemail();
    QString getadress();
    int getN_tel();
    void setCIN(int);
    void setnom(QString);
    void setprenom(QString);
    void setdate_de_naissance(QDate);
    void setemail(QString);
    void setgrade(QString);
    void setadress(QString);
    void setN_tel(int);



    bool ajouter();
    QSqlQueryModel* afficher();


        QSqlQueryModel* afficherPersonnel();

        bool supprimerPersonnel(int);

        bool modifierPersonnel(QString,QString,int,QString,QDate,int,QString,QString );
        QSqlQueryModel*  chercherPersonnel(QString);

         QSqlQueryModel* trierPersonnel();
         bool supprimerTout();




private:
    int CIN,N_tel;
    QString prenom;
    QString nom;
    QDate date_de_naissance;
    QString grade;
    QString email;
    QString adress;

};

#endif // PERSONNEL_H
