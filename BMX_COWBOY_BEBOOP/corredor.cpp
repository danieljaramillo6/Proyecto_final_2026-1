#include "corredor.h"
#include <QPainter>
#include <QDebug>
Corredor::Corredor() {
    x=30;
    cam_x=0;
    y=300.0;
    vel=0;
    velmax=10;
    nitro=true;
    cambiando_carril=false;
}

void Corredor::cambiarcarril(bool up, bool dw){
    if(up && !dw && !cambiando_carril){
        if(y > 180){
            y -= 120;
            cambiando_carril = true;
        }
    }
    else if(!up && dw && !cambiando_carril){
        if(y < 540){
            y += 120;
            cambiando_carril = true;
        }
    }

    if(!up && !dw){
        cambiando_carril = false;
    }
}

void Corredor::pintar(QPainter &painter){
    if(!imprimible)return;
    painter.setBrush(Qt::gray);
    painter.setPen(Qt::NoPen);
    painter.drawRect(x-cam_x, y, 10, 15);
}
void Corredor::acelerar(bool der,bool iz){
    if (!der && !iz) vel=vel*0.987;
    else if (der && !iz){
        vel=vel*1.2;
        if (vel>velmax)vel=velmax;
        else if(vel == 0)vel=0.5;
    }
    else if(!der && iz) {
        vel= vel*0.9;
        if(vel < 0.5) vel = 0;
    }
    return;
}

void Corredor::intobj(short act,float x_){
    switch(act){
    case 1:
        vel=0;
        break;
    case 2:
        velmax=2;
        if (vel>2)vel=2;
        break;
    case 3:
        vel=0;
        bloquear(30);
    case 4:
        vel=0;
        x=x_;
        bloquear(60);
        imprimible=false;
    default:
        break;
    }
}

void Corredor::bloquear(short frames){
    f_bloq=frames;
}
void Corredor::mover(){
    if (f_bloq>0){
        f_bloq--;
        return;
    }
    imprimible=true;
    x+=vel;
    cam_x+=vel;
}

float Corredor::getcam_x(){
    return cam_x;
}

float Corredor::getX(){
    return x;
}

float Corredor::getY(){
    return y;
}

void Corredor::setvelmax(double nueva){
    velmax=nueva;
    return;
}
