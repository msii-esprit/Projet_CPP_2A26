#ifndef TRIE_H
#define TRIE_H

#include <QWidget>

namespace Ui {
class TRIE;
}

class TRIE : public QWidget
{
    Q_OBJECT

public:
    explicit TRIE(QWidget *parent = nullptr);
    ~TRIE();

private:
    Ui::TRIE *ui;
};

#endif // TRIE_H
