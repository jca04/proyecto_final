#include "player.h"
#include "enemy.h"

Player::Player(QGraphicsScene *scene, float x, float y, QVector<Enemy *> enemies) : scene(scene), xPlayer(x), yPlayer(y), enemies(enemies) {
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    //sprites de bart caminando hacia la derecha;
    walksRigth.append(QPixmap(":/public/images/bart_stop.png").scaled(70, 70, Qt::KeepAspectRatio));
    walksRigth.append(QPixmap(":/public/images/bart_walks_1-removebg-preview.png").scaled(70, 70, Qt::KeepAspectRatio));
    walksRigth.append(QPixmap(":/public/images/bart_walks_2-removebg-preview.png").scaled(70, 70, Qt::KeepAspectRatio));
    walksRigth.append(QPixmap(":/public/images/bart_walks_2-removebg-preview.png").scaled(70, 70, Qt::KeepAspectRatio));
    walksRigth.append(QPixmap(":/public/images/bart_walks_4-removebg-preview.png").scaled(70, 70, Qt::KeepAspectRatio));
    walksRigth.append(QPixmap(":/public/images/bart_walks_5-removebg-preview.png").scaled(70, 70, Qt::KeepAspectRatio));

    //sprites de bart camninado hacia la izquierda
    walksLeft.append(QPixmap(":/public/images/bart_stop_left.png").scaled(70, 70, Qt::KeepAspectRatio));
    walksLeft.append(QPixmap(":/public/images/bart_walks_1_left.png").scaled(70, 70, Qt::KeepAspectRatio));
    walksLeft.append(QPixmap(":/public/images/bart_walks_2_left.png").scaled(70, 70, Qt::KeepAspectRatio));
    walksLeft.append(QPixmap(":/public/images/bart_walks_3_left.png").scaled(70, 70, Qt::KeepAspectRatio));
    walksLeft.append(QPixmap(":/public/images/bart_walks_4_left.png").scaled(70, 70, Qt::KeepAspectRatio));
    walksLeft.append(QPixmap(":/public/images/bart_walks_5_left.png").scaled(70, 70, Qt::KeepAspectRatio));

    //sprites de bart peleando hacia la derecha
    fightRigth.append(QPixmap(":/public/images/bart_figth_1_rigth.png").scaled(70, 70, Qt::KeepAspectRatio));
    fightRigth.append(QPixmap(":/public/images/bart_figth_2_rigth.png").scaled(70, 70, Qt::KeepAspectRatio));
    fightRigth.append(QPixmap(":/public/images/bart_figth_3_rigth.png").scaled(70, 70, Qt::KeepAspectRatio));
    fightRigth.append(QPixmap(":/public/images/bart_figth_4_rigth.png").scaled(70, 70, Qt::KeepAspectRatio));

    //sprites de bart peleando hacia la izquierda
    fightLeft.append(QPixmap(":/public/images/bart_figth_1_left.png").scaled(70, 70, Qt::KeepAspectRatio));
    fightLeft.append(QPixmap(":/public/images/bart_figth_2_left.png").scaled(70, 70, Qt::KeepAspectRatio));
    fightLeft.append(QPixmap(":/public/images/bart_figth_3_left.png").scaled(70, 70, Qt::KeepAspectRatio));
    fightLeft.append(QPixmap(":/public/images/bart_figth_4_left.png").scaled(70, 70, Qt::KeepAspectRatio));

    //sprites de bart saltando derecha
    jumpingRigth.append(QPixmap(":/public/images/bart_jumping_1_rigth.png").scaled(70, 70, Qt::KeepAspectRatio));
    jumpingRigth.append(QPixmap(":/public/images/bart_jumping_2_rigth.png").scaled(70, 70, Qt::KeepAspectRatio));

    //sprites de bart saltando a la izquerda
    jumpingLeft.append(QPixmap(":/public/images/bart_jumping_1_left.png").scaled(70, 70, Qt::KeepAspectRatio));
    jumpingLeft.append(QPixmap(":/public/images/bart_jumping_2_left.png").scaled(70, 70, Qt::KeepAspectRatio));

    //sprites de bart lanzando un objeto
    launchObjects.append(QPixmap(":/public/images/bart_ball_launch_1.png").scaled(30, 30, Qt::KeepAspectRatio));
    launchObjects.append(QPixmap(":/public/images/bart_ball_launch_2.png").scaled(30, 30, Qt::KeepAspectRatio));
    launchObjects.append(QPixmap(":/public/images/bart_ball_launch_3.png").scaled(30, 30, Qt::KeepAspectRatio));
    launchObjects.append(QPixmap(":/public/images/bart_ball_launch_4.png").scaled(30, 30, Qt::KeepAspectRatio));
    launchObjects.append(QPixmap(":/public/images/bart_ball_launch_5.png").scaled(30, 30, Qt::KeepAspectRatio));

    objectLaunch = new QGraphicsPixmapItem(launchObjects[0]);
    objectLaunch->setOpacity(0.0);
    objectLaunch->setZValue(5);
    scene->addItem(objectLaunch);

    fall = new QTimer(this);
    walksTimeOut = new QTimer(this);
    figthTimeOut = new QTimer(this);
    launchTimer = new QTimer(this);

    connect(fall, &QTimer::timeout, this, &Player::fallMotion); // timer para el salto
    connect(walksTimeOut, &QTimer::timeout, this, &Player::walkingPlayer); // timer para caminar
    connect(figthTimeOut, &QTimer::timeout, this, &Player::attack); // timer para el combo de ataques a mele
    connect(launchTimer, &QTimer::timeout, this, &Player::moveLaunchObject);

    fall->start(16);
    walksTimeOut->start(80);
    figthTimeOut->start(200);
    launchTimer->start(30);

    actualSprite = 0;
    directionWalk = 1;
    isJumping = false;

    Character::isWalking = false;
    Character::indSpriteAttack = -1;
    Character::speed = 5;
    Character::isFigthing = false;
    Character::isLaunchObject = 0;
    Character::isLaunchObject = false;
    Physics::isFalling = false;
}

void Player::fallMotion(){
    if (isJumping){
        float xdt = this->x();
        float ydt = this->y();

        if (Physics::jumping(xdt, ydt, yPlayer, (directionWalk == 1 ? 60 : 135))){
            isJumping = false;
            Physics::time = 0.0;
            return;
        }else setPos(xdt, ydt);
    }
}

void Player::keyPressEvent(QKeyEvent * event){

    QRectF player(this->x(), this->y(), this->boundingRect().width() , this->boundingRect().height());

    switch (event->key()) {
    case Qt::Key_Up:  // Mover hacia arriba
        isJumping = true;
        break;
    case Qt::Key_Left:  // Mover hacia la izquierda
        if (!isCollidengWall(scene, player, 2)){
            moveBy(-Character::speed, 0);
            directionWalk = 2;
            Character::isWalking = true;
        }
        break;
    case Qt::Key_Right:
        if (!isCollidengWall(scene, player, 1)){
            directionWalk = 1;
            Character::isWalking = true;
            moveBy(Character::speed, 0);
        }
        break;
    case Qt::Key_Space: //tecla para lanzar proyectiles (bombas)
        launchObject();
        break;
    case Qt::Key_X: // atacar cuerpo a cuerpo
        qDebug() << "Atacando";
        break;
    default:
        break;
    }
}

void Player::walkingPlayer(){

    if (Character::isWalking){
        actualSprite++;
        if (actualSprite >= walksRigth.size() || actualSprite >= walksLeft.size()) actualSprite = 0;
    }else actualSprite = 0; // sprite cuando esta parado

    update(boundingRect());
    Character::isWalking = false;
}

void Player::attack(){

    if (Character::isFigthing){
        Character::indSpriteAttack++;

        if (Character::indSpriteAttack >= fightLeft.size() ||
            Character::indSpriteAttack >= fightRigth.size()
            ){
            Character::indSpriteAttack = 0;
        }
    }else Character::indSpriteAttack = -1;

    update(boundingRect());
    Character::isFigthing = false;
}

//launch object
void Player::launchObject(){
    if (Character::isLaunchObject) return;
    else Character::isLaunchObject = true;
    Physics::time = 0;
    objectLaunch->setOpacity(1.0);
    objectLaunch->setPos(this->x(), this->y());
}

void Player::moveLaunchObject(){
    if (Character::isLaunchObject){
        float x = objectLaunch->x();
        float y = objectLaunch->y();

        Physics::parabolicMotion(x, y, 55);

        objectLaunch->setPos(x, y);
    }

    if (objectLaunch->y() > (this->y() + this->boundingRect().height())){
        objectLaunch->setOpacity(0.0);
        Character::isLaunchObject = false;
    }

    if (objectLaunch->x() < scene->sceneRect().left() ||
        objectLaunch->x() > scene->sceneRect().right() ||
        objectLaunch->y() < scene->sceneRect().top() ||
        objectLaunch->y() > scene->sceneRect().bottom()
        ){
        objectLaunch->setOpacity(0.0);
        Character::isLaunchObject = false;
    }

    QList<QGraphicsItem*> items = scene->items();

    for (QGraphicsItem* item: items){
        for (const auto& enemy: enemies){
            if (enemy->collidesWithItem(item)){
                qDebug() << "colison";
            }
        }
    }
}

// Método para dibujar el jugador (renderizarlo en la escena)
void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->fillRect(boundingRect(), Qt::transparent);

    //saltando
    if (isJumping){
        painter->drawPixmap(
            0,
            0,
            (directionWalk == 1 ? jumpingRigth[1] : jumpingLeft[1])
            );
        return;
    }


    if (Character::indSpriteAttack != -1){ // cuando ataca
        if (directionWalk == 1){
            painter->drawPixmap(
                0,
                0,
                fightRigth[Character::indSpriteAttack]
            );
            return;
        }

        painter->drawPixmap(
            0,
            0,
            fightLeft[Character::indSpriteAttack]
        );
        return;
    }

    //caminar
    if (directionWalk != 1){
        painter->drawPixmap(
            0,
            0,
            walksLeft[actualSprite]
        );
        return;
    }

    painter->drawPixmap(
        0,
        0,
        walksRigth[actualSprite]
    );
}

QRectF Player::boundingRect() const { // Método para definir el área interactiva del jugador
    if (Character::indSpriteAttack != -1){
        if (directionWalk == 1){
            return QRectF(
                0,
                0,
                fightRigth[Character::indSpriteAttack].width() + 10,
                fightRigth[Character::indSpriteAttack].height()
            );
        }

        return QRectF(
            0,
            0,
            fightLeft[Character::indSpriteAttack].width() + 10,
            fightLeft[Character::indSpriteAttack].height()
        );
    }


    if (directionWalk != 1){
         return QRectF(
            0,
            0,
            walksLeft[actualSprite].width() + 10,
            walksLeft[actualSprite].height()
            );
    }

    return QRectF(
        0,
        0,
        walksRigth[actualSprite].width() + 10,
        walksRigth[actualSprite].height()
        );
}

void Player::setPositonPlayer(QPointF position){
    this->setPos(position.x(), position.y());
}


Player::~Player(){
    figthTimeOut->stop();
    walksTimeOut->stop();
    fall->stop();

    delete scene;
    delete figthTimeOut;
    delete fall;
    delete walksTimeOut;
    delete scene;
}
