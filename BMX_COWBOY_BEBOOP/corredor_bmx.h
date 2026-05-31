#ifndef CORREDORBMX_H
#define CORREDORBMX_H
#include <QPainter>
#include <QPixmap>

class Corredor_bmx
{
private:

    float x;
    float y;

    float vel;
    float velmax;

    float vel_y;
    float gravedad;
    float salto;

    bool  volando;

    float cam_x;

    bool  imprimible;

    short f_bloq;

    float piso;

public:

    Corredor_bmx();

    void mover();

    void pintar(QPainter& painter);

    void caer();

    void saltar();

    void intobj(short act, float x_);

    void acelerar(bool der, bool iz);

    void estavolando(bool colision);

    void bloquear(short frames);

    void setvelmax(float nueva);

    float getcam_x();

    float getX();

    float getY();

    float getSalto();

    void setSalto(float nuevo);

    float getVel();


};

#endif // CORREDORBMX_H
