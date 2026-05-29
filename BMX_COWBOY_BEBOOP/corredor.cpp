#include "corredor.h"
#include <QPainter>
#include <QDebug>
Corredor::Corredor() {
    x=30;
    cam_x=0;
    y=300.0;
    vel=0;
    velmax=20;
    nitro=0;
    vel_z=10;
    cambiando_carril=false;
    z=0;
    volando=false;
    imprimible=true;
    f_bloq=0;
    f_nitro=0;
    act_nitro=false;
    caido=false;
    sprite=QPixmap(":/sprites/spikesheet.png");
    sprite_caido=QPixmap(":/sprites/spritecaido.png");
    if(sprite_caido.isNull()){
        qDebug() << "no cargo la imagen";
    }
    primero=true;
    acelerando=false;
    n_sprite=0;
    frame=0;
    termino=false;
}

void Corredor::cambiarcarril(bool up, bool dw){
    if (termino)return;
    if (f_bloq>0)return;
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
    if(termino){
        painter.drawPixmap(x-cam_x,y-z-120,160,160,sprite,0,0,128,128);
        return;
    }
    if(caido){
        painter.drawPixmap(x-cam_x,y-120,160,160,sprite_caido);
        return;
    }
    if(f_nitro>0){
        painter.drawPixmap(x-cam_x,y-z-120,160,160,sprite,0,128,128,128);
        return;
    }
    if(acelerando){
        if(n_sprite>3) n_sprite=0;
        painter.drawPixmap(x-cam_x, y-z-120, 160, 160,sprite,128*n_sprite,0,128,128);
        if(frame==8){
        n_sprite++;
        frame=0;
        }
        else frame++;
    }
    else painter.drawPixmap(x-cam_x, y-z-120, 160, 160,sprite,0,0,128,128);

}
void Corredor::acelerar(bool der,bool iz){
    if (!der && !iz){//inercia
        vel=vel*0.987;
        acelerando=false;
    }
    else if (der && !iz){//acelerar
        vel=vel*1.2;
        if (vel>velmax)vel=velmax;
        else if(vel == 0)vel=0.5;
        acelerando=true;
    }
    else if(!der && iz && !volando) {//frenar
        vel= vel*0.9;
        if(vel < 0.5) vel = 0;
        acelerando=false;
    }
    return;
}

void Corredor::intobj(short act,float x_){
    if(z>0)return;
    switch(act){
    case 1:
        if(vel>20)break;
        vel=0;
        break;
    case 2:
        velmax=2;
        if (vel>2)vel=2;
        break;
    case 3:
        vel=0;
        bloquear(30);
        caido=true;
        break;
    case 4:

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
    if (termino)return;
    if (f_bloq>0){
        f_nitro=0;
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
        velmax=35;
        f_nitro--;
    }else velmax=10;
    caido=false;
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

float Corredor::getZ(){
    return z;
}

void Corredor::final(){
    termino=true;
}

void Corredor::setPos(bool pos){
    primero=pos;
}

bool Corredor::getPos()const{
    return primero;
}
