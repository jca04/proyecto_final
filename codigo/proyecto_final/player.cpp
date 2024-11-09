#include "player.h"


Player::Player(QGraphicsScene *scene) : scene(scene) {
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    // animationTimer = new QTimer(this);
    // connect(animationTimer, &QTimer::timeout, this, &Player::updateAnimation);
    // animationTimer->start(1000);
}

void Player::keyPressEvent(QKeyEvent * event){
    qDebug() << "tecla";

    switch (event->key()) {
    case Qt::Key_Up:  // Mover hacia arriba
        moveBy(0, -10);  // Mover en el eje Y
        break;
    case Qt::Key_Down:  // Mover hacia abajo
        moveBy(0, 10);  // Mover en el eje Y
        break;
    case Qt::Key_Left:  // Mover hacia la izquierda
        moveBy(-10, 0);  // Mover en el eje X
        break;
    case Qt::Key_Right:  // Mover hacia la derecha
        moveBy(10, 0);  // Mover en el eje X
        break;
    default:
        break;
    }
}

// Método para dibujar el jugador (renderizarlo en la escena)
void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(Qt::blue);  // Color de fondo
    painter->drawRect(0, 0, 20, 30);  // Dibujar el jugador
}

// Método para definir el área interactiva del jugador
QRectF Player::boundingRect() const {
    return QRectF(0, 0, 20, 30);
}

void Player::updateAnimation(){
    qDebug() << "aqui animcaion";
}
