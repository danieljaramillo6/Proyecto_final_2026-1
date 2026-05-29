#include "enemigo.h"
#include <cstdlib>

Enemigo::Enemigo() : Corredor() {
    learning_rate = 0.1f;
    epsilon       = 0.3f;
    tope_q        = 5.0f;
    estado_actual = 0;
    accion_actual = 0;
    for(int i = 0; i < 16; i++)
        for(int j = 0; j < 3; j++)
            q_table[i][j] = 0.0f;
}

Enemigo::Enemigo(float x, float y, int dificultad) : Corredor() {
    this->x   = x;
    this->y   = y;
    estado_actual = 0;
    accion_actual = 0;
    learning_rate = 0.1f;

    switch(dificultad){
    case 1:
        epsilon = 0.5f;
        tope_q  = 2.0f;
        break;
    case 2:
        epsilon = 0.3f;
        tope_q  = 5.0f;
        break;
    case 3:
        epsilon = 0.1f;
        tope_q  = 10.0f;
        break;
    default:
        epsilon = 0.3f;
        tope_q  = 5.0f;
    }

    for(int i = 0; i < 16; i++)
        for(int j = 0; j < 3; j++)
            q_table[i][j] = 0.0f;

    f_carril=0;
    f_colision=0;
    vel=5.0;
}

Enemigo::EstadoVision Enemigo::verAdelante(Obstaculo** obstaculos, int n_obs){
    EstadoVision vision;
    float rango = 600.0f;

    for(int i = 0; i < 6; i++) vision.obstaculo_carril[i] = false;

    for(int i = 0; i < n_obs; i++){
        if(!obstaculos[i]->estavivo()) continue;

        float ox = obstaculos[i]->getX();
        float oy = obstaculos[i]->getY() + obstaculos[i]->getAlto()/2;

        if(ox > x && ox < x + rango){
            int carril = (int)oy / 120;
            if(carril >= 1 && carril <= 4)
                vision.obstaculo_carril[carril] = true;
        }
    }
    return vision;
}

int Enemigo::visionAEstado(EstadoVision v){
    int estado = 0;
    for(int i = 1; i <= 4; i++){
        if(v.obstaculo_carril[i])
            estado |= (1 << (i - 1));
    }
    return estado;
}

int Enemigo::elegirAccion(){
    if((rand() % 100) < epsilon * 100){
        return rand() % 3;
    }

    int mejor = 0;
    for(int a = 1; a < 3; a++){
        if(q_table[estado_actual][a] > q_table[estado_actual][mejor])
            mejor = a;
    }
    return mejor;
}

void Enemigo::actualizarQ(float recompensa){
    int estado = visionAEstado(verAdelante(nullptr, 0));

    float mejor_futuro = q_table[estado][0];
    for(int a = 1; a < 3; a++)
        if(q_table[estado][a] > mejor_futuro)
            mejor_futuro = q_table[estado][a];

    float nuevo_q = q_table[estado_actual][accion_actual] +
                    learning_rate * (recompensa + 0.9f * mejor_futuro - q_table[estado_actual][accion_actual]);

    if(nuevo_q > tope_q)  nuevo_q = tope_q;
    if(nuevo_q < -tope_q) nuevo_q = -tope_q;

    q_table[estado_actual][accion_actual] = nuevo_q;
}

void Enemigo::aprender(short colision){
    float recompensa;
    if(colision != 0){
        recompensa = -10.0f;
    } else {
        recompensa = 1.0f;
    }
    actualizarQ(recompensa);
}

void Enemigo::actualizar(short colision, Obstaculo** obstaculos, int n_obs){
    EstadoVision vision = verAdelante(obstaculos, n_obs);
    estado_actual = visionAEstado(vision);
    accion_actual = elegirAccion();
}
    bool usar_nitro = false;
    if(nitro > 0){
        int carril_actual = (int)y / 120;
        bool obst_mi_carril = vision.obstaculo_carril[carril_actual];
        bool puedo_subir    = (y > 180) && !vision.obstaculo_carril[carril_actual - 1];
        bool puedo_bajar    = (y < 540) && !vision.obstaculo_carril[carril_actual + 1];

        if(obst_mi_carril && !puedo_subir && !puedo_bajar){
            usar_nitro = true;
        }
    }

    if(f_carril > 0){
        f_carril--;
    } else {
        switch(accion_actual){
        case 0: cambiarcarril(false, false); break;
        case 1: cambiarcarril(true,  false); f_carril = 30; break;
        case 2: cambiarcarril(false, true);  f_carril = 30; break;
        }
    }

    acelerar(true, false);
    mover(usar_nitro)}
    if(colision != 0) f_colision = 10;
    if(f_colision > 0) f_colision--;
    else if(vel < 5.0) vel = 5.0;

    aprender(colision);
    caer();
}

/*void Enemigo::pintar(QPainter& painter){

        if(!imprimible)return;
        if(termino){
            painter.drawPixmap(x-cam,y-z-120,160,160,sprite,0,0,128,128);
            return;
        }
        if(caido){
            painter.drawPixmap(x-cam,y-120,160,160,sprite_caido);
            return;
        }
        if(f_nitro>0){
            painter.drawPixmap(x-cam,y-z-120,160,160,sprite,0,128,128,128);
            return;
        }
        if(acelerando){
            if(n_sprite>3) n_sprite=0;
            painter.drawPixmap(x-cam, y-z-120, 160, 160,sprite,128*n_sprite,0,128,128);
            if(frame==8){
                n_sprite++;
                frame=0;
            }
            else frame++;
        }
        else painter.drawPixmap(x-cam, y-z-120, 160, 160,sprite,0,0,128,128);


*/

void Enemigo::setcam_x(float c){
    cam_x=c;
}
