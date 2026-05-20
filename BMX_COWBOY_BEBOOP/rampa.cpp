#include "rampa.h"


Rampa::Rampa() {}
Rampa::Rampa(float x, float y){
    this->x=x;
    this->y=y;
    ancho=100;
    alto=100;
}

bool Rampa::arriba_rampa(float px,float py, float pancho,float palto){
    if (px + pancho > x && px < x + ancho && py + palto > y && py < y + alto ){
        return true;
    }
    return false;
}

void Rampa::actz(Corredor &corredor){
    corredor.setZ(corredor.getX()-x);
    return;
}

void Rampa::dibujar(QPainter &painter,float camX){
    QPolygon triangulo;
    triangulo << QPoint(x - camX, y + alto)        // esquina inferior izquierda
              << QPoint(x - camX + ancho, y + alto) // esquina inferior derecha
              << QPoint(x - camX + ancho, y);        // punta superior derecha

    painter.setBrush(Qt::gray);
    painter.setPen(Qt::NoPen);
    painter.drawPolygon(triangulo);
}
