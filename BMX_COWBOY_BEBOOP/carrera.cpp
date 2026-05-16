#include "carrera.h"
#include "ui_carrera.h"
#include "corredor.h"
#include <QKeyEvent>

Carrera::Carrera(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Carrera)
{
    n_obstaculos=0;
    ui->setupUi(this);
    setFixedSize(1200,720);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Carrera::onTimer);
    timer->start(16);
    jug=Corredor();

    //obstaculos;
    agregarobs(1,1000.0f,180.0f);
    agregarobs(1,2000.0f,300.0f);
    agregarobs(1,3000.0f,420.0f);
    agregarobs(1,4000.0f,540.0f);
    agregarobs(1,5000.0f,180.0f);
    agregarobs(1,6000.0f,300.0f);
    agregarobs(1,7000.0f,420.0f);
    agregarobs(1,8000.0f,540.0f);
    agregarobs(3,1000.0f,300.0f);
    agregarobs(3,2000.0f,420.0f);
    agregarobs(3,3000.0f,540.0f);
    agregarobs(3,4000.0f,180.0f);
    agregarobs(3,5000.0f,300.0f);
    agregarobs(3,6000.0f,420.0f);
    agregarobs(3,7000.0f,540.0f);
    agregarobs(3,8000.0f,180.0f);
}

void Carrera::onTimer(){

    jug.cambiarcarril(tecla_up,tecla_dw);
    jug.acelerar(tecla_der,tecla_izq);

    //short resultado=0;
    for(int i = 0; i < n_obstaculos; i++){
        short resultado = obstaculos[i]->colisiona(jug.getX(), jug.getY(),10,15);
        if(resultado != 0){
            jug.intobj(resultado, obstaculos[i]->getX()+obstaculos[i]->getancho());
        }
        else if(resultado==0)jug.setvelmax(10);
    }
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

    for (int i=0;i<n_obstaculos;i++){
        obstaculos[i]->dibujar(painter,jug.getcam_x());
    }
    jug.pintar(painter);
}

void Carrera::agregarobs(short tipo,float x,float y){
    if (n_obstaculos>=100)return;//100 es el numero de obstaculos que voy a añadir
    switch(tipo){
    case 1:
        obstaculos[n_obstaculos++]=new Barrera(x,y);
        break;
    case 2:
        obstaculos[n_obstaculos++]=new Bache(x,y);
    case 3:
        obstaculos[n_obstaculos++]=new Aceite(x,y);
    case 4:
        obstaculos[n_obstaculos++]=new Acantilado(x,y);
    }
}
