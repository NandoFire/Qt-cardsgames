#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    QGraphicsScene scene;
//    QGraphicsView view(&scene);
//    QGraphicsPixmapItem item(QPixmap("C:\\Users\\Thiago\\Documents\\Controle e Automação\\LingProg\\carta.jpeg"));
//    scene.addItem(&item);
//    view.show();
//    return a.exec();
//}
