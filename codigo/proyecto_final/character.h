#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsItem>
#include <QObject>

class Character : public QObject, public QGraphicsItem
{
public:
    Character();

protected:

    int heal;
    qreal speed;
    QPointF position;

    // void move();
    // void attack();

    void keyPressEvent(QKeyEvent* event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;


};

#endif // CHARACTER_H
