#include "corredor_bmx.h"

Corredor_bmx::Corredor_bmx() {

    x          = 30;
    y          = 300;

    vel        = 0;
    velmax     = 10;

    vel_y      = 0;
    gravedad   = 0.5;
    salto      = 12;

    piso       = 300;

    cam_x      = 0;

    volando    = false;

    imprimible = true;

    f_bloq     = 0;
}

void Corredor_bmx::mover(){ //avanza al jugador y la cámara sumando vel a x y cam_x. Si está bloqueado descuenta el contador y no mueve nada

    if(f_bloq > 0){
        f_bloq--;
        return; // acaba el metodo de entrar al if
    }
    imprimible = true;
    x += vel;
    cam_x += vel;
}

void Corredor_bmx::pintar(QPainter& painter)
{
    if (!imprimible){

        return;
    }

    painter.setBrush(Qt::green);

    painter.setPen(Qt::NoPen);

    painter.drawRect(x - cam_x, y, 10, 15);
}

void Corredor_bmx::caer(){
    if (volando) {

        vel_y += gravedad;

        y += vel_y;

        if (y >= piso) {

            y = piso;

            vel_y = 0;

            volando = false;
        }
    }
}

void Corredor_bmx::saltar(){

    if(!volando){

        vel_y = -salto;

        volando = true;
    }
}

void Corredor_bmx::intobj(short act, float x_){
    switch(act){
    case 1: // cohete — aumenta la fuerza del salto temporalmente
        salto += 6;
        break;
    default:
        break;
    }
}

void Corredor_bmx::acelerar(bool der, bool iz){
    if(!der && !iz){

        vel = vel * 0.987;
    }
    else if(der && !iz){
        vel = vel * 1.2;
        if(vel > velmax){

            vel = velmax;
        }
        else if(vel == 0){

            vel = 0.5;
        }
    }
    else if(!der && iz && !volando){
        vel = vel * 0.9;
        if(vel < 0.5) vel = 0;
    }
}

void Corredor_bmx::estavolando(bool colision){
    if(!colision && y < piso){

        volando = true;
    }
    else if(colision) {

        volando = false;
    }
}

void Corredor_bmx::bloquear(short frames){ //penalizacion por fallar truco
    f_bloq = frames;
}

void Corredor_bmx::setvelmax(float nueva)//sera para cambiar velocidad del power up
{
    velmax = nueva;
}
float Corredor_bmx::getcam_x()
{
    return cam_x;
}
float Corredor_bmx::getX()
{
    return x;
}
float Corredor_bmx::getY()
{
    return y;
}
