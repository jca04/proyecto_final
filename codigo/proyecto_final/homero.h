#ifndef HOMERO_H
#define HOMERO_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QBrush>
#include <QKeyEvent>
#include <QVector>
#include <QPixmap>
#include <QTimer>
#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsScene>

#include "kodosandkang.h"

class KodosAndKang;

class Homero : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Homero(QGraphicsScene* scene);
    void lanzarObjeto();
    void recibirDano(int cantidad);
    void setWalls(const QVector<QGraphicsRectItem*>& walls);
    void setEnemigo(KodosAndKang* enemigo);
    void exitMenu();

private:
    int vida;
    QVector<QGraphicsRectItem*> walls;  // Lista de paredes

    QTimer* animationTimer;  // Timer para la animación

    QVector<QPixmap> walksRight;
    QVector<QPixmap> walksLeft;
    QVector<QPixmap> fightRight;
    QVector<QPixmap> fightLeft;
    QPixmap homeroDead;
    QPixmap donutSprite;
    QGraphicsScene* scene;
    QGraphicsRectItem* barraVida;

    short actualSprite;
    short walkDirection;
    bool isWalking;
    bool isAttacking;
    int life;
    int speed;
    KodosAndKang* enemigo;

    void updateAnimation();
    void keyReleaseEvent(QKeyEvent* event);
    bool checkWallCollision(int dx, int dy);
    void atacarKodosAndKang(KodosAndKang* enemigo);
    void deadMenu();
    void restartGame();
    void actualizarBarraVida();

signals:
    void returnToMainMenu();


protected:
    void keyPressEvent(QKeyEvent* event) override;
};

#endif // HOMERO_H
