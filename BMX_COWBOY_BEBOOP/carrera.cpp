#include "carrera.h"
#include "ui_carrera.h"
#include "corredor.h"
#include <QKeyEvent>

Carrera::Carrera(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Carrera)
{
    n_obstaculos=0;
    n_rampas=0;
    ui->setupUi(this);
    setFixedSize(1200,720);
    timer = new QTimer(this);
    tecla_der=false;
    tecla_dw=false;
    tecla_izq=false;
    tecla_up=false;
    nitro=false;
    connect(timer, &QTimer::timeout, this, &Carrera::onTimer);
    timer->start(16);
    jug=Corredor();

    //obstaculos;
    agregarobs(1,1000.0f,180.0f);
    agregarobs(3,2000.0f,300.0f);
    agregarobs(1,3000.0f,420.0f);
    agregarobs(3,4000.0f,540.0f);
    agregarobs(3,5000.0f,180.0f);
    agregarobs(3,6000.0f,300.0f);
    agregarobs(3,7000.0f,420.0f);
    agregarobs(4,8000.0f,540.0f);
    agregarobs(3,1000.0f,300.0f);
    agregarobs(3,2000.0f,420.0f);
    agregarobs(3,3000.0f,540.0f);
    agregarobs(3,4000.0f,180.0f);
    agregarobs(3,5000.0f,300.0f);
    agregarobs(3,6000.0f,420.0f);
    agregarobs(3,7000.0f,540.0f);
    agregarobs(3,8000.0f,180.0f);
    agregarobs(5,500,300);
    agregarobs(5,1500,300);
    agregarobs(5,2500,300);
    agregarobs(5,3500,300);
    agregarobs(5,4500,540);
    agregarobs(5,5500,420);
    agregarobs(5,6500,300);
    agregarobs(5,7500,300);
    agregarobs(5,8500,300);
    agregarobs(5,9500,300);
    agregarobs(5,10500,540);
    agregarobs(5,11500,420);
    agregarram(1000,420);
}

void Carrera::onTimer(){

    jug.cambiarcarril(tecla_up,tecla_dw);
    jug.acelerar(tecla_der,tecla_izq);

    for(int i = 0; i < n_obstaculos; i++){
        short resultado = obstaculos[i]->colisiona(jug.getX(), jug.getY(),10,15);
        if(resultado != 0){
            jug.intobj(resultado, obstaculos[i]->getX()+obstaculos[i]->getancho());
        }
        else if(resultado==0)jug.setvelmax(10);
    }
    bool enrampa=false;
    for (int i=0;i<n_rampas;i++){
        if (rampas[i]->arriba_rampa(jug.getX(),jug.getY(),10,15)){
            rampas[i]->actz(jug);
            enrampa=true;
            break;
        }
    }
    jug.estavolando(enrampa);
    jug.caer();
    jug.mover(nitro);
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
    if(event->key() == Qt::Key_Q)  nitro  = true;
}

void Carrera::keyReleaseEvent(QKeyEvent* event){
    if(event->key() == Qt::Key_A)  tecla_izq = false;
    if(event->key() == Qt::Key_D) tecla_der = false;
    if(event->key() == Qt::Key_W)    tecla_up  = false;
    if(event->key() == Qt::Key_S)  tecla_dw  = false;
    if(event->key() == Qt::Key_Q)  nitro  = false;
}

void Carrera::paintEvent(QPaintEvent *event){
    QPainter painter(this);

    for (int i=0;i<n_obstaculos;i++){
        obstaculos[i]->dibujar(painter,jug.getcam_x());
    }
    for (int i=0;i<n_rampas;i++){
        rampas[i]->dibujar(painter,jug.getcam_x());
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
        break;
    case 3:
        obstaculos[n_obstaculos++]=new Aceite(x,y);
        break;
    case 4:
        obstaculos[n_obstaculos++]=new Acantilado(x,y);
        break;
    case 5:
        obstaculos[n_obstaculos++]=new Nitro(x,y);
        break;
    default:
        break;
    }
}

void Carrera::agregarram(float x, float y){
    if (n_rampas>=50)return;
    rampas[n_rampas++]=new Rampa(x,y);
    return;
}
