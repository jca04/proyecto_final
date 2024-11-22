#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QGraphicsItem>
#include <QPainter>
#include <QTimer>

class Player : public Character
{
    Q_OBJECT
public:
    Player(QGraphicsScene* scene = nullptr, float x = 0.0, float y = 0.0);

    void setPositonPlayer(QPointF position);

    ~Player();

private:
    QGraphicsScene* scene;
    QTimer* walksTimeOut;
    QTimer* figthTimeOut;
    QTimer* fall;

    QVector<QPixmap> walksRigth;
    QVector<QPixmap> walksLeft;
    QVector<QPixmap> fightRigth;
    QVector<QPixmap> fightLeft;
    QVector<QPixmap> jumpingRigth;
    QVector<QPixmap> jumpingLeft;

    //movimiento
    short actualSprite;
    short directionWalk;
    bool isJumping;

    float xPlayer;
    float yPlayer;

    void fallMotion();
    void walkingPlayer();
    void attack();

protected:
    void keyPressEvent(QKeyEvent* event) override;     // Método para manejar el evento de la tecla
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;        // Método para dibujar el jugador (renderizarlo en la escena)
    QRectF boundingRect() const override;     // Método para definir el área interactiva del jugador

};

#endif // PLAYER_H
