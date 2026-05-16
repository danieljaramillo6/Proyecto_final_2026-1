#ifndef BACHE_H
#define BACHE_H
#include "obstaculo.h"
#include <QPainter>

class Bache: public Obstaculo
{
public:
    Bache();
    Bache(float x,float y);
    void dibujar(QPainter &painter, float cam_x);
    short colisiona(float px, float py, int pancho, int palto);
};

#endif // BACHE_H
