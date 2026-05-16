#ifndef BARRERA_H
#define BARRERA_H
#include "obstaculo.h"
#include <QPainter>

class Barrera : public Obstaculo
{
public:
    Barrera();
    Barrera(float x,float y);
    void dibujar(QPainter& painter,float cam_x);
    short colisiona(float px,float py,int pancho,int palto);

};

#endif // BARRERA_H
