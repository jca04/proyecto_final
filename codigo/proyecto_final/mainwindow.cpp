#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSize screenSize = QGuiApplication::primaryScreen()->size();
    ui->graphicsView->setFixedSize(screenSize.width(), screenSize.height());
    ui->graphicsView->setBackgroundBrush(Qt::yellow);
    //configuraciones iniciales del graphicsview
    ui->graphicsView->setFrameShape(QFrame::NoFrame);
    ui->graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform); // suavizar bordes de las imagenes
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // inhabilitar scroll horizontal
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // inhabilitar scroll vertical
    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop); // ajustarlo arriba a la izquierda


    this->scene = new QGraphicsScene(0, 0,screenSize.width(), screenSize.height());
    this->scene->setSceneRect(0, 0, ui->graphicsView->width(), ui->graphicsView->height());

    ui->graphicsView->setScene(scene);

    //volumen de la salida de audio
    this->audio_output = new QAudioOutput();
    this->audio_output->setVolume(1.0);

    //animaciones ============================

    // effectOpacity = new QGraphicsOpacityEffect(ui->graphicsView); // efecto al cambiar de escenas
    // ui->graphicsView->setGraphicsEffect(effectOpacity);

    //mapas de las escenas
    QPixmap initialBackground = QPixmap(":/public/images/Stage_2_KrustyLand-removebg-preview.png");
    initialBackground = initialBackground.scaled(scene->width(), scene->height(), Qt::IgnoreAspectRatio);


    // krustyLandBackgroubd = krustyLandBackgroubd.scaled(800, 600, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    background = new QGraphicsPixmapItem(initialBackground);
     // background->setPos((ui->graphicsView->width() - initialBackground .width()) / 2,
     //                   (ui->graphicsView->height() - krustyLandBackgroubd.height()) / 2);

    scene->addItem(background);

    homeScreen();
}

MainWindow::~MainWindow()
{
    delete scene;
    delete theme_chapter;
    delete audio_output;
    // delete effectOpacity;
    // delete animation;
    delete ui;
}

void MainWindow::changeScene(QString toScene){ // cambiar de escena

    // //configuracion de la animacion
    // animation = new QPropertyAnimation(effectOpacity, "opacity");
    // animation->setDuration(500);
    // animation->setStartValue(1.0);
    // animation->setEndValue(0.0);

    // //señal de la animacion
    // connect(animation, &QPropertyAnimation::finished, this,[=]{

    //     scene->clear();
    //     effectOpacity->setOpacity(1.0);

    //     delete animation;
    // });

    // animation->start();
    // this->scene->clear(); //limpiar la escena actual
    scene->clear();

    QList<QGraphicsItem*> items = scene->items();

    foreach (QGraphicsItem* item, items) {
        scene->removeItem(item);
        delete item;
    }

    if (toScene == "CHAPTER_ONE") evilBrotherScene();
}

void MainWindow::homeScreen(){ // pantalla de inicio

    this->theme_chapter = new QMediaPlayer();
    this->theme_chapter->setSource(QUrl("qrc:/public/audios/main_theme.mp3"));
    this->theme_chapter->setAudioOutput(audio_output);

    // this->theme_chapter->play();

    QPushButton *button = new QPushButton("INICIAR"); // boton inicio
    QPushButton *buttonOut = new QPushButton("SALIR AL ESCRITORIO");

    QGraphicsProxyWidget *proxy = scene->addWidget(button); //necesario para poder tener el boton en la escena
    QGraphicsProxyWidget *proxyOut = scene->addWidget(buttonOut);

    button->setStyleSheet(
        "QPushButton {"
        "   background-color: #3498db;"
        "   color: white;"
        "   border-radius: 10px;"
        "   padding: 10px 20px;"
        "   font-size: 16px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #2980b9;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #1c5987;"
        "}"
    );

    buttonOut->setStyleSheet(
        "QPushButton {"
        "   background-color: #3498db;"
        "   color: white;"
        "   border-radius: 10px;"
        "   padding: 10px 20px;"
        "   font-size: 16px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #2980b9;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #1c5987;"
        "}"
    );

    proxy->setPos((ui->graphicsView->width() - button->width()) / 2, // posicionarlo en la mitad del a pantalla
                (ui->graphicsView->height() - button->height()) / 2);

    proxyOut->setPos((ui->graphicsView->width() - buttonOut->width()) / 2,
                     (ui->graphicsView->height() - buttonOut->height() + button->height() + 80) / 2);

    connect(button, &QPushButton::clicked, [this,proxy, proxyOut](){ // funcion lambda para ejecucuon del evento click del boton
        qDebug() << "boton clickeado";

        scene->removeItem(proxy);
        scene->removeItem(proxyOut);

        changeScene("CHAPTER_ONE");
    });

    connect(buttonOut, &QPushButton::clicked, [proxy, proxyOut, this](){
        qDebug() << "salir al escriotorio";

        scene->removeItem(proxy);
        scene->removeItem(proxyOut);
    });
}

//Capitulo uno diseño del nivel
void MainWindow::evilBrotherScene(){ // capitulo uno: el hermano gemelo de bart

    QPixmap mapEvilBart = QPixmap(":/public/images/evil_bart_map.png");

    if (mapEvilBart.isNull()){
        qDebug() << "No se pudo cargar el mapa";
    }

    mapEvilBart = mapEvilBart.scaled(scene->width(), scene->height(),  Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    background = new QGraphicsPixmapItem(mapEvilBart);
    background->setPos(10,0);
    scene->addItem(background);

    walls.append(scene->addRect(0, 160, 830, 10));
    walls.append(scene->addRect(870, 200, 660, 10));
    walls.append(scene->addRect(0, 160, 50, 200));
    walls.append(scene->addRect(0, 350, 450, 10));

    QGraphicsRectItem* wallFall = scene->addRect(450, 350, 150, 10);
    wallFall->setData(0, "wallFall");
    walls.append(wallFall);

    //top Rigth walls
    walls.append(scene->addRect(600, 350, 170, 10));
    walls.append(scene->addRect(770, 360, 20, 10));
    walls.append(scene->addRect(790, 370, 20, 10));
    walls.append(scene->addRect(810, 380, 20, 10));
    walls.append(scene->addRect(820, 390, 700, 10));
    walls.append(scene->addRect(790, 370, 20, 10));

    //left down walls
    walls.append(scene->addRect(450, 360, 10, 100));
    walls.append(scene->addRect(460, 420, 20, 10));
    walls.append(scene->addRect(470, 420, 10, 290));
    walls.append(scene->addRect(220, 700, 250, 10));
    walls.append(scene->addRect(220, 710, 10, 120));
    walls.append(scene->addRect(230, 825, 380, 10));
    walls.append(scene->addRect(550, 360, 10, 330));

    QGraphicsRectItem* wallUpStarway = scene->addRect(550, 690, 10, 140);
    wallUpStarway->setData(0, "wallStarway");
    walls.append(wallUpStarway);
    walls.append(scene->addRect(610, 690, 10, 140));

    //rigth down walls
    walls.append(scene->addRect(790, 570, 700, 10));
    walls.append(scene->addRect(790, 760, 50, 10));
    walls.append(scene->addRect(840, 750, 20, 10));
    walls.append(scene->addRect(860, 740, 20, 10));
    walls.append(scene->addRect(870, 730, 20, 10));
    walls.append(scene->addRect(880, 720, 640, 10));


    for (int i = 0; i < walls.size(); ++i) {
        walls[i]->setBrush(Qt::darkGray);
    }
}

void MainWindow::kodosAndKand(){ // capitulo dos: kodos y kang

}

void MainWindow::microbialCivilization(){ //capitulo tres: civilizacion de microbios

}

void MainWindow::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);

    // // Obtener el nuevo tamaño de la ventana
    // QSize newSize = event->size();
    // scene->setSceneRect(0, 0, newSize.width(), newSize.height());

    // // Redimensionar la imagen de fondo para que se ajuste a la nueva ventana
    // if (background) {
    //     // Escalar la imagen de fondo al tamaño de la escena (o la vista)
    //     // QPixmap scaledBackground = mapEvilBart1.scaled(scene->sceneRect().size().toSize(),
    //     //                                                Qt::KeepAspectRatio, Qt::SmoothTransformation);

    //     // // Establece la imagen escalada en el background
    //     // background->setPixmap(scaledBackground);
    // }

    // ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);


}

