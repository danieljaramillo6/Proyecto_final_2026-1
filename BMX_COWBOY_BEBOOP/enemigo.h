// enemigo.h
#ifndef ENEMIGO_H
#define ENEMIGO_H
#include "corredor.h"
#include "obstaculo.h"

class Enemigo : public Corredor {
private:
    float q_table[16][3];
    int estado_actual;
    int accion_actual;
    float learning_rate;
    float epsilon;
    float tope_q;
    short f_carril;
    short f_colision;
    struct EstadoVision {
        bool obstaculo_carril[6];
    };

    EstadoVision verAdelante(Obstaculo** obstaculos, int n_obs);
    int visionAEstado(EstadoVision v);
    int elegirAccion();
    void actualizarQ(float recompensa);

public:
    Enemigo();
    Enemigo(float x, float y, int dificultad);
    void actualizar(short colision, Obstaculo** obstaculos, int n_obs);
    void aprender(short colision);
    int getAncho() const { return 160; }
    int getAlto()  const { return 160; }
    void setcam_x(float c);
};

#endif // ENEMIGO_H
