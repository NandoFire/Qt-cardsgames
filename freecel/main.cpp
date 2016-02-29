#include "freecell.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    freecell w;
    w.show();

    return a.exec();
}
