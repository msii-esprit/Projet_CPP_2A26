#include "genererfacturepdf.h"
#include "ui_genererfacturepdf.h"

GenererFacturePDF::GenererFacturePDF(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GenererFacturePDF)
{
    ui->setupUi(this);
}

GenererFacturePDF::~GenererFacturePDF()
{
    delete ui;
}
