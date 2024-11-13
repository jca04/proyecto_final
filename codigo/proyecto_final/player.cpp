#include "player.h"

Player::Player(QGraphicsScene *scene) : scene(scene) {
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    // animationTimer = new QTimer(this);
    // connect(animationTimer, &QTimer::timeout, this, &Player::updateAnimation);
    // animationTimer->start(1000);

    fall = new QTimer(this);
    connect(fall, &QTimer::timeout, this, &Player::fallMotion); // timer para mantener el player pegado al suelo
    fall->start(25);

    Physics::isFalling = false;
}

void Player::fallMotion(){
    float x = this->x();
    float y = this->y();

    QRectF player(x, y, this->boundingRect().width() , this->boundingRect().height());

    if (isCollidengWall(scene, player, 4)) Physics::isFalling = false;
    else Physics::isFalling = true;

    if (Physics::isFalling){
        Physics::checkGravity(x, y);
        setPos(x, y);
    }
}

void Player::keyPressEvent(QKeyEvent * event){

    QRectF player(this->x(), this->y(), this->boundingRect().width() , this->boundingRect().height());
    qDebug() << "tecla";

    switch (event->key()) {
    // case Qt::Key_Up:  // Mover hacia arriba

    //     moveBy(0, -10);  // Mover en el eje Y
    //     break;
    case Qt::Key_Down:  // Mover hacia abajo
        // if (!isCollidengWall(scene, player, 4)){
        //     moveBy(0, 10);
        // }
        break;
    case Qt::Key_Left:  // Mover hacia la izquierda
        if (!isCollidengWall(scene, player, 2)){
            moveBy(-10, 0);
        }
        break;
    case Qt::Key_Right:
        if (!isCollidengWall(scene, player, 1)){
            moveBy(10, 0);
        }
        break;
    case Qt::Key_Space: //tecla para lanzar proyectiles (bombas)

        launchProyectile(scene, this->x(), this->y());

        for (int i = 0; i < VProjectiles.size(); i++){
            VProjectiles[i].drawProjectile();
        }
        break;
    default:
        break;
    }

}

// Método para dibujar el jugador (renderizarlo en la escena)
void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(Qt::blue);
    painter->drawRect(0, 0, 20, 30);
}

// Método para definir el área interactiva del jugador
QRectF Player::boundingRect() const {
    return QRectF(0, 0, 20, 30);
}

void Player::updateAnimation(){
    qDebug() << "aqui animcaion";
}

void Player::setPositonPlayer(QPointF position){
    this->setPos(position.x(), position.y());
}
