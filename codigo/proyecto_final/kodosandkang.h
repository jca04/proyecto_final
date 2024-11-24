#ifndef KODOSANDKANG_H
#define KODOSANDKANG_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QObject>
#include <QPixmap>
#include "homero.h"
#include <QGraphicsPixmapItem>

class Homero;

class KodosAndKang : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    KodosAndKang(QGraphicsScene* scene, Homero* homero);
    void recibirDano(int cantidad);
    void lanzarLaser();

private slots:
    void mover();

private:
    int vida;
    QTimer* movimientoTimer;
    QTimer* ataqueTimer;
    QGraphicsScene* scene;
    Homero* homero;
    int direccionY;
    double tiempo;
    QPixmap kodosAndKangSprite;
    QPixmap happyHomero;
};

#endif // KODOSANDKANG_H
