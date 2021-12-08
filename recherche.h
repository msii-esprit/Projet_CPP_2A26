#ifndef RECHERCHE_H
#define RECHERCHE_H

#include <QWidget>

namespace Ui {
class recherche;
}

class recherche : public QWidget
{
    Q_OBJECT

public:
    explicit recherche(QWidget *parent = nullptr);
    ~recherche();

private slots:
    void on_pb_ok_clicked();

private:
    Ui::recherche *ui;
};

#endif // RECHERCHE_H
