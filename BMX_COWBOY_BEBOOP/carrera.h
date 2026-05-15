#ifndef CARRERA_H
#define CARRERA_H

#include <QWidget>
#include <QTimer>
#include "corredor.h"
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


private slots:
    void on_pushButton_clicked();
    void onTimer();

private:
    QTimer* timer;
    Corredor jug;
    bool tecla_izq, tecla_der, tecla_up, tecla_dw;
    Ui::Carrera *ui;
};

#endif // CARRERA_H
