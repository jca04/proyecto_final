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
    ~Character();
protected:
    int heal;
    bool isWalking;
    qreal speed;
    QPointF position;
    short indSpriteAttack;
    bool isFigthing;
    short isLaunchObject;

    QVector<QPixmap> walksRigth;
    QVector<QPixmap> walksLeft;
    QVector<QPixmap> fightRigth;
    QVector<QPixmap> fightLeft;
    QVector<QPixmap> jumpingRigth;
    QVector<QPixmap> jumpingLeft;
    QVector<QPixmap> launchObjects;


    // void move();
    void attack();
    bool isCollidengWall(QGraphicsScene* scene, QRectF object, short direction);
    void launchProyectile(QGraphicsScene* scene, qreal dx, qreal dy);
    void keyPressEvent(QKeyEvent* event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;

};

#endif // CHARACTER_H
