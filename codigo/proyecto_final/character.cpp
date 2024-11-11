#include "character.h"

Character::Character() {}

//metodo para heredar
void Character::launchProyectile(QGraphicsScene* scene, qreal dx, qreal dy){

    if (!projectile){
        projectile = new Projectile(0.15, 20, 10, 0, dx, dy, scene);
        projectile->drawProjectile();
    }else{
        projectile->drawProjectile();
    }
}

void Character::keyPressEvent(QKeyEvent* event){}
void Character::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){}
QRectF Character::boundingRect() const {}

bool Character::isCollidengWall(QGraphicsScene *scene, QRectF object, short direction){
    QGraphicsRectItem tempRectItem(object);
    QList<QGraphicsItem*> items = scene->items();

    if (items.isEmpty()) return false;

    for (QGraphicsItem* item : items){

        if (item == &tempRectItem) continue;

        if (item->data(0).toString() == "wall"){
            if (tempRectItem.collidesWithItem(item)) {
                QRectF itemRect = item->mapToScene(item->boundingRect()).boundingRect();

                switch (direction) {
                case 1:
                    if (object.x() + object.width() > itemRect.x()) return true;
                    break;
                case 2:
                    if (object.x() < (itemRect.x() + itemRect.width())) {
                        return true;
                    }
                    break;
                case 4:
                    if ((object.y() + object.height() + 10) >= itemRect.y()) return true;
                    break;
                default:
                    break;
                }
            }
        }
    }

    return false;
}
