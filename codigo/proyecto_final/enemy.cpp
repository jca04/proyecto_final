#include "enemy.h"
#include "player.h"
#include "libs/functions.h"

Enemy::Enemy(const Enemy& enemy){}

Enemy::Enemy(QGraphicsScene *scene_, QString typeEnemy_, Player *player) : scene(scene_)  ,typeEnemy(typeEnemy_), player(player)  {
    if (typeEnemy == "FLY_CIRCLE"){
        walksRigth.append(QPixmap(":/public/images/fly_demon_level1_rigth_1.png").scaled(50, 50, Qt::KeepAspectRatio));
        walksRigth.append(QPixmap(":/public/images/fly_demon_level1_rigth_2.png").scaled(50, 50, Qt::KeepAspectRatio));
        walksRigth.append(QPixmap(":/public/images/fly_demon_level1_rigth_3.png").scaled(50, 50, Qt::KeepAspectRatio));
        walksRigth.append(QPixmap(":/public/images/fly_demon_level1_rigth_4.png").scaled(50, 50, Qt::KeepAspectRatio));

        walksLeft.append(QPixmap(":/public/images/fly_demon_level1_left_1.png").scaled(50, 50, Qt::KeepAspectRatio));
        walksLeft.append(QPixmap(":/public/images/fly_demon_level1_left_2.png").scaled(50, 50, Qt::KeepAspectRatio));
        walksLeft.append(QPixmap(":/public/images/fly_demon_level1_left_3.png").scaled(50, 50, Qt::KeepAspectRatio));
        walksLeft.append(QPixmap(":/public/images/fly_demon_level1_left_4.png").scaled(50, 50, Qt::KeepAspectRatio));

        VProjectiles.append(QPixmap(":/public/images/fly_demon_projectile_1.png"));
        VProjectiles.append(QPixmap(":/public/images/fly_demon_projectile_2.png"));

        projectile = new QGraphicsPixmapItem(VProjectiles[0]);
        scene->addItem(projectile);

        timeFlyEnemy = new QTimer(this);
        shootPlayer = new QTimer(this);
        timerProjectile = new QTimer(this);

        connect(timeFlyEnemy, &QTimer::timeout, this, &Enemy::moveEnemyFlier);
        connect(shootPlayer, &QTimer::timeout, this, &Enemy::shootToPlayer);
        connect(timerProjectile, &QTimer::timeout, this, &Enemy::moveProjectile);

        timeFlyEnemy->start(40);
        shootPlayer->start(2000);
        timerProjectile->start(16);
    }
    else if (typeEnemy == "MELE"){

    }

    direction = 1; //rigth
    imgNext = 0;
    recolecAngle = true;
    velocityProjectile = 3.3;
    shoot = false;
}

//FLY_CIRCLE enemy
//==============================================
void Enemy::moveEnemyFlier(){
    imgNext++;

    if (imgNext >= walksRigth.size() || imgNext >= walksLeft.size()) imgNext = 0;

    float x = this->x();
    float y = this->y();

    Physics::circularMotion(3.0, 3.0, 0.1, x, y);

    if (x > this->x()) direction = 1;
    else direction = 2;

    setPos(x, y);
    update(boundingRect());
}


void Enemy::moveProjectile(){

    if (recolecAngle) angleTrayectory = angleBetween(this->x(), player->x(), this->y(), player->y());

    float dx = cos(angleTrayectory * M_PI / 180.0) * velocityProjectile;
    float dy = sin(angleTrayectory * M_PI / 180.0) * velocityProjectile;

    if (dx > 0.0) projectile->setPixmap(VProjectiles[1]);
    else projectile->setPixmap(VProjectiles[0]);

    projectile->setRotation(dx);

    if (projectile) projectile->setPos(projectile->x() + dx, projectile->y() + dy);

    recolecAngle = false;

    if (projectile && projectile->collidesWithItem(player) && projectile->opacity() != 0.0){
        recolecAngle = true;
        projectile->setOpacity(0.0);
        shoot = false;
        return;
    }

    if (projectile->x() < scene->sceneRect().left() ||
        projectile->x() > scene->sceneRect().right() ||
        projectile->y() < scene->sceneRect().top() ||
        projectile->y() > scene->sceneRect().bottom()
        ){
        recolecAngle = true;
        projectile->setOpacity(0.0);
        shoot = false;
    }
}

void Enemy::shootToPlayer(){

    if (shoot) return;
    else shoot = true;

    projectile->setOpacity(1.0);
    projectile->setPos(this->x(), this->y());
}

//==============================================

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);


    painter->fillRect(boundingRect(), Qt::transparent);

    if (typeEnemy == "FLY_CIRCLE"){
        painter->drawPixmap(0, 0, (direction == 1 ? walksRigth[imgNext] : walksLeft[imgNext]));
        return;
    }


}

QRectF Enemy::boundingRect() const {

    if (typeEnemy == "FLY_CIRCLE"){
        return QRectF(
            0,
            0,
            (direction == 1 ? walksRigth[imgNext].width() : walksLeft[imgNext].width()),
            (direction == 1 ? walksRigth[imgNext].height() : walksLeft[imgNext].height())
            );
    }
}

//=====================================00
//Getter y Setter
void Enemy::setPosition(float x, float y){
    setPos(x, y);
}

Enemy::~Enemy(){
    timeFlyEnemy->stop();
    shootPlayer->stop();
    timerProjectile->stop();

    delete player;
    delete projectile;
    delete timeFlyEnemy;
    delete shootPlayer;
    delete timerProjectile;
    delete scene;
}
