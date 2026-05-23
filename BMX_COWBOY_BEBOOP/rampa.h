#ifndef RAMPA_H
#define RAMPA_H
#include "corredor.h"
#include <QPainter>
#include <QPixmap>

class Rampa
{
private:
    float x,y,alto,ancho;
    QPixmap sprite;
public:
    Rampa();
    Rampa(float x,float y);
    bool arriba_rampa(float px,float py,float pancho,float palto);
    void actz(Corredor &corredor);
    void dibujar(QPainter &painter,float camX);
};

#endif // RAMPA_H
