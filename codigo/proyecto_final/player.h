#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QGraphicsItem>
#include <QPainter>
#include <QTimer>

class Enemy;

class Player : public Character
{
    Q_OBJECT
public:
    Player(QGraphicsScene* scene = nullptr, float x = 0.0, float y = 0.0, QVector<Enemy*> enemies = {});

    void setPositonPlayer(QPointF position);

    ~Player();

private:
    QGraphicsScene* scene;
    QGraphicsPixmapItem* objectLaunch;
    QTimer* walksTimeOut;
    QTimer* figthTimeOut;
    QTimer* fall;
    QTimer* launchTimer;
    QVector<Enemy*> enemies;

    //movimiento
    short actualSprite;
    short directionWalk;
    bool isJumping;

    float xPlayer;
    float yPlayer;


    void fallMotion();
    void walkingPlayer();
    void attack();
    void launchObject();
    void moveLaunchObject();


protected:
    void keyPressEvent(QKeyEvent* event) override;     // Método para manejar el evento de la tecla
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;        // Método para dibujar el jugador (renderizarlo en la escena)
    QRectF boundingRect() const override;     // Método para definir el área interactiva del jugador

};

#endif // PLAYER_H
