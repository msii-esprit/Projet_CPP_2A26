#ifndef STAT_H
#define STAT_H

#include <QDialog>
#include"qcustomplot.h"
#include<QSqlQuery>
#include<QSqlQueryModel>

namespace Ui {
class Servicestat;
}

class Servicestat : public QDialog
{
    Q_OBJECT

public:
    explicit Servicestat(QWidget *parent = nullptr);
    ~Servicestat();
    void makePlot();

private:
    Ui::Servicestat *ui;
};

#endif // STAT_H
