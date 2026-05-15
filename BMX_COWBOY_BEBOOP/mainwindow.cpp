#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "carrera.h"

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

void MainWindow::on_pushButton_clicked()
{
    Carrera *c=new Carrera();
    c->show();
    this->hide();
    connect(c,&Carrera::volver,this,[this,c](){
        c->close();
        this->show();
    });
}

