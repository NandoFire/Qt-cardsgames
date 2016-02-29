#include "mainwindow.h"
#include <QApplication>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>


    int main(int argc, char *argv[])
    {
        QApplication a(argc, argv);
        QGraphicsScene scene;
        QGraphicsView view(&scene);
        QGraphicsPixmapItem item(QPixmap("C:\\Users\\Thiago\\Documents\\Controle e Automação\\LingProg\\carta.jpg"));
        scene.addItem(&item);
        view.show();
        return a.exec();
    }

