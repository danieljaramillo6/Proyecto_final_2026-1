#ifndef TRUCO_H
#define TRUCO_H
#include <QString>
#include <Qt>

struct Truco
{
    QString    nombre;
    Qt::Key    secuencia[4];
    int        longitud;
    int        puntos;
    Truco() : longitud(0), puntos(0) {}
};
#endif // TRUCO_H
