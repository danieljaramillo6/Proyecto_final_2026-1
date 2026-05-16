#include "aceite.h"

Aceite::Aceite() {}
Aceite::Aceite(float x, float y):Obstaculo(x,y,50,50){}

void Aceite::dibujar(QPainter& painter,float cam_x){
    if(vivo){
        painter.setBrush(Qt::blue);
        painter.setPen(Qt::NoPen);
        painter.drawRect(x-cam_x, y, ancho, alto);
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
