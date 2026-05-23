#ifndef CORREDOR_H
#define CORREDOR_H
#include <QPainter>
#include <QPixmap>

class Corredor
{
private:
    float cam_x;
    float x;
    float y;
    float z;
    double vel;
    double velmax;
    int nitro;
    bool cambiando_carril;
    short f_bloq;
    short f_nitro;
    bool imprimible;
    bool volando;
    double vel_z;
    bool act_nitro;
public:
    Corredor();
    void cambiarcarril(bool up,bool dw);
    void acelerar(bool der,bool iz);
    void intobj(short act,float x_);
    void mover(bool espacio);
    void actnitro();
    void pintar(QPainter &painter);
    float getcam_x();
    float getX();
    float getY();
    void setZ(float new_z);
    void setvelmax(double nueva);
    void bloquear(short frames);
    void caer();
    void estavolando(bool colision);
    int getnitro();

};

#endif // CORREDOR_H
