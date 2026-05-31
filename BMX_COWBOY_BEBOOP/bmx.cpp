#include "bmx.h"
#include "ui_bmx.h"
#include <QKeyEvent>
#include <QPainter>

BMX::BMX(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BMX)
{
    ui->setupUi(this);
    setFixedSize(1200, 720);

    n_rampas     = 0;
    segundos     = 0;
    juego_activo = true;
    tecla_der    = false;
    tecla_izq    = false;

    for(int i = 1; i <= 50; i++)
        agregarram(i * 2000, 520);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &BMX::onTimer);
    timer->start(16);

    timer_seg = new QTimer(this);
    connect(timer_seg, &QTimer::timeout, this, &BMX::onSegundo);
    timer_seg->start(1000);
}

BMX::~BMX()
{
    for(int i = 0; i < n_rampas; i++) delete rampas[i];
    delete ui;
}

void BMX::onSegundo()
{
    if(juego_activo) segundos++;
}

void BMX::onTimer()
{
    if(!juego_activo) return;

    if(jug.getX() >= 100000){
        juego_activo = false;
        timer->stop();
        timer_seg->stop();
        update();
        return;
    }

    jug.acelerar(tecla_der, tecla_izq);

    bool enrampa = false;
    for(int i = 0; i < n_rampas; i++){
        if(rampas[i]->arriba_rampa(jug.getX(), jug.getY(), 10, 15)){
            rampas[i]->actz(jug);
            if(!jug.estaEnTruco())
                jug.iniciarTruco();
            enrampa = true;
            break;
        }
    }

    if(!enrampa) jug.estavolando(false);

    jug.caer();
    jug.mover();
    update();
}

void BMX::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    dibujarPista(painter);

    for(int i = 0; i < n_rampas; i++)
        rampas[i]->dibujar(painter, jug.getcam_x());

    // Meta visual al final
    dibujarMeta(painter);

    jug.pintar(painter);
    dibujarHUD(painter);

    if(jug.estaEnTruco())
        dibujarQTE(painter);

    if(!juego_activo)
        dibujarFin(painter);
}

void BMX::keyPressEvent(QKeyEvent* event)
{
    if(!juego_activo) return;

    Qt::Key k = static_cast<Qt::Key>(event->key());

    if(jug.estaEnTruco()){
        jug.hacerprueba(k);
        return;
    }

    if(k == Qt::Key_A)     tecla_izq = true;
    if(k == Qt::Key_D)     tecla_der = true;
    if(k == Qt::Key_Space) jug.activarNitro();
}

void BMX::keyReleaseEvent(QKeyEvent* event)
{
    Qt::Key k = static_cast<Qt::Key>(event->key());
    if(k == Qt::Key_A) tecla_izq = false;
    if(k == Qt::Key_D) tecla_der = false;

}

void BMX::agregarram(float x, float y)
{
    if(n_rampas >= 50) return;
    rampas[n_rampas++] = new Rampa_bmx(x, y);
}

void BMX::dibujarPista(QPainter& painter)
{
    // Fondo espacial
    painter.fillRect(0, 0, width(), height(), Qt::black);

    // Estrellas
    painter.setPen(Qt::white);
    int estrellas[][2] = {
        {100,50},{200,30},{350,80},{500,20},{650,60},
        {800,40},{950,70},{1100,25},{150,150},{400,120},
        {700,100},{900,140},{1050,90},{300,200},{600,180}
    };
    for(auto& e : estrellas){
        int sx = (e[0] - (int)jug.getcam_x() % 1200 + 1200) % 1200;
        painter.drawPoint(sx, e[1]);
    }

    // Piso metalico
    painter.fillRect(0, 620, width(), 100, QColor(80, 80, 80));
    painter.setPen(QColor(120, 120, 120));
    painter.drawLine(0, 620, width(), 620);
}

void BMX::dibujarHUD(QPainter& painter)
{
    // Fondo HUD
    painter.fillRect(0, 0, width(), 45, QColor(0, 0, 0, 180));

    QFont f("Arial", 14, QFont::Bold);
    painter.setFont(f);

    // Puntaje
    painter.setPen(QColor(80, 220, 255));
    painter.drawText(20, 30, "PUNTOS: " + QString::number(jug.getPuntaje()));

    // Tiempo
    painter.setPen(Qt::white);
    int min = segundos / 60;
    int seg = segundos % 60;
    painter.drawText(450, 30, QString("TIEMPO: %1:%2")
                                  .arg(min, 2, 10, QChar('0'))
                                  .arg(seg, 2, 10, QChar('0')));

    // Nitros — igual que nivel 1
    painter.setPen(QColor(255, 200, 0));
    painter.drawText(900, 30, "NITROS: " + QString::number(jug.getNitros()));
}

void BMX::dibujarQTE(QPainter& painter)
{
    // Nombre del truco
    QFont fNombre("Arial", 18, QFont::Bold);
    painter.setFont(fNombre);
    painter.setPen(QColor(255, 220, 0));

    // Obtener nombre del truco activo via indice
    QString nombres[3] = {"SPIKE", "BEBOP", "SPACE COWBOY"};
    int     longitudes[3] = {2, 3, 4};
    QString teclas[3][4] = {
        {"H","J","",""},
        {"H","J","K",""},
        {"H","J","K","L"}
    };

    int t = jug.getTrucoActivo();
    painter.drawText(QRect(0, 55, width(), 30), Qt::AlignCenter, nombres[t]);

    // Cajas de teclas
    QFont fKey("Arial", 18, QFont::Bold);
    painter.setFont(fKey);

    int n      = longitudes[t];
    int boxW   = 50;
    int gap    = 10;
    int totalW = n * boxW + (n - 1) * gap;
    int startX = (width() - totalW) / 2;
    int startY = 90;

    for(int i = 0; i < n; i++){
        int bx = startX + i * (boxW + gap);
        QColor bg = (i < jug.getIndice()) ? QColor(40, 160, 70) :
                        (i == jug.getIndice()) ? QColor(255, 200, 0) :
                        QColor(50, 50, 70);
        painter.setBrush(bg);
        painter.setPen(Qt::white);
        painter.drawRoundedRect(bx, startY, boxW, boxW, 6, 6);
        painter.setPen(i < jug.getIndice() ? Qt::white : QColor(20,20,20));
        painter.drawText(QRect(bx, startY, boxW, boxW), Qt::AlignCenter, teclas[t][i]);
    }
}

void BMX::dibujarMeta(QPainter& painter)
{
    float metaX = 100000 - jug.getcam_x();
    if(metaX > width() || metaX < -200) return;

    painter.setBrush(QColor(255, 215, 0));
    painter.setPen(Qt::NoPen);
    painter.drawRect(metaX, 480, 20, 140);

    QFont f("Arial", 10, QFont::Bold);
    painter.setFont(f);
    painter.setPen(Qt::black);
    painter.drawText(metaX - 10, 475, "META");
}

void BMX::dibujarFin(QPainter& painter)
{
    painter.fillRect(0, 0, width(), height(), QColor(0, 0, 0, 200));

    QFont fBig("Arial", 36, QFont::Bold);
    painter.setFont(fBig);
    painter.setPen(QColor(255, 215, 0));
    painter.drawText(QRect(0, 150, width(), 80), Qt::AlignCenter, "NIVEL COMPLETADO");

    QFont fMed("Arial", 22, QFont::Bold);
    painter.setFont(fMed);
    painter.setPen(Qt::white);

    int min = segundos / 60;
    int seg = segundos % 60;

    painter.drawText(QRect(0, 270, width(), 50), Qt::AlignCenter,
                     "PUNTOS: " + QString::number(jug.getPuntaje()));
    painter.drawText(QRect(0, 330, width(), 50), Qt::AlignCenter,
                     QString("TIEMPO: %1:%2").arg(min,2,10,QChar('0')).arg(seg,2,10,QChar('0')));
    painter.drawText(QRect(0, 390, width(), 50), Qt::AlignCenter,
                     "NITROS RESTANTES: " + QString::number(jug.getNitros()));
}

void BMX::on_pushButton_clicked()
{
    emit volver();
}
