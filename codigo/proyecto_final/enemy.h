#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"
#include <QGraphicsScene>

class Enemy : public Character
{
    Q_OBJECT
public:
    Enemy(QGraphicsScene* scene_, QString typeEnemy_);

    ~Enemy();

private:
    QGraphicsScene* scene;
    QString typeEnemy;


protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;        // Método para dibujar el jugador (renderizarlo en la escena)
    QRectF boundingRect() const override;     // Método para definir el área interactiva del jugador
};

#endif // ENEMY_H
