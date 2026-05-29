#include "barrera.h"

Barrera::Barrera() {}
Barrera::Barrera(float x, float y):Obstaculo(x,y,50,50){
    sprite = QPixmap(":/sprites/barrera.png");
    if(sprite.isNull()){
        qDebug() << "no cargo la imagen";
    }
}

void Barrera::dibujar(QPainter& painter,float cam_x){
    if(vivo){

    painter.drawPixmap(x-cam_x-50, y-100, ancho+100, alto+100,sprite);
    }
    return;
}

short Barrera::colisiona(float px, float py,float pz,int pancho,int palto){
    if (px + pancho > x && px < x + ancho && py + palto > y && py < y + alto && vivo){
        if (pz==0)vivo=false;
        return 1;
    }
    return 0;
}
