#include "obstaculo.h"

Obstaculo::Obstaculo() {}
Obstaculo::Obstaculo(float x, float y, int ancho, int alto, bool vivo ): x(x), y(y), ancho(ancho), alto(alto), vivo(vivo) {}

bool Obstaculo::estavivo(){
    return vivo;
}

void Obstaculo::matar(){
    vivo=false;
}

void Obstaculo::dibujar(QPainter &painter, float cam_x){
    if (vivo){
    painter.setBrush(Qt::blue);
    painter.setPen(Qt::NoPen);
    painter.drawRect(x-cam_x, y, ancho, alto);
    }
    return;
}

short Obstaculo::colisiona(float x, float y,int pancho,int palto){
    return 0;
}

float Obstaculo::getX(){
    return x;
}

int Obstaculo::getancho(){
    return ancho;
}
