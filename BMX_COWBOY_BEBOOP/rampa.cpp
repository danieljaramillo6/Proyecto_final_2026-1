#include "rampa.h"


Rampa::Rampa() {}
Rampa::Rampa(float x, float y){
    this->x=x;
    this->y=y;
    ancho=100;
    alto=100;
    sprite=QPixmap(":/sprites/rampa.png");
}

bool Rampa::arriba_rampa(float px,float py, float pancho,float palto){
    if (px + pancho > x && px < x + ancho && py + palto > y && py < y + alto ){
        return true;
    }
    return false;
}

void Rampa::actz(Corredor &corredor){
    if (corredor.getZ()>corredor.getX()-x)return;
    corredor.setZ(corredor.getX()-x);
    return;
}

void Rampa::dibujar(QPainter &painter,float camX){
    painter.drawPixmap(x-camX, y-135, ancho+20, alto+140,sprite);
}
