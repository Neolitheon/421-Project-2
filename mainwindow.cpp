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
//    int progress = ui->display->return_progress();
//    printf("%d\n", progress);
//    ui->progressBar->setValue(progress);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_start_clicked()
{
    ui->display->start();
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    ui->display->set_maximum_iterations(position);
    ui->lcdNumber->setProperty("value", position);
}

void MainWindow::on_horizontalSlider_3_sliderMoved(int position)
{
    ui->display->set_training_set_size(position);
    ui->lcdNumber_2->setProperty("value", position);
}

void MainWindow::on_horizontalSlider_2_sliderMoved(int position)
{
    ui->display->set_perceptron_degree(position);
    ui->lcdNumber_3->setProperty("value", position);
}

void MainWindow::on_radioButton_9_clicked()
{
    bool radio9 = ui->radioButton_9->isChecked();
    if (radio9)
        ui->frame_5->setEnabled(true);
    else
        ui->frame_5->setEnabled(false);
    ui->display->set_analysis(radio9);
}

void MainWindow::on_radioButton_8_clicked()
{
    bool radio9 = ui->radioButton_9->isChecked();
    if (radio9)
        ui->frame_5->setEnabled(true);
    else
        ui->frame_5->setEnabled(false);
    ui->display->set_analysis(radio9);
}

void MainWindow::on_radioButton_clicked()
{
    ui->display->set_data_set(0);
}

void MainWindow::on_radioButton_2_clicked()
{
    ui->display->set_data_set(1);
}

void MainWindow::on_radioButton_3_clicked()
{
    ui->display->set_data_set(2);
}

void MainWindow::on_radioButton_4_clicked()
{
    ui->display->set_data_set(3);
}

void MainWindow::on_radioButton_5_clicked()
{
    ui->display->set_algorithm(0);
}

void MainWindow::on_radioButton_6_clicked()
{
    ui->display->set_algorithm(1);
}

void MainWindow::on_radioButton_7_clicked()
{
    ui->display->set_algorithm(2);
}
