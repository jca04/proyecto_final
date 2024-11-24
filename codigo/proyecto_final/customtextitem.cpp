#include "customtextitem.h"

CustomTextItem::CustomTextItem(const QString& text, QGraphicsItem* parent)
    : QGraphicsTextItem(text, parent)
{}

void CustomTextItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    emit clicked(); // Se emite la señal personalizada
    QGraphicsTextItem::mousePressEvent(event); // Se llama al comportamiento predeterminado
}
