#ifndef CARRERA_H
#define CARRERA_H

#include <QWidget>
#include <QTimer>
#include "corredor.h"
#include <QVector>
#include "obstaculo.h"
#include "barrera.h"
#include "bache.h"
#include "Acantilado.h"
#include "aceite.h"
#include "nitro.h"
#include "rampa.h"

namespace Ui {
class Carrera;
}

class Carrera : public QWidget
{
    Q_OBJECT
signals:
    void volver();
protected:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

public:
    explicit Carrera(QWidget *parent = nullptr);
    ~Carrera();
    void agregarobs(short tipo,float x,float y);
    void agregarram(float x, float y);

private slots:
    void on_pushButton_clicked();
    void onTimer();

private:
    Obstaculo* obstaculos[100];
    Rampa* rampas[50];
    QTimer* timer;
    Corredor jug;
    bool tecla_izq, tecla_der, tecla_up, tecla_dw,nitro;
    Ui::Carrera *ui;
    short n_obstaculos;
    short n_rampas;
};

#endif // CARRERA_H
