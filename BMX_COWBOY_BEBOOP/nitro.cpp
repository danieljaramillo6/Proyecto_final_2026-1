#include "nitro.h"

Nitro::Nitro() {}
Nitro::Nitro(float x, float y):Obstaculo(x,y,50,50){}

void Nitro::dibujar(QPainter& painter,float cam_x){
    if(vivo){
        painter.setBrush(Qt::darkBlue);
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(x-cam_x, y, ancho, alto);
    }
    return;
}

short Nitro::colisiona(float px, float py,int pancho,int palto){
    if (px + pancho > x && px < x + ancho && py + palto > y && py < y + alto && vivo){
        vivo=false;
        return 5;
    }
    return 0;
}

