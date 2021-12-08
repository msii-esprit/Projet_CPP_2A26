#include "trie.h"
#include "ui_trie.h"

TRIE::TRIE(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TRIE)
{
    ui->setupUi(this);
}

TRIE::~TRIE()
{
    delete ui;
}
