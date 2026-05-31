#ifndef RAMPA_BMX_H
#define RAMPA_BMX_H
#include <QPainter>
#include "corredor_bmx.h"

class Rampa_bmx
{
private:
    float x, y, ancho, alto;
public:
    Rampa_bmx();

    Rampa_bmx(float x, float y);

    bool arriba_rampa(float px, float py, float pancho, float palto);

    void actz(Corredor_bmx& corredor);

    void dibujar(QPainter& painter, float cam_x);
};

#endif // RAMPA_BMX_H
