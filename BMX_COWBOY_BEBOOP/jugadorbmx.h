#ifndef JUGADORBMX_H
#define JUGADORBMX_H
#include "corredor_bmx.h"
#include "truco.h"

class JugadorBMX : public Corredor_bmx
{
private:
    Truco  catalogo[3];
    int    indice;
    int    truco_activo;
    bool   en_truco;
    int    n_nitros;
    int    puntaje;

public:
    JugadorBMX();

    void iniciarTruco();
    void hacerprueba(Qt::Key tecla);
    bool n_aciertos();
    void sumarpuntos();
    void secuencia();

    void activarNitro();

    int  getPuntaje()  const;
    int  getNitros()   const;
    int  getTrucoActivo() const;
    int  getIndice()   const;
    bool estaEnTruco() const;
};

#endif // JUGADORBMX_H
