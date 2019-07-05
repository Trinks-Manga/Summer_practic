#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QGraphicsScene>
#include "field.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    MainWindow(Field *F, QWidget *parent = nullptr);
    ~MainWindow();
    QTimer *timer;
    QGraphicsScene *scene;
    QVector <QVector<QGraphicsRectItem *> > fills;
private:
    Field *F;
    Ui::MainWindow *ui;
public slots:
    void start();
    void on_timer_timeout();
};

#endif // MAINWINDOW_H
