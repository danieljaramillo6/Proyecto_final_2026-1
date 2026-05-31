#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "carrera.h"
#include "bmx.h"

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

void MainWindow::on_pushButton_2_clicked()
{
    BMX *b = new BMX();
    b->show();
    this->hide();
    connect(b, &BMX::volver, this, [this, b](){
        b->close();
        this->show();
    });
}
