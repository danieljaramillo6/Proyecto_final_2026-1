#ifndef CORREDOR_H
#define CORREDOR_H
#include <QPainter>

class Corredor
{
private:
    float cam_x;
    float x;
    float y;
    double vel;
    double velmax;
    bool nitro;
    bool cambiando_carril;
    short f_bloq;
    bool imprimible;
public:
    Corredor();
    void cambiarcarril(bool up,bool dw);
    void acelerar(bool der,bool iz);
    void intobj(short act,float x_);
    void mover();
    void pintar(QPainter &painter);
    float getcam_x();
    float getX();
    float getY();
    void setvelmax(double nueva);
    void bloquear(short frames);

};

#endif // CORREDOR_H
