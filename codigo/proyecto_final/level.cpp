#include "level.h"
#include "qgraphicsview.h"
#include <QGraphicsRectItem>


Level::Level(QString nameLevel) : nameLevel(nameLevel) {
     a_scene = new QGraphicsScene;
}


void Level::setLevel0(){ // primera scena inicio de la pantalla

    //cuadrar esta parte para que sea un video

    for (int i = 1; i <= 14; i++){
        QString url = ":/public/images/Homer_inicio_" + QString::number(i) + ".png";
        QPixmap homer = QPixmap(url);
        QGraphicsPixmapItem* bK = new QGraphicsPixmapItem(homer);
        bK->setPos(i * 15, 0);
        a_scene->addItem(bK); // añadir el fondo a la escena

    }

    QPixmap spriteBK = QPixmap(":/public/images/genesis_tub.png").scaled(m_view->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation); //imagen de fondo


    if (spriteBK.isNull())
        qDebug() << "No se pudo cargar la imagen del inicio";

    main_theme = new QMediaPlayer(); // main_theme
    audioOutput =  new QAudioOutput(); // output device
    main_theme->setSource(QUrl("qrc:/public/audios/main_theme.mp3"));

    audioOutput->setVolume(1.0);
    main_theme->setAudioOutput(audioOutput);

    main_theme->play();   // Reproduce el audio


    m_view->setScene(a_scene); // añadir la escena al grhapichsview
}

void Level::setLevel1(){}

void Level::setLevel2(){}

void Level::setLevel3(){}

void Level::changeScene(){}

void Level::initGame(){}

void Level::setView(QGraphicsView *view){
    m_view = view;
}

QGraphicsScene* Level::getScene() const {
    return a_scene;
}

Level::~Level(){
    delete m_view;
    delete a_scene;
}
