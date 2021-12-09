#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "participant.h"
#include <QStyleOptionViewItem>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public slots:
    void on_pushButtonajouterclicked();



public slots:

    void connectEquipe();
    void on_pushButton_clicked();
    void connectEquipeM();

    QModelIndex on_tableView_activated( QModelIndex index);
bool search(int);





private slots:
void on_pushButton_modifier_clicked();



void on_buttonBox_accepted();

void on_buttonBox_rejected();





void on_lineEdit_R_returnPressed();




void on_pushButton_predict_clicked();


void on_tableWidget_5_activated( QModelIndex index);



void on_comboBox_class1_1_currentIndexChanged(int index);

void on_comboBox_class1_2_currentIndexChanged(int index);

void on_comboBox_class1_3_currentIndexChanged(int index);

void on_comboBox_class1_4_currentIndexChanged(int index);

void on_comboBox_class2_1_currentIndexChanged(int index);

void on_comboBox_class2_2_currentIndexChanged(int index);

void on_comboBox_class2_3_currentIndexChanged(int index);

void on_comboBox_class2_4_currentIndexChanged(int index);

void on_comboBox_class3_1_currentIndexChanged(int index);

void on_comboBox_class3_2_currentIndexChanged(int index);

void on_comboBox_class3_3_currentIndexChanged(int index);

void on_comboBox_class3_4_currentIndexChanged(int index);

void on_comboBox_class4_1_currentIndexChanged(int index);

void on_comboBox_class4_2_currentIndexChanged(int index);

void on_comboBox_class4_3_currentIndexChanged(int index);

void on_comboBox_class4_4_currentIndexChanged(int index);

void on_pushButton_tirage5_clicked();

void on_toolButton_clicked();

void on_lineEdit_R_cursorPositionChanged(int arg1, int arg2);



void on_tableView_2_clicked(const QModelIndex &index);

void on_tableView_3_activated(const QModelIndex &index);

void on_button_2_clicked();

private:
    Ui::MainWindow *ui;

    participant p;


    int y=0;
};
#endif // MAINWINDOW_H
