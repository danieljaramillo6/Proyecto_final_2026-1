#ifndef CORREDOR_H
#define CORREDOR_H
#include <QPainter>

class Corredor
{
private:
    float x;
    float y;
    double vel;
    double velmax;
    bool nitro;
    bool cambiando_carril;
public:
    Corredor();
    void cambiarcarril(bool up,bool dw);
    void acelerar(bool der,bool iz);
    void intobj();
    void detectartecla();
    void mover();
    void pintar(QPainter &painter);
};

#endif // CORREDOR_H
