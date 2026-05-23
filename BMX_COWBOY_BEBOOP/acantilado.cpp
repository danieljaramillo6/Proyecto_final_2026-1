#include "acantilado.h"

Acantilado::Acantilado() {}
Acantilado::Acantilado(float x, float y):Obstaculo(x,y,50,50){
    sprite = QPixmap(":/sprites/pozo.png");
    if(sprite.isNull()){
        qDebug() << "no cargo la imagen";
    }
}
void Acantilado::dibujar(QPainter& painter,float cam_x){
    if(vivo){

        painter.drawPixmap(x-cam_x-20, y-35, ancho+30, alto+30,sprite);
    }
    return;
}

short Acantilado::colisiona(float px, float py, int pancho, int palto){
    if (px + pancho > x && px < x + ancho && py + palto > y && py < y + alto && vivo){
        return 4;
    }
    return 0;
}
