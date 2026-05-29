#include "aceite.h"
#include <QDebug>

Aceite::Aceite() {}
Aceite::Aceite(float x, float y):Obstaculo(x,y,50,50){
    sprite = QPixmap(":/sprites/aceite.png");
    if(sprite.isNull()){
        qDebug() << "no cargo la imagen";
    }

}

void Aceite::dibujar(QPainter& painter,float cam_x){
    if(vivo){
        painter.setBrush(Qt::blue);
        painter.setPen(Qt::NoPen);
        painter.drawPixmap(x-cam_x, y-30, ancho+70, alto+70,sprite);
    }
    return;
}

short Aceite::colisiona(float px, float py,float pz,int pancho,int palto){
    if (px + pancho > x && px < x + ancho && py + palto > y && py < y + alto && vivo){
        if(pz==0)vivo = false;
        return 3;
    }
    return 0;
}
