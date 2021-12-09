#include "dialog.h"
#include "ui_dialog.h"
#include <QString>
#include <QMessageBox>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

}

Dialog::~Dialog()
{
    delete ui;
}

bool Dialog::on_pushButton_clicked()
{
    QString m=ui->lineEdit->text();
    QString m1=ui->lineEdit_2->text();

    if((m=="amine")&&(m1=="amine"))
    {
        hide();
        w.show();
    return true;
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    return false;
}
