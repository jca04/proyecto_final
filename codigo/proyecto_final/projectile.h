#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QPainter>
#include <QBrush>
#include <cmath>
#include <QObject>

class Projectile: public QObject
{
    Q_OBJECT
public:
    Projectile(qreal V0_, qreal angle_, qreal g_, qreal time_, qreal dx, qreal dy, QGraphicsScene* scene_);
    void drawProjectile();

protected:

private:
    qreal v0;
    qreal angle;
    qreal g;
    qreal time;
    qreal dy;
    qreal dx;
    QGraphicsScene* scene;

    QTimer* timer;

    QGraphicsEllipseItem* sllipe = nullptr;

private slots:
    void updatePosition();

};

#endif // PROJECTILE_H
