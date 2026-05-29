#ifndef ACANTILADO_H
#define ACANTILADO_H
#include "obstaculo.h"
class Acantilado:public Obstaculo
{
public:
    Acantilado();
    Acantilado(float x,float y);
    void dibujar(QPainter &painter, float cam_x);
    short colisiona(float px, float py,float pz, int pancho, int palto);
};

#endif // ACANTILADO_H
