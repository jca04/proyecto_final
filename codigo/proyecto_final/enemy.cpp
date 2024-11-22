#include "enemy.h"

Enemy::Enemy(QGraphicsScene *scene_, QString typeEnemy_) : scene(scene_)  ,typeEnemy(typeEnemy_)  {




}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->fillRect(boundingRect(), Qt::transparent);
    painter->drawRect(10, 10, 10 ,10);
}

QRectF Enemy::boundingRect() const {
    return QRectF(
        0,
        0,
        10, 10
        );
}

Enemy::~Enemy(){

}
