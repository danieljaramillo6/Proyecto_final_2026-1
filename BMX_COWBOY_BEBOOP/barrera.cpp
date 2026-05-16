#include "barrera.h"

Barrera::Barrera() {}
Barrera::Barrera(float x, float y):Obstaculo(x,y,50,50){}

void Barrera::dibujar(QPainter& painter,float cam_x){
    if(vivo){
    painter.setBrush(Qt::black);
    painter.setPen(Qt::NoPen);
    painter.drawRect(x-cam_x, y, ancho, alto);
    }
    return;
}

short Barrera::colisiona(float px, float py,int pancho,int palto){
    if (px + pancho > x && px < x + ancho && py + palto > y && py < y + alto && vivo){
        vivo=false;
        return 1;
    }
    return 0;
}
