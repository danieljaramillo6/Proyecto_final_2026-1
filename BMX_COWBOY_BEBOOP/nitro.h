#ifndef NITRO_H
#define NITRO_H
#include "obstaculo.h"

class Nitro:public Obstaculo
{
public:
    Nitro();
    Nitro(float x,float y);
    void dibujar(QPainter& painter,float cam_x);
    short colisiona(float px,float py,int pancho,int palto);
};

#endif // NITRO_H
