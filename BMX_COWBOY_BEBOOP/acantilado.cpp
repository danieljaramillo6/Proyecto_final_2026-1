#include "acantilado.h"

Acantilado::Acantilado() {}
Acantilado::Acantilado(float x, float y):Obstaculo(x,y,50,50){}
void Acantilado::dibujar(QPainter& painter,float cam_x){
    if(vivo){
        painter.setBrush(Qt::red);
        painter.setPen(Qt::NoPen);
        painter.drawRect(x-cam_x, y, ancho, alto);
    }
    return;
}

short Acantilado::colisiona(float px, float py, int pancho, int palto){
    if (px + pancho > x && px < x + ancho && py + palto > y && py < y + alto && vivo){
        return 4;
    }
    return 0;
}
