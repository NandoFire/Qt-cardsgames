#ifndef FREECELL_H
#define FREECELL_H

#include <QMainWindow>

namespace Ui {
class freecell;
}

class freecell : public QMainWindow
{
    Q_OBJECT

public:
    explicit freecell(QWidget *parent = 0);
    ~freecell();

private:
    Ui::freecell *ui;
};

#endif // FREECELL_H
