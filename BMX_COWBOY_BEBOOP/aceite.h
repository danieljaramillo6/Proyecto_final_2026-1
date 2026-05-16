#ifndef ACEITE_H
#define ACEITE_H
#include "obstaculo.h"

class Aceite:public Obstaculo
{
public:
    Aceite();
    Aceite(float x,float y);
    void dibujar(QPainter& painter,float cam_x);
    short colisiona(float px,float py,int pancho,int palto);
};

#endif // ACEITE_H
