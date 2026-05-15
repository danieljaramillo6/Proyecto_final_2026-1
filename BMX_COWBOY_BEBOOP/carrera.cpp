#include "carrera.h"
#include "ui_carrera.h"
#include "corredor.h"
#include <QKeyEvent>

Carrera::Carrera(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Carrera)
{
    ui->setupUi(this);
    setFixedSize(1000,720);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Carrera::onTimer);
    timer->start(16);
    jug=Corredor();
}

void Carrera::onTimer(){

    jug.cambiarcarril(tecla_up,tecla_dw);
    jug.acelerar(tecla_der,tecla_izq);
    jug.mover();
    update();
}

Carrera::~Carrera()
{
    delete ui;
}

void Carrera::on_pushButton_clicked()
{
    emit volver();
}

void Carrera::keyPressEvent(QKeyEvent* event){
    if(event->key() == Qt::Key_A)  tecla_izq = true;
    if(event->key() == Qt::Key_D) tecla_der = true;
    if(event->key() == Qt::Key_W)    tecla_up  = true;
    if(event->key() == Qt::Key_S)  tecla_dw  = true;
}

void Carrera::keyReleaseEvent(QKeyEvent* event){
    if(event->key() == Qt::Key_A)  tecla_izq = false;
    if(event->key() == Qt::Key_D) tecla_der = false;
    if(event->key() == Qt::Key_W)    tecla_up  = false;
    if(event->key() == Qt::Key_S)  tecla_dw  = false;
}

void Carrera::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    jug.pintar(painter);
}
