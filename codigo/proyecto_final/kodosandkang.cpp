#include "kodosandkang.h"
#include "homero.h"
#include <cmath>
#include <QPointF>
#include <QPushButton>

KodosAndKang::KodosAndKang(QGraphicsScene* scene, Homero* homero)
    : vida(100), scene(scene), homero(homero), direccionY(1), tiempo(0) {


    kodosAndKangSprite = QPixmap(":/public/images/kang_and_kodos.png");

    if (kodosAndKangSprite.isNull()) {
        qDebug() << "No se pudo cargar el sprite de Kodos y Kang";
    }

    kodosAndKangSprite = kodosAndKangSprite.scaled(250, 250);

    setPixmap(kodosAndKangSprite);
    setPos(500, 10);

    barraVida = new QGraphicsRectItem(0, 0, 100, 10);
    barraVida->setBrush(Qt::green);
    barraVida->setPos(x(), y() - 15);
    scene->addItem(barraVida);

    //setRect(0, 0, 100, 50); // Representación inicial como un rectángulo
    //setBrush(Qt::green);
    //setPos(500, 100); // Posición inicial (flotando)

    // Configurar movimiento flotante
    movimientoTimer = new QTimer(this);
    connect(movimientoTimer, &QTimer::timeout, this, &KodosAndKang::mover);
    movimientoTimer->start(50); // Movimiento cada 50 ms

    // Configurar ataque
    ataqueTimer = new QTimer(this);
    connect(ataqueTimer, &QTimer::timeout, this, &KodosAndKang::lanzarLaser);
    ataqueTimer->start(1000); // Lanzar láser cada 1 segundos
}

void KodosAndKang::mover() {
    // Movimiento sinusoidal
    tiempo += 0.1;
    qreal nuevaY = 200 + 50 * sin(tiempo);
    setY(nuevaY);

    barraVida->setPos(x(), y() - 15);
}

void KodosAndKang::lanzarLaser() {

    QPointF posicionInicial = pos();
    QPointF posicionHomero = homero->pos();

    QGraphicsRectItem* laser = new QGraphicsRectItem();
    laser->setRect(0, 0, 20, 5);
    laser->setBrush(Qt::red);
    laser->setPos(posicionInicial.x(), posicionInicial.y() + boundingRect().height() / 2);
    scene->addItem(laser);

    qreal dx = posicionHomero.x() - posicionInicial.x();
    qreal dy = posicionHomero.y() - posicionInicial.y();
    qreal velocidadX = dx / 100.0;
    qreal velocidadY = dy / 100.0 - 0.05 * 100.0 / 2; // gravedad

    QTimer* laserTimer = new QTimer(this);
    connect(laserTimer, &QTimer::timeout, [=]() mutable {

        // Actualizar posicion del laser
        velocidadY += 0.05;
        laser->moveBy(velocidadX, velocidadY);

        if (homero->collidesWithItem(laser)) {
            homero->recibirDano(5);
            delete laser;
            laserTimer->stop();
            laserTimer->deleteLater();
        }
        // Verificar si el laser sale de los limites
        else if (!scene->sceneRect().contains(laser->pos())) {
            delete laser;
            laserTimer->stop();
            laserTimer->deleteLater();
        }
    });

    laserTimer->start(20);
}

void KodosAndKang::recibirDano(int cantidad) {

    if (vida <= 0) return;

    vida -= cantidad;
    if (vida <= 0) {
        qDebug() << "KodosAndKang han sido derrotados!";

        // Detener los temporizadores antes de eliminar los objetos
        movimientoTimer->stop();
        ataqueTimer->stop();

        // Eliminar barra de vida de la escena
        scene->removeItem(barraVida);
        delete barraVida;
        barraVida = nullptr; // Asegúrate de no usar un puntero colgado

        // Eliminar este objeto (KodosAndKang) de la escena
        scene->removeItem(this);
        //delete this; // Eliminar el objeto completamente

        emit derrotado(true, scene);
    }
    actualizarBarraVida();
}

void KodosAndKang::actualizarBarraVida() {
    if (barraVida) {
        qreal nuevoAncho = (vida / 100.0) * 100;
        barraVida->setRect(0, 0, nuevoAncho, 10);

        if (vida > 50) {
            barraVida->setBrush(Qt::green);
        } else  if (vida > 25) {
            barraVida->setBrush(Qt::yellow);
        } else {
            barraVida->setBrush(Qt::red);
        }
    }
}
