#include "bache.h"

Bache::Bache() {}
Bache::Bache(float x, float y):Obstaculo(x,y,50,50){}
void Bache::dibujar(QPainter& painter,float cam_x){
    if(vivo){
        painter.setBrush(Qt::yellow);
        painter.setPen(Qt::NoPen);
        painter.drawRect(x-cam_x, y, ancho, alto);
    }
    return;
}

short Bache::colisiona(float px, float py, int pancho, int palto){
    if (px + pancho > x && px < x + ancho && py + palto > y && py < y + alto && vivo){
        return 2;
    }
    return 0;
}
