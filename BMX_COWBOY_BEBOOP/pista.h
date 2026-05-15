#ifndef PISTA_H
#define PISTA_H
#include <QVector>
#include <QList>
#include "corredor.h"
class Pista
{
private:
   // vector<obstaculo> obstaculos;
    QList<Corredor> corredores;
public:
    Pista();
};

#endif // PISTA_H
