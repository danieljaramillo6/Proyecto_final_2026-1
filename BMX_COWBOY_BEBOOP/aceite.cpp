#include "aceite.h"
#include <QDebug>

Aceite::Aceite() {}
Aceite::Aceite(float x, float y):Obstaculo(x,y,50,50){
    sprite = QPixmap("C:/Users/danie/Documents/Proyecto_final/BMX_COWBOY_BEBOOP/aceite.png");
    if(sprite.isNull()){
        qDebug() << "no cargo la imagen";
    }

}

void Aceite::dibujar(QPainter& painter,float cam_x){
    if(vivo){
        painter.setBrush(Qt::blue);
        painter.setPen(Qt::NoPen);
        painter.drawPixmap(x-cam_x, y, ancho, alto,sprite);
    }
    return;
}

short Aceite::colisiona(float px, float py,int pancho,int palto){
    if (px + pancho > x && px < x + ancho && py + palto > y && py < y + alto && vivo){
        vivo=false;
        return 3;
    }
    return 0;
}
