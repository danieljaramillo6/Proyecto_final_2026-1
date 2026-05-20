#ifndef OBSTACULO_H
#define OBSTACULO_H
#include <QPainter>
#include <QPixmap>
class Obstaculo
{
protected:
    float x,y;
    int ancho,alto;
    bool vivo;
    QPixmap sprite;
public:
    Obstaculo();
    Obstaculo(float x, float y, int ancho, int alto, bool vivo = true);
    bool estavivo();
    void matar();
    virtual void dibujar(QPainter& painter,float cam_x);
    virtual short colisiona(float x,float y,int pancho,int palto);
    float getX();
    int getancho();
};

#endif // OBSTACULO_H
