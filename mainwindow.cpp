#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "field.h"
#include <QTimer>
#include <QGraphicsRectItem>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow::MainWindow(Field *F, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    timer = new QTimer();
    this->F = F;
    timer->setInterval(100);
    QObject::connect(timer, SIGNAL(timeout()), SLOT(on_timer_timeout()));
    QObject::connect(ui->pushButton, SIGNAL(clicked()),this, SLOT(start()));
    scene = new QGraphicsScene(0,0,ui->graphicsView->viewport()->width(), ui->graphicsView->viewport()->height());
    fills.resize(Field::sizeMap);
    for (int i = 0; i < Field::sizeMap; i++){
        fills[i].resize(Field::sizeMap);
        for (int j =0; j < Field::sizeMap; j++){
            QGraphicsRectItem* q = new QGraphicsRectItem(QRect(0, 0, Field::cellsize, Field::cellsize));
            if (F->map[i][j] == wall);
            else {
                q->setBrush(Qt::white);
            }
            q->setPen(QPen(Qt::black));
            scene->addItem(q);
            q->setPos(i * Field::cellsize, j * Field::cellsize);
            fills[i][j] = q;
        }
    }
    ui->graphicsView->setScene(scene);
}


void MainWindow::start(){
    if (!timer->isActive())
    timer->start();
}


void MainWindow::on_timer_timeout(){
    F->update();
     for (int i = 0; i < Field::sizeMap; i++)
         for (int j = 0; j < Field::sizeMap; j++){
             int temp = F->map[i][j];
             if (temp == 0)
                 fills[i][j]->setBrush(Qt::white);
             else
                 if (temp == stockman)
                     fills[i][j]->setBrush(Qt::green);
                 else {
                     if (temp == Pests)
                         fills[i][j]->setBrush(Qt::red);
                     else
                         if(temp == trap)
                             fills[i][j]->setBrush(Qt::blue);
                     else
                             if (temp == wall)
                                 fills[i][j]->setBrush(Qt::black);
                             else {
                                 if (temp == box)
                                     fills[i][j]->setBrush(Qt::gray);
                             }
                 }
         }
    ui->label_2->setText(QString::number(F->En[0]->PayDay(0)));
    ui->graphicsView->setScene(scene);
}
