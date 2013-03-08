#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    animationTimer(NULL),
    calcTimer(NULL)
{
    ui->setupUi(this);

    // we create a simple timer, with the widget being its parent
    animationTimer = new QTimer(this);
    // the timer will send a signal timeout at regular intervals.
    // whenever this timeout signal occurs, we want it to call our drawOpenGL
    // function
    calcTimer = new QTimer(this);
    connect(animationTimer, SIGNAL(timeout()), this, SLOT(drawOpenGL()));
    connect(calcTimer, SIGNAL(timeout()), this, SLOT(calcOpenGL()));
    // we start the timer with a timeout interval of 20ms
    animationTimer->start(20);
    calcTimer->start(5);
    //initPoints();
}

void MainWindow::drawOpenGL()
{
    ui->display->repaint();
}

void MainWindow::calcOpenGL()
{

}

MainWindow::~MainWindow()
{
    delete ui;
}
