#ifndef BMX_H
#define BMX_H

#include <QWidget>
#include <QTimer>
#include <QPainter>
#include "jugadorbmx.h"
#include "rampa_bmx.h"

namespace Ui {
class BMX;
}

class BMX : public QWidget
{
    Q_OBJECT
signals:
    void volver();
protected:
    void keyPressEvent(QKeyEvent* event)   override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void paintEvent(QPaintEvent* event)    override;
public:
    explicit BMX(QWidget *parent = nullptr);
    ~BMX();
    void agregarram(float x, float y);
    void dibujarPista(QPainter& painter);
    void dibujarHUD(QPainter& painter);
    void dibujarQTE(QPainter& painter);
    void dibujarMeta(QPainter& painter);
    void dibujarFin(QPainter& painter);
private slots:
    void on_pushButton_clicked();
    void onTimer();
    void onSegundo();
private:
    Rampa_bmx*  rampas[50];
    QTimer*     timer;
    QTimer*     timer_seg;
    JugadorBMX  jug;
    bool  tecla_izq;
    bool  tecla_der;
    short n_rampas;
    int   segundos;
    bool  juego_activo;
    Ui::BMX *ui;
};

#endif // BMX_H
