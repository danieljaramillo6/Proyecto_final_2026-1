#include "jugadorbmx.h"
#include <QRandomGenerator>

JugadorBMX::JugadorBMX()
{
    catalogo[0].nombre   = "SPIKE";
    catalogo[0].secuencia[0] = Qt::Key_H;
    catalogo[0].secuencia[1] = Qt::Key_J;
    catalogo[0].longitud = 2;
    catalogo[0].puntos   = 100;

    catalogo[1].nombre   = "BEBOP";
    catalogo[1].secuencia[0] = Qt::Key_H;
    catalogo[1].secuencia[1] = Qt::Key_J;
    catalogo[1].secuencia[2] = Qt::Key_K;
    catalogo[1].longitud = 3;
    catalogo[1].puntos   = 200;

    catalogo[2].nombre   = "SPACE COWBOY";
    catalogo[2].secuencia[0] = Qt::Key_H;
    catalogo[2].secuencia[1] = Qt::Key_J;
    catalogo[2].secuencia[2] = Qt::Key_K;
    catalogo[2].secuencia[3] = Qt::Key_L;
    catalogo[2].longitud = 4;
    catalogo[2].puntos   = 400;

    indice       = 0;
    truco_activo = 0;
    en_truco     = false;
    n_nitros     = 0;
    puntaje      = 0;
}

void JugadorBMX::iniciarTruco()
{
    if(en_truco) return;
    truco_activo = QRandomGenerator::global()->bounded(3);
    indice       = 0;
    en_truco     = true;
}

void JugadorBMX::hacerprueba(Qt::Key tecla)
{
    if(!en_truco) return;

    if(tecla == catalogo[truco_activo].secuencia[indice]){
        indice++;
        if(indice >= catalogo[truco_activo].longitud){
            sumarpuntos();
            n_nitros++;
            en_truco = false;
            indice   = 0;
        }
    } else {
        en_truco = false;
        indice   = 0;
        bloquear(30);
    }
}

bool JugadorBMX::n_aciertos()
{
    return indice > 0;
}

void JugadorBMX::sumarpuntos()
{
    puntaje += catalogo[truco_activo].puntos;
}

void JugadorBMX::secuencia()
{
}

void JugadorBMX::activarNitro()
{
    if(n_nitros > 0){
        n_nitros--;
        setSalto(getSalto() + 6);
    }
}

int  JugadorBMX::getPuntaje()      const { return puntaje;      }
int  JugadorBMX::getNitros()       const { return n_nitros;     }
int  JugadorBMX::getTrucoActivo()  const { return truco_activo; }
int  JugadorBMX::getIndice()       const { return indice;       }
bool JugadorBMX::estaEnTruco()     const { return en_truco;     }
