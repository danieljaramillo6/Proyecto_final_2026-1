#include "rampa_bmx.h"

Rampa_bmx::Rampa_bmx() {}

Rampa_bmx::Rampa_bmx(float x, float y){
    this->x   = x;
    this->y   = y;
    ancho     = 100;
    alto      = 100;
}

bool Rampa_bmx::arriba_rampa(float px, float py, float pancho, float palto){
    if(px + pancho > x && px < x + ancho && py + palto > y && py < y + alto)
    {
        return true;
    }
    return false;
}

void Rampa_bmx::actz(Corredor_bmx& corredor){
    corredor.saltar();
}

void Rampa_bmx::dibujar(QPainter& painter, float cam_x){
    float rx = x - cam_x;
    QPolygonF triangulo;
    triangulo << QPointF(rx, y + alto)
              << QPointF(rx + ancho, y + alto)
              << QPointF(rx + ancho, y);
    painter.setBrush(Qt::gray);
    painter.setPen(Qt::NoPen);
    painter.drawPolygon(triangulo);
}
