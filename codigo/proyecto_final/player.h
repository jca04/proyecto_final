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

private:
    QGraphicsScene* scene;
    QTimer* animationTimer;
    QTimer* fall;
    int idTimer;

    void fallMotion();

private slots:
     void updateAnimation();

protected:
    void keyPressEvent(QKeyEvent* event) override;     // Método para manejar el evento de la tecla
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;        // Método para dibujar el jugador (renderizarlo en la escena)
    QRectF boundingRect() const override;     // Método para definir el área interactiva del jugador

};

#endif // PLAYER_H
