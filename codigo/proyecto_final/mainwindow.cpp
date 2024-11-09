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


    this->scene = new QGraphicsScene(this);
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
    delete effectOpacity;
    delete animation;
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
    if (toScene == "CHAPTER_ONE") evilBrotherScene();
}

void MainWindow::homeScreen(){ // pantalla de inicio

    this->theme_chapter = new QMediaPlayer();
    this->theme_chapter->setSource(QUrl("qrc:/public/audios/main_theme.mp3"));
    this->theme_chapter->setAudioOutput(audio_output);

    this->theme_chapter->play();

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

    connect(button, &QPushButton::clicked, [this, button, buttonOut](){ // funcion lambda para ejecucuon del evento click del boton
        qDebug() << "boton clickeado";

        delete button;
        delete buttonOut;

        changeScene("CHAPTER_ONE");
    });

    connect(buttonOut, &QPushButton::clicked, [button, buttonOut](){
        qDebug() << "salir al escriotorio";

        delete button;
        delete buttonOut;
    });
}

//Capitulo uno diseño del nivel
void MainWindow::evilBrotherScene(){ // capitulo uno: el hermano gemelo de bart

    const int ADDSIZE = 40;
    QPixmap leftTopMap = QPixmap(":/public/images/evil_bart_map_top_left.png");
    QPixmap righTopMap = QPixmap(":/public/images/evil_bart_map_top_rigth.png");
    QPixmap leftDownMap = QPixmap(":/public/images/evil_bart_map_down_left.png");
    QPixmap rigthDownMap = QPixmap(":/public/images/evil_bart_map_down_rigth.png");

    if (
        leftTopMap.isNull() ||
        righTopMap.isNull() ||
        leftDownMap.isNull() ||
        rigthDownMap.isNull()
        ){
        qDebug() << "No se pudo cargar el mapa";
    }

    leftTopMap = leftTopMap.scaled((scene->width() / 2) + ADDSIZE, scene->height() / 2, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    righTopMap = righTopMap.scaled((scene->width() / 2) + ADDSIZE, scene->height() / 2, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    leftDownMap = leftDownMap.scaled((scene->width() / 2) + ADDSIZE, scene->height() / 2, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    rigthDownMap = rigthDownMap.scaled((scene->width() / 2) + ADDSIZE, scene->height() / 2, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    imgLeftTop = new QGraphicsPixmapItem(leftTopMap);
    imgleftDown = new QGraphicsPixmapItem(leftDownMap);
    imgRigthDown = new QGraphicsPixmapItem(rigthDownMap);
    imgRigthTop = new QGraphicsPixmapItem(righTopMap);

    //mitad de la pantalla
    int middleX = scene->width() / 2;
    int middleY = scene->height() / 2;

    imgLeftTop->setPos(0, 0);
    imgleftDown->setPos(0, middleY);
    imgRigthTop->setPos(middleX, 0);
    imgRigthDown->setPos(middleX, middleY);

    scene->addItem(imgLeftTop);
    scene->addItem(imgleftDown);
    scene->addItem(imgRigthTop);
    scene->addItem(imgRigthDown);



    // background = new QGraphicsPixmapItem(mapEvilBart1);
    // background->setPos(0,0);
    // scene->addItem(background);

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

