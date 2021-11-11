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

 int PERSONNEL::getCIN(){return CIN  ;}
 int PERSONNEL::getN_tel(){return N_tel ;}
 QString PERSONNEL::getnom(){return nom  ;}
 QString PERSONNEL::getprenom(){return prenom  ;}
 QString PERSONNEL::getemail(){return email  ;}
 QString PERSONNEL::getgrade(){return grade  ;}
 QString PERSONNEL::getadress(){return adress  ;}
 QDate PERSONNEL::getdate_de_naissance(){return date_de_naissance  ;}





bool  PERSONNEL :: ajouter()
{

    QSqlQuery query;
    //QString CIN_string= QString::number(CIN);
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















/*

/////////////////////////////// finnnn dimplementation des crud  /////////////////////////////////


QSqlQueryModel * PERSONNEL ::chercherPersonnel(int, QString, QString) CIN_P,QString type,QString regime)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * from ANIMAUX where ID_ANIMAL like :id or TYPE_ANIMAL like :type or REGIME_ALIMENT like :regime ");
    query.bindValue(":id",id);// ID VARIABLE LOCAL BA3D BCH NA3MALOU APPEL BIL getIDANIM()
    query.bindValue(":type",type);
    query.bindValue(":regime",regime);
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID  ANIMAL"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM ANIMAL"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPE ANIMAL"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("AGE ANIMAL"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("PAYS ANIMAL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("REGIME ALIMENTAIRE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("STATUS ANIMAL"));

    return model;
}




QSqlQueryModel* PERSONNEL ::trierAnim()
{
    QSqlQueryModel* model = new QSqlQueryModel();

        model->setQuery("select *FROM ANIMAUX ORDER BY ID_ANIMAL ASC");


    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ROLE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("PASS"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("REPASS"));

    return model;
}



bool PERSONNEL ::supprimerTout()
{ QSqlQuery query;

   query.prepare("delete from animaux ");

  return query.exec();
}


*/





/*

 QSqlQueryModel* PERSONNEL::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();


   model->setQuery("SELECT* FROM Personnel");
  model->setHeaderData(0, Qt::Horizontal, QObject:: tr("CIN"));
   model->setHeaderData(1, Qt::Horizontal, QObject:: tr("nom"));
   model->setHeaderData(2, Qt::Horizontal, QObject:: tr("prenom"));
   model->setHeaderData(3, Qt::Horizontal, QObject:: tr("date_de_naissance"));
   model->setHeaderData(4, Qt::Horizontal, QObject:: tr("grede"));
   model->setHeaderData(5, Qt::Horizontal, QObject:: tr("email"));
   model->setHeaderData(6, Qt::Horizontal, QObject:: tr("adress"));
   model->setHeaderData(7, Qt::Horizontal, QObject:: tr("Num_t"));

return model;

}

 bool PERSONNEL::supprimer(int CIN)
{
  QSqlQuery query;
   QString res= QString::number(CIN);
  query.prepare("Delete from Personnel where CIN = :CIN ");
  query.bindValue(":CIN", CIN);
  return    query.exec();
}

*/











