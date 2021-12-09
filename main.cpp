#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include "participant.h"

#include <QDebug>
#include "utils.h"
#include "Dataset.h"
#include "LinearRegressionModel.h"
#include <algorithm>
#include <ostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include "dialog.h"
#include <QTextStream>
#include <QFile>




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Connection c;
    bool test=c.createconnect();
    MainWindow w;
    Dialog d;
d.show();



    if(test)
    {

        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}







    return a.exec();

}
