#include "projectile.h"

Projectile::Projectile(const Projectile& projectile){}

Projectile::Projectile(qreal V0_, qreal angle_, qreal g_, qreal time_, qreal dx, qreal dy, QGraphicsScene *scene_)
    : v0(V0_), angle(angle_), g(g_), time(time_ ), dy(dy), dx(dx), scene(scene_)
{
    angle = qDegreesToRadians(angle);
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Projectile::updatePosition);
    timer->start(16);
}

void Projectile::drawProjectile(){
    if (!sllipe){
        sllipe = new QGraphicsEllipseItem(-5, -5, 10, 10);  // Crea un círculo de 10x10 (radio 5)
        sllipe->setBrush(Qt::red);  // Color del proyectil
        sllipe->setPos(dx, dy);
        scene->addItem(sllipe);
    }

}

void Projectile:: updatePosition(){

    if (!sllipe){
        drawProjectile();
    }

    time += 0.016;

    qreal v0x = v0 * cos(angle);
    qreal v0y = v0 * sin(angle);

    qreal x = dx + (v0x * time);
    qreal y = dy + ((v0y * time) - (0.5 * g * time * time));

    qDebug() << x << " " << y;

    sllipe->setPos(x, y);

    if (y > scene->height() || x > scene->width() || x < 0 || y < 0) {
        timer->stop();  // Detiene la animación si el proyectil sale de los límites

        delete timer;
        delete sllipe;
        sllipe = nullptr;

    }
}

