#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setCurrent()
{
    int w = this->width();
    int h = this->height();
    ui->label->setText("window width: " + QString::number(w) +
                       "\nwindow heigth: " + QString::number(h));
}

void MainWindow::resizeEvent( QResizeEvent *e )
{
  QMainWindow::resizeEvent(e);
  setCurrent();
}

void MainWindow::on_actionminimum_size_triggered()
{
    this->resize(this->minimumSize());
}

void MainWindow::on_actionmaximum_size_triggered()
{

    this->resize(this->maximumSize());
}

void MainWindow::on_action500x500_triggered()
{
    this->resize(500,500);
}

void MainWindow::on_action400x400_triggered()
{
    this->resize(400,400);
}

void MainWindow::on_action300x300_triggered()
{
    this->resize(300,300);
}

void MainWindow::on_s200_triggered()
{
    this->resize(200,200);
}
