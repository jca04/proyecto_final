#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"
#include <QGraphicsScene>
#include <QTimer>

class Player;


class Enemy : public Character
{
    Q_OBJECT
public:
    Enemy(const Enemy& enemy);
    Enemy(QGraphicsScene* scene_, QString typeEnemy_, Player* player);

    void setPosition(float x, float y);

    ~Enemy();

private:
    QGraphicsScene* scene;
    QString typeEnemy;
    short direction;
    short imgNext;
    bool recolecAngle;
    bool shoot;
    float angleTrayectory;
    float velocityProjectile;
    QVector<QPixmap> VProjectiles;

    Player* player;

    QGraphicsPixmapItem* projectile;

    //enemigo aereo nivel 1
    QTimer* timeFlyEnemy;
    QTimer* shootPlayer;
    QTimer* timerProjectile;
    void moveEnemyFlier();
    void shootToPlayer();
    void moveProjectile();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;        // Método para dibujar el jugador (renderizarlo en la escena)
    QRectF boundingRect() const override;     // Método para definir el área interactiva del jugador
};

#endif // ENEMY_H
