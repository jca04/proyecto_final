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
    explicit Player(QGraphicsScene* scene = nullptr);

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

    //movimiento
    short actualSprite;
    short directionWalk;


    void fallMotion();
    void walkingPlayer();
    void attack();

protected:
    void keyPressEvent(QKeyEvent* event) override;     // Método para manejar el evento de la tecla
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;        // Método para dibujar el jugador (renderizarlo en la escena)
    QRectF boundingRect() const override;     // Método para definir el área interactiva del jugador

};

#endif // PLAYER_H
