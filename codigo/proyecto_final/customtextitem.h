#ifndef CUSTOMTEXTITEM_H
#define CUSTOMTEXTITEM_H

#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>

class CustomTextItem : public QGraphicsTextItem
{
    Q_OBJECT
public:
    explicit CustomTextItem(const QString& text, QGraphicsItem* parent = nullptr);

signals:
    void clicked(); // señal que se emitira cunado se haga click

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // CUSTOMTEXTITEM_H
