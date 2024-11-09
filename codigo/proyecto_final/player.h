#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QGraphicsItem>
#include <QPainter>
#include <QTimer>

class Player : public Character
{
    Q_OBJECT
public:
    explicit Player(QGraphicsScene* scene = nullptr);

private:
    QGraphicsScene* scene;
    QTimer* animationTimer;

private slots:
     void updateAnimation();

protected:
    // Método para manejar el evento de la tecla
    void keyPressEvent(QKeyEvent* event) override;

    // Método para dibujar el jugador (renderizarlo en la escena)
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // Método para definir el área interactiva del jugador
    QRectF boundingRect() const override ;


};

#endif // PLAYER_H
