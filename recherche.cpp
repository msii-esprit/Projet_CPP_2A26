#include "recherche.h"
#include "ui_recherche.h"

recherche::recherche(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::recherche)
{
    ui->setupUi(this);
}

recherche::~recherche()
{
    delete ui;
}
