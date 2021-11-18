#include "sport.h"

Sport::Sport()
{

}

Sport::Sport(int Id,QString Nom,QString Type,int Nbr_p,int Duree)
{
    id=Id;
    nom=Nom;
    type=Type;
    nbr_p=Nbr_p;
    duree=Duree;
}

bool Sport::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO SPORT (ID,NOM,TYPE,NBR_PARTICIPANT,DUREE_MATCH) "
                        "VALUES (:id,:nom,:type,:nbr_p,:duree)");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":type", type);
    query.bindValue(":nbr_p", nbr_p);
    query.bindValue(":duree", duree);
    return    query.exec();
}

QSqlQueryModel * Sport::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from SPORT ORDER BY ID ASC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPE"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("NOMBRE PARTICIPANTS"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("DUREE"));

return model;
}



QSqlQueryModel * Sport::triNom(QString cls)
{QSqlQueryModel * model= new QSqlQueryModel();
    QString req="select * from SPORT ORDER BY NOM"+cls;
model->setQuery(req);

model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPE"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("NOMBRE PARTICIPANTS"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("DUREE"));

return model;
}

QSqlQueryModel * Sport::triNbr_p(QString cls)
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from SPORT ORDER BY NBR_PARTICIPANT"+cls);



model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPE"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("NOMBRE PARTICIPANTS"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("DUREE"));

return model;
}

QSqlQueryModel * Sport::triType(QString cls)
{
QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from SPORT ORDER BY TYPE"+cls);
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPE"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("NOMBRE PARTICIPANTS"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("DUREE"));

return model;
}



QSqlQueryModel * Sport::recherche(QString cls)
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from SPORT WHERE ( ID LIKE '%"+cls+"%' OR NOM LIKE '%"+cls+"%' OR TYPE LIKE '%"+cls+"%' OR NBR_PARTICIPANT LIKE '%"+cls+"%' )");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPE"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("NOMBRE PARTICIPANTS"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("DUREE"));

return model;
}

bool Sport::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("Delete from SPORT where ID = :id ");
    query.bindValue(":id", id);
    return    query.exec();
}



bool Sport::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE SPORT SET ID=:id ,NOM=:nom,TYPE=:type,NBR_PARTICIPANT=:nbr_p ,DUREE_MATCH=:duree WHERE ID=:id;");
    query.bindValue(":id", id );
    query.bindValue(":nom",nom);
    query.bindValue(":type",type);
    query.bindValue("nbr_p", nbr_p);
    query.bindValue(":duree", duree);


    return query.exec();

}

void Sport::statistiques(QWidget * w)
{
    int nbm = 0,nbsr=0;
                QSqlQuery query("SELECT COUNT(*) FROM SPORT WHERE type='individuel'");
                while(query.next())
                {
                    nbm = query.value(0).toInt();
                }
                QSqlQuery query2("SELECT COUNT(*) FROM SPORT WHERE type='collectif'");
                while(query2.next())
                {
                   nbsr= query2.value(0).toInt();
                }

            QPieSeries *series = new QPieSeries();

            series->append("Individuel",nbm);
            series->append("Collectif",nbsr);

            series->setHoleSize(0.8);
            series->setPieSize(1.0);

            QPieSlice * I = series->slices().at(0);
            QPieSlice * C = series->slices().at(1);

            I->setLabelVisible(true);
            C->setLabelVisible(true);

            I->setBrush(QColor::fromRgb(255, 0, 0));
            C->setBrush(QColor::fromRgb(0, 0, 255));

            QChart *chart = new QChart();
            chart->addSeries(series);
            chart->setTitle("Types");
            chart->legend()->setVisible(true);
            chart->legend()->setAlignment(Qt::AlignBottom);
            chart->setAnimationOptions(QChart::AllAnimations);

            QChartView * chartview = new QChartView(chart);
            chartview->resize(w->width(),w->height());
            chartview->setParent(w);

}

bool Sport::ajouter_mod(int id,QString a,QDateTime d)
{
    QSqlQuery query;
    QString res = QString::number(id);
    query.prepare("INSERT INTO mod(id,type,date_mod)""VALUES (:id,:type,:date_mod)");
    query.bindValue(":id",id);
    query.bindValue(":type",a);
    query.bindValue(":date_mod",d);
    return query.exec();
}
QSqlQueryModel * Sport::afficher_mod()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM mod");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID sport modifié"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Type"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Date et Temps"));
    return model;
}
