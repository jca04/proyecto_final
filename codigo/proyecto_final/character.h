#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include "physics.h"
#include "projectile.h"

class Character :  public QObject, public Physics, public QGraphicsItem
{
    Q_OBJECT

public:
    Character();
    std::vector<Projectile>VProjectiles;

protected:
    int heal;
    qreal speed;
    QPointF position;

    // void move();
    // void attack();
    bool isCollidengWall(QGraphicsScene* scene, QRectF object, short direction);
    void launchProyectile(QGraphicsScene* scene, qreal dx, qreal dy);
    void keyPressEvent(QKeyEvent* event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;

};

#endif // CHARACTER_H
