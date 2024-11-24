#include "homero.h"
#include "customtextitem.h"
#include <QPointF>
#include <QGraphicsRectItem>

Homero::Homero(QGraphicsScene* scene) : actualSprite(0), walkDirection(1), isWalking(false), isAttacking(false), life(100), speed(10), scene(scene) {
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    // Tamaño deseado para los sprites
    const int spriteWidth = 150;  // Ancho del sprite
    const int spriteHeight = 150; // Altura del sprite

    // Sprites para caminar (derecha)
    walksRight = { QPixmap(":/public/images/hom_walk_1.png").scaled(spriteWidth, spriteHeight),
                  QPixmap(":/public/images/hom_walk_2.png").scaled(spriteWidth, spriteHeight),
                  QPixmap(":/public/images/hom_walk_3.png").scaled(spriteWidth, spriteHeight),
                  QPixmap(":/public/images/hom_walk_4.png").scaled(spriteWidth, spriteHeight) };

    // Sprites para caminar (izquierda)
    walksLeft = { QPixmap(":/public/images/hom_walk_1_left.png").scaled(spriteWidth, spriteHeight),
                 QPixmap(":/public/images/hom_walk_2_left.png").scaled(spriteWidth, spriteHeight),
                 QPixmap(":/public/images/hom_walk_3_left.png").scaled(spriteWidth, spriteHeight),
                 QPixmap(":/public/images/hom_walk_4_left.png").scaled(spriteWidth, spriteHeight) };

    // Sprites para atacar (derecha e izquierda)
    fightRight = { QPixmap(":/public/images/hom_punch.png").scaled(spriteWidth, spriteHeight) };
    fightLeft = { QPixmap(":/public/images/hom_punch_left.png").scaled(spriteWidth, spriteHeight) };

    // Sprites de homero muerto
    homeroDead = QPixmap(":/public/images/hom_dead.png").scaled(spriteWidth, spriteHeight);

    // Donut sprite
    donutSprite = QPixmap(":/public/images/donut.png").scaled(20, 20);

    // Timer para la animación
    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &Homero::updateAnimation);
    animationTimer->start(100); // Cambia el sprite cada 100 ms

    // Posiciona a Homero en el suelo
    setPixmap(walksRight[0]);
    setPos(100, 600); // Coordenadas iniciales (en el suelo)

}

void Homero::lanzarObjeto() {

    QPointF posicionInicial = pos();
    QPointF posicionEnemigo = enemigo->pos();


    QGraphicsPixmapItem* proyectil = new QGraphicsPixmapItem(donutSprite);
    //QGraphicsRectItem* proyectil = new QGraphicsRectItem();
    proyectil->setPos(posicionInicial.x(), posicionInicial.y() + boundingRect().height() / 2);
    scene->addItem(proyectil);

    qreal dx = posicionEnemigo.x() - posicionInicial.x();
    qreal dy = posicionEnemigo.y() - posicionInicial.y();
    qreal velocidadX = dx / 100.0;
    qreal velocidadY = dy / 100.0 - 0.05 * 100.0 * 2;

    QTimer* proyectilTimer = new QTimer(this);

    connect(proyectilTimer, &QTimer::timeout, [=]() mutable {

        velocidadY += 0.05;
        proyectil->moveBy(velocidadX, velocidadY);

        if (enemigo->collidesWithItem(proyectil)) {
            enemigo->recibirDano(5);
            delete proyectil;
            proyectilTimer->stop();
            proyectilTimer->deleteLater();
        } else if (!scene->sceneRect().contains(proyectil->pos())) {
            delete proyectil;
            proyectilTimer->stop();
            proyectilTimer->deleteLater();
        }
    });

    proyectilTimer->start(20);
}

void Homero::recibirDano(int cantidad) {
    life -= cantidad;
    if (life <= 0) {
        qDebug() << "Homero ha perdido toda su vida!";
        setPixmap(homeroDead);
        animationTimer->stop();
        deadMenu();
    }
}

void Homero::keyPressEvent(QKeyEvent* event) {
    if (isAttacking) return; // No permitir movimiento mientras está atacando

    switch (event->key()) {
    case Qt::Key_Left:
        if (!isWalking || walkDirection != -1) {
            isWalking = true;
            walkDirection = -1;
        }
        break;
    case Qt::Key_Right:
        if (!isWalking || walkDirection != 1) {
            isWalking = true;
            walkDirection = 1;
        }
        break;
    case Qt::Key_Shift:
        speed = 20;
        break;
    case Qt::Key_X:
        isAttacking = true;
        actualSprite = 0;
        lanzarObjeto();  // Lanzar objeto cuando se presiona la barra espaciadora
        break;
    default:
        QGraphicsPixmapItem::keyPressEvent(event);
        break;
    }
}

void Homero::keyReleaseEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Left && walkDirection == -1) {
        isWalking = false;
    } else if (event->key() == Qt::Key_Right && walkDirection == 1) {
        isWalking = false;
    }

    if (!isWalking) {
        actualSprite = 0; // Se reinicia la animación de caminar
        setPixmap(walkDirection == 1 ? walksRight[0] : walksLeft[0]);
    }
}

void Homero::updateAnimation() {
    if (isAttacking) {
        // Animación de ataque
        const QVector<QPixmap>& attackSprites = walkDirection == 1 ? fightRight : fightLeft;
        setPixmap(attackSprites[actualSprite]);
        actualSprite++;
        if (actualSprite >= attackSprites.size()) {
            isAttacking = false; // Termina ataque
            actualSprite = 0;
        }
        return;
    }

    if (isWalking) {
        // Animación de caminar
        const QVector<QPixmap>& walkSprites = walkDirection == 1 ? walksRight : walksLeft;
        setPixmap(walkSprites[actualSprite]);
        actualSprite = (actualSprite + 1) % walkSprites.size();

        // Verificar colisiones antes de mover
        int dx = walkDirection * speed; // Desplazamiento en x
        if (!checkWallCollision(dx, 0)) {
            moveBy(dx, 0); // Solo se mueve si no hay colisión
        }
    }
}

bool Homero::checkWallCollision(int dx, int dy) {
    // Crear una copia de la posición actual con el desplazamiento propuesto
    QRectF nextPos = boundingRect().translated(pos().x() + dx, pos().y() + dy);

    // Comprobar colisiones con cada pared
    for (const auto& wall : walls) {
        if (nextPos.intersects(wall->boundingRect().translated(wall->pos()))) {
            return true; // Hay colisión
        }
    }
    return false; // No hay colisión
}

void Homero::atacarKodosAndKang(KodosAndKang *enemigo) {
    QGraphicsRectItem* proyectil = new QGraphicsRectItem();
    proyectil->setRect(x() + (walkDirection == 1 ? 50 : -10), y() + 20, 10, 5);
    proyectil->setBrush(Qt::blue);
    scene->addItem(proyectil);

    QTimer* movementTimer = new QTimer(this);
    connect(movementTimer, &QTimer::timeout, [proyectil, enemigo, movementTimer, this]() {
        proyectil->moveBy(walkDirection * 15, 0); // Mueve el proyectil

        // Verificar colisión con KodosAndKang
        if (enemigo->collidesWithItem(proyectil)) {
            enemigo->recibirDano(10); // Reducir vida de KodosAndKang
            delete proyectil;         // Eliminar proyectil
            movementTimer->stop();
            movementTimer->deleteLater();
        } else if (!scene->sceneRect().contains(proyectil->pos())) {
            delete proyectil; // Eliminar proyectil si sale de la escena
            movementTimer->stop();
            movementTimer->deleteLater();
        }
    });
    movementTimer->start(50);
}

void Homero::deadMenu() {
    // Limpiar elementos previos relacionados con el menú de muerte
    QList<QGraphicsItem*> items = scene->items();
    foreach (QGraphicsItem* item, items) {
        if (item->zValue() >= 1) { // Eliminar elementos que están encima del fondo del juego
            scene->removeItem(item);
            delete item;
        }
    }

    // Crear fondo del menú
    QGraphicsRectItem* fondo = new QGraphicsRectItem();
    fondo->setRect(0, 0, 400, 200);
    fondo->setBrush(Qt::black);
    fondo->setOpacity(0.8);
    fondo->setZValue(1); // Asegurarse de que esté encima
    fondo->setPos(scene->width() / 2 - 200, scene->height() / 2 - 100);
    scene->addItem(fondo);

    // Texto "Has muerto"
    QGraphicsTextItem* texto = new QGraphicsTextItem("¡Has muerto!");
    texto->setDefaultTextColor(Qt::white);
    texto->setFont(QFont("Arial", 20, QFont::Bold));
    texto->setZValue(2);
    texto->setPos(fondo->pos().x() + 100, fondo->pos().y() + 20);
    scene->addItem(texto);

    // Botón "Intentar de nuevo"
    CustomTextItem* botonReintentar = new CustomTextItem("Intentar de nuevo");
    botonReintentar->setDefaultTextColor(Qt::white);
    botonReintentar->setFont(QFont("Arial", 16));
    botonReintentar->setZValue(2);
    botonReintentar->setPos(fondo->pos().x() + 50, fondo->pos().y() + 100);
    scene->addItem(botonReintentar);
    connect(botonReintentar, &CustomTextItem::clicked, [this]() {
        restartGame(); // Llama al método para reiniciar el juego
    });

    // Botón "Salir al menú"
    CustomTextItem* botonSalir = new CustomTextItem("Salir al menú");
    botonSalir->setDefaultTextColor(Qt::white);
    botonSalir->setFont(QFont("Arial", 16));
    botonSalir->setZValue(2);
    botonSalir->setPos(fondo->pos().x() + 200, fondo->pos().y() + 100);
    scene->addItem(botonSalir);
    connect(botonSalir, &CustomTextItem::clicked, [this]() {
        exitMenu(); // Llama al método para volver al menú de inicio
    });
}

void Homero::restartGame() {
    qDebug() << "Reiniciando el nivel";
}

void Homero::exitMenu() {
    qDebug() << "Volviendo al menú principal...";
    QList<QGraphicsItem*> items = scene->items();
    foreach (QGraphicsItem* item, items) {
        scene->removeItem(item);
        delete item;
    }

    emit returnToMainMenu();
}

void Homero::setEnemigo(KodosAndKang *enemigo) {
    this->enemigo = enemigo;
}

void Homero::setWalls(const QVector<QGraphicsRectItem*>& walls) {
    this->walls = walls;
}
