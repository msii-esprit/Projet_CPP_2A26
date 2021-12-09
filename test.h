#ifndef TEST_H
#define TEST_H
#include <QMainWindow>
#include <QString>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlQuery>


class test
{
public:
    test();
    bool ajouter();

private:
     QString nom_T;
};

#endif // TEST_H
