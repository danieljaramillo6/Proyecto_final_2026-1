#include "nitro.h"

Nitro::Nitro() {}
Nitro::Nitro(float x, float y):Obstaculo(x,y,50,50){
    sprite = QPixmap(":/sprites/nitro.png");
    if(sprite.isNull()){
        qDebug() << "no cargo la imagen";
    }
}

void Nitro::dibujar(QPainter& painter,float cam_x){
    if(vivo){
        painter.setBrush(Qt::darkBlue);
        painter.setPen(Qt::NoPen);
        painter.drawPixmap(x-cam_x, y-20, ancho, alto,sprite);
    }
    return;
}

short Nitro::colisiona(float px, float py,float pz,int pancho,int palto){
    if (px + pancho > x && px < x + ancho && py + palto > y && py < y + alto && vivo){
        vivo=false;
        return 5;
    }
    return 0;
}

