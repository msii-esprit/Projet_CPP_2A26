#ifndef DIALOG_H
#define DIALOG_H
#include "mainwindow.h"

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
public slots:
    bool on_pushButton_clicked();

private:
    Ui::Dialog *ui;
    MainWindow w;
};

#endif // DIALOG_H
