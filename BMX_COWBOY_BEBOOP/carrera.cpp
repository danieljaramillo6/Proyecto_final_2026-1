#include "carrera.h"
#include "ui_carrera.h"
#include "corredor.h"
#include <QKeyEvent>

Carrera::Carrera(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Carrera)
{
    sprite_pista=QPixmap(":/sprites/pista.jpg");
    n_nitro=QPixmap(":/sprites/123xsheet.png");
    nitro_sprite=QPixmap(":/sprites/nitro.png");

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

    agregarobs(4,1100.0f,420.0f);
    agregarobs(4,8000.0f,540.0f);


    agregarobs(4,3000.0f,540.0f);

    agregarobs(4,5000.0f,300.0f);


    agregarobs(4,8000.0f,180.0f);

    agregarobs(4,1500,300);
    agregarobs(2,2500,300);
    agregarobs(5,3500,300);
    agregarobs(5,4500,540);
    agregarobs(5,5500,420);
    agregarobs(5,6500,300);
    agregarobs(1,7500,300);
    agregarobs(1,8500,300);
    agregarobs(1,9500,300);
    agregarobs(1,10500,540);
    agregarobs(1,11500,420);
    agregarram(1000,180);
    agregarram(1000,300);
    agregarram(1000,420);
    agregarram(1000,540);
    agregarram(4000,180);
    agregarram(4000,300);
    agregarram(4000,420);
    agregarram(4000,540);
    agregarram(1000,180);
    agregarram(1000,300);
    agregarram(1000,420);
    agregarram(1000,540);
    agregarram(8000,180);
    agregarram(8000,300);
    agregarram(8000,420);
    agregarram(8000,540);
    agregarram(12000,180);
    agregarram(12000,300);
    agregarram(12000,420);
    agregarram(12000,540);
    agregarram(16000,180);
    agregarram(16000,300);
    agregarram(16000,420);
    agregarram(16000,540);

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
    dibujarPista(painter);
    dibujarnitros(painter);

    for (int i=0;i<n_rampas;i++){
        rampas[i]->dibujar(painter,jug.getcam_x());
    }
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

void Carrera::dibujarPista(QPainter& painter){
    int ancho_tile = sprite_pista.width();
    int offset = (int)jug.getcam_x() % ancho_tile;

    for(int x = -offset; x < width() + ancho_tile; x += ancho_tile){
        painter.drawPixmap(x, 0, ancho_tile, height(), sprite_pista);
    }
}
void Carrera::dibujarnitros(QPainter &painter){
    painter.drawPixmap(50,590,80,80,nitro_sprite);
    if (jug.getnitro()==1)painter.drawPixmap(120,610,50,50,n_nitro,0,0,36,59);
    else if (jug.getnitro()==2)painter.drawPixmap(120,610,50,50,n_nitro,72,0,36,59);
    else if (jug.getnitro()==3)painter.drawPixmap(120,610,50,50,n_nitro,108,0,36,59);
    else painter.drawPixmap(120,610,50,50,n_nitro,36,0,36,59);
    return;
}
