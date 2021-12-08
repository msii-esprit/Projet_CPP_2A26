#ifndef GENERERFACTUREPDF_H
#define GENERERFACTUREPDF_H

#include <QWidget>

namespace Ui {
class GenererFacturePDF;
}

class GenererFacturePDF : public QWidget
{
    Q_OBJECT

public:
    explicit GenererFacturePDF(QWidget *parent = nullptr);
    ~GenererFacturePDF();

private:
    Ui::GenererFacturePDF *ui;
};

#endif // GENERERFACTUREPDF_H
