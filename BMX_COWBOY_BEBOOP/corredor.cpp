#include "corredor.h"
#include <QPainter>
#include <QDebug>
Corredor::Corredor() {
    x=30;
    cam_x=0;
    y=300.0;
    vel=0;
    velmax=10;
    nitro=0;
    vel_z=10;
    cambiando_carril=false;
    z=0;
    volando=false;
    imprimible=true;
    f_bloq=0;
    act_nitro=false;
}

void Corredor::cambiarcarril(bool up, bool dw){
    if(up && !dw && !cambiando_carril && z==0){
        if(y > 180){
            y -= 120;
            cambiando_carril = true;
        }
    }
    else if(!up && dw && !cambiando_carril && z==0){
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
    painter.setBrush(Qt::green);
    painter.setPen(Qt::NoPen);
    painter.drawRect(x-cam_x, y-z, 10, 15);
    qDebug()<<nitro;
}
void Corredor::acelerar(bool der,bool iz){
    if (!der && !iz) vel=vel*0.987;
    else if (der && !iz){
        vel=vel*1.2;
        if (vel>velmax)vel=velmax;
        else if(vel == 0)vel=0.5;
    }
    else if(!der && iz && !volando) {
        vel= vel*0.9;
        if(vel < 0.5) vel = 0;
    }
    return;
}

void Corredor::intobj(short act,float x_){
    switch(act){
    case 1:
        if(vel>10)break;
        vel=0;
        break;
    case 2:
        velmax=2;
        if (vel>2)vel=2;
        break;
    case 3:
        vel=0;
        bloquear(30);
        break;
    case 4:
        if(z>0)break;
        vel=0;
        x=x_;
        bloquear(60);
        imprimible=false;
        break;
    case 5:
        if (nitro<3){
        nitro++;
        }

        break;
    default:
        break;
    }
}

void Corredor::bloquear(short frames){
    f_bloq=frames;
}


void Corredor::mover(bool espacio){
    if (f_bloq>0){
        f_bloq--;
        return;
    }
    if (f_nitro==0)act_nitro=false;
    if (espacio && nitro>0 && !act_nitro){
        vel+=20;
        nitro--;
        f_nitro=30;
        act_nitro=true;
    }
    if (f_nitro>0){
        velmax=20;
        f_nitro--;
    }else velmax=10;

    imprimible=true;
    x+=vel;
    cam_x+=vel;
}

void Corredor::caer(){
    if (volando){
    vel_z-=0.9;
    z+=vel_z;
    if (z<=0){
        z=0;
        vel_z=10;
        volando=false;
    }
    }
    return;
}

void Corredor::estavolando(bool colision){
    if(!colision && z>0){
        volando=true;
        return;
    }
    else if(colision) volando =false;
    return;
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

void Corredor::setZ(float new_z){
    z=new_z;
    return;
}

int Corredor::getnitro(){
    return nitro;
}
