#include "Personnel.h"
#include <QSqlQuery>
#include <QDebug>
#include <QObject>
#include <QDate>
 PERSONNEL:: PERSONNEL()
 {
   nom="";
   prenom=" ";
   CIN=0;
   grade="";

   N_tel=0;
   adress="";
   email="";

 }


 PERSONNEL::PERSONNEL(QString nom,QString prenom,int CIN,QString grade,QDate date_de_naissance,int N_tel,QString adress,QString email)
 {
 this->nom=nom;
 this->prenom=prenom;
 this->CIN=CIN;
 this->grade=grade;
 this->date_de_naissance=date_de_naissance;
 this->N_tel=N_tel;
 this->adress=adress;
 this->email=email;

 }



 void PERSONNEL::setCIN(int CIN)
 {this->CIN=CIN;}
 void PERSONNEL::setnom(QString nom)
 {this->nom=nom;}
 void PERSONNEL::setprenom(QString prenom)
 {this->prenom=prenom;}
 void PERSONNEL::setemail(QString email)
 {this->email=email;}
 void PERSONNEL::setadress(QString adress)
 {this->adress=adress;}
 void PERSONNEL::setgrade(QString grade)
 {this->grade=grade;}
 void PERSONNEL::setN_tel(int N_tel)
 {this->N_tel=N_tel;}
 int PERSONNEL::getCIN(){return CIN  ;}
 int PERSONNEL::getN_tel(){return N_tel ;}
 QString PERSONNEL::getnom(){return nom  ;}
 QString PERSONNEL::getprenom(){return prenom  ;}
 QString PERSONNEL::getemail(){return email  ;}
 QString PERSONNEL::getgrade(){return grade  ;}
 QString PERSONNEL::getadress(){return adress  ;}
 QDate PERSONNEL::getdate_de_naissance(){return date_de_naissance  ;}

// void setCIN(int);
 //void setnom(QString);
 //void setprenom(QString);
// void setdate_de_naissance(QDate);
 void setemail(QString);
 void setgrade(QString);
 void setadress(QString);
 void setN_tel(int);




bool  PERSONNEL :: ajouter()
{

    QSqlQuery query;

    query.prepare("INSERT INTO PERSONNEL (NOM_P,PRENOM_P,CIN_P,GRADE_P,DATE_N_P,ADRESS_P,EMAIL_P,NUM_TEL_P) "
                  "VALUES ( :nom, :prenom, :CIN, :grade, :date_de_naissance, :adress , :email, :N_tel)");

    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":CIN", CIN);
    query.bindValue(":grade", grade);
    query.bindValue(":date_de_naissance", date_de_naissance);
    query.bindValue(":adress", adress);
    query.bindValue(":email", email);
   query.bindValue(":N_tel", N_tel);

   return query.exec();

}



QSqlQueryModel* PERSONNEL ::afficherPersonnel()
{
    QSqlQueryModel* model=new QSqlQueryModel() ;


    model->setQuery("SELECT* FROM PERSONNEL");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM_P"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRENOM_P"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("CIN_P"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("GRADE_P"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE_DE_NAISSANCE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("N_tel"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("ADRESS_P"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("EMAIL_P"));


return model;

}


bool PERSONNEL ::supprimerPersonnel(int personnel)
{

    QSqlQuery query;

         query.prepare("delete from personnel where CIN_P=:CIN_P");
         query.bindValue(":CIN_P", personnel);

              return query.exec();

}




bool PERSONNEL::modifierPersonnel(QString nom,QString prenom,int CIN,QString grade,QDate date_de_naissance,int N_tel,QString adress,QString email )
{
    QSqlQuery query;

    query.prepare("UPDATE PERSONNEL set NOM_P=:nom,PRENOM_P=:prenom,GRADE_P=:grade,DATE_N_P=:date_de_naissance,NUM_TEL_P=:N_tel,ADRESS_P=:adress,EMAIL_P=:email where CIN_P=:cin");

    query.bindValue(":cin",CIN);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":grade",grade);
    query.bindValue(":date_de_naissance",date_de_naissance);
    query.bindValue(":N_tel",N_tel);
    query.bindValue(":adress",adress);
    query.bindValue(":email",email);
    return query.exec();
}






/////////////////////////////// fin d'implementation des crud  /////////////////////////////////


QSqlQueryModel * PERSONNEL::chercherPersonnel(QString recherche)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM personnel WHERE cin_p LIKE '"+recherche+"%' OR nom_p LIKE '"+recherche+"%' OR prenom_p LIKE '"+recherche+"%'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM_P"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRENOM_P"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("CIN_P"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("GRADE_P"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE_DE_NAISSANCE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("N_tel"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("ADRESS_P"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("EMAIL_P"));

    return model;
}



    QSqlQueryModel* PERSONNEL ::trierPersonnel()
{
    QSqlQueryModel* model = new QSqlQueryModel();

        model->setQuery("select *FROM PERSONNEL ORDER BY CIN_P ASC");


    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM_P"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRENOM_P"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("CIN_P"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("GRADE_P"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE_DE_NAISSANCE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("N_tel"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("ADRESS_P"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("EMAIL_P"));


    return model;
}


    QSqlQueryModel* PERSONNEL ::trierPersonnelNom()
{
    QSqlQueryModel* model = new QSqlQueryModel();

        model->setQuery("select *FROM PERSONNEL ORDER BY NOM_P ASC");


    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM_P"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRENOM_P"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("CIN_P"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("GRADE_P"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE_DE_NAISSANCE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("N_tel"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("ADRESS_P"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("EMAIL_P"));


    return model;
}


    QSqlQueryModel* PERSONNEL ::trierPersonnelGrade()
{
    QSqlQueryModel* model = new QSqlQueryModel();

        model->setQuery("select *FROM PERSONNEL ORDER BY GRADE_P ASC");


    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM_P"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRENOM_P"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("CIN_P"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("GRADE_P"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE_DE_NAISSANCE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("N_tel"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("ADRESS_P"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("EMAIL_P"));


    return model;
}









/*

bool PERSONNEL ::supprimerTout()
{ QSqlQuery query;

   query.prepare("delete from personnel ");

  return query.exec();
}

*/









