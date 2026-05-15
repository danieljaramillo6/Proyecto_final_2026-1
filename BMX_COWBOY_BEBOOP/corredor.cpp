#include "corredor.h"
#include <QPainter>

Corredor::Corredor() {
    x=3.0;
    y=300.0;
    vel=0;
    velmax=5;
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
    painter.setBrush(Qt::gray);
    painter.setPen(Qt::NoPen);
    painter.drawRect(x, y, 10, 15);
}
void Corredor::acelerar(bool der,bool iz){
    if (!der && !iz) vel=vel*0.9;
    else if (der && !iz){
        vel=vel*1.2;
        if (vel>velmax)vel=velmax;
        else if(vel == 0)vel=0.5;
    }
    else if(!der && iz) {
        vel= vel*0.5;
        if(vel < 0.5) vel = 0;
    }
    return;
}

void Corredor::mover(){
    x+=vel;
}
