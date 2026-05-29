#include "carrera.h"
#include "ui_carrera.h"
#include "corredor.h"
#include <QKeyEvent>
#include <QFile>

Carrera::Carrera(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Carrera)
{
    sprite_pista=QPixmap(":/sprites/pista.jpg");
    n_nitro=QPixmap(":/sprites/123xsheet.png");
    nitro_sprite=QPixmap(":/sprites/nitro.png");
    linea_meta=QPixmap(":/sprites/linea_meta.png");
    victory=QPixmap(":/sprites/victory.png");
    lose=QPixmap(":/sprites/lose.png");
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
    final=false;
    qDebug() << "antes de enemigo";
    enemigo = Enemigo(500, 300, 3);
    qDebug() << "despues de enemigo";
    cargarMapa();
    qDebug() << "despues de cargarMapa";

}

void Carrera::onTimer(){

    jug.cambiarcarril(tecla_up,tecla_dw);
    jug.acelerar(tecla_der,tecla_izq);

    for(int i = 0; i < n_obstaculos; i++){
        short resultado = obstaculos[i]->colisiona(jug.getX(), jug.getY(),jug.getZ(),10,15);
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
    short col_enemigo = 0;
    for(int i = 0; i < n_obstaculos; i++){
        short r = obstaculos[i]->colisiona(
            enemigo.getX(),
            enemigo.getHitboxY(),
            enemigo.getZ(),
            enemigo.getHitboxAncho(),
            enemigo.getHitboxAlto()
            );
        if(r != 0){
            col_enemigo = r;
            enemigo.intobj(r,obstaculos[i]->getX()+obstaculos[i]->getancho());
        }
    }
    bool enrampae=false;
    for (int i=0;i<n_rampas;i++){
        if (rampas[i]->arriba_rampa(enemigo.getX(),enemigo.getY(),10,15)){
            rampas[i]->actz(enemigo);
            enrampae=true;
            break;
        }
    }
    enemigo.actualizar(col_enemigo, obstaculos, n_obstaculos);
    if (jug.getX()>x_meta){
        jug.final();
        final=true;
    }
    if(enemigo.getX()>x_meta){
        enemigo.final();
    }
    if (!final){
        bool first = jug.getX() > enemigo.getX();
        jug.setPos(first);
        qDebug()<<first;
    }
    enemigo.estavolando(enrampae);
    enemigo.caer();
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
    enemigo.setcam_x(jug.getcam_x());
    enemigo.pintar(painter);
    if (final && jug.getPos()==true){
        painter.drawPixmap(0,100,1200,400,victory);
    }
    else if(final && jug.getPos()==false){
        painter.drawPixmap(0,100,1200,400,lose);
    }
}

void Carrera::agregarobs(short tipo,float x,float y){
    if (n_obstaculos>=200)return;//100 es el numero de obstaculos que voy a añadir
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
    painter.drawPixmap(x_meta-jug.getcam_x(),118,64,490,linea_meta);
}

void Carrera::dibujarnitros(QPainter &painter){
    painter.drawPixmap(50,590,80,80,nitro_sprite);
    if (jug.getnitro()==1)painter.drawPixmap(120,610,50,50,n_nitro,0,0,36,59);
    else if (jug.getnitro()==2)painter.drawPixmap(120,610,50,50,n_nitro,72,0,36,59);
    else if (jug.getnitro()==3)painter.drawPixmap(120,610,50,50,n_nitro,108,0,36,59);
    else painter.drawPixmap(120,610,50,50,n_nitro,36,0,36,59);
    return;
}

void Carrera::cargarMapa(){
    QFile archivo(":/mapa.txt");
    archivo.open(QIODevice::ReadOnly);
    QString datos = archivo.readAll();
    archivo.close();
    QStringList lineas = datos.split("\n");

    for(int i = 0; i < lineas.size(); i++){
        QStringList campos = lineas[i].split(",");

        if(campos.size() < 3) continue; // linea invalida

        short tipo = campos[0].toShort();
        float x    = campos[1].toFloat();
        float y    = campos[2].toFloat();

        if(tipo >= 1 && tipo <= 5){
            agregarobs(tipo, x, y);
        }
        else if(tipo == 6){
            agregarram(x, y);
        }
        else if(tipo == 7){
            x_meta=x;
        }
    }
}
