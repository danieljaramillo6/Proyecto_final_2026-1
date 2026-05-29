#ifndef CORREDOR_H
#define CORREDOR_H
#include <QPainter>
#include <QPixmap>

class Corredor
{
protected:
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
    bool caido;
    bool acelerando;
    short n_sprite;
    short frame;
    QPixmap sprite;
    QPixmap sprite_caido;
    bool termino;
    bool primero;

public:
    Corredor();
    void cambiarcarril(bool up,bool dw);
    void acelerar(bool der,bool iz);
    void intobj(short act,float x_);
    void mover(bool espacio);;
    virtual void pintar(QPainter &painter);
    float getcam_x();
    float getX();
    float getY();
    float getZ();
    void setZ(float new_z);
    void setvelmax(double nueva);
    void bloquear(short frames);
    void caer();
    void estavolando(bool colision);
    int getnitro();
    void final();
    void setPos(bool pos);
    bool getPos()const;
    int getHitboxAncho() const { return 80; }
    int getHitboxAlto()  const { return 80; }
    int getHitboxY()     const { return y - 60; }
};

#endif // CORREDOR_H
