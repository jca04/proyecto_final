#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "kodosandkang.h"
#include "homero.h"
#include <QComboBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //homero = new Homero(scene);

    //connect(homero, &Homero::returnToMainMenu, this, &MainWindow::homeScreen);

    //configuraciones iniciales del graphicsview
    QSize screenSize = QGuiApplication::primaryScreen()->size();   //tamaño de mi pantalla
    ui->graphicsView->setFixedSize(screenSize.width(), screenSize.height());  //tamaño por defecto el QGraphicsView
    ui->graphicsView->setStyleSheet("QGraphicsView { background-color: #34221E; }");
    ui->graphicsView->setFrameShape(QFrame::NoFrame);
    ui->graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform); // suavizar bordes de las imagenes
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // inhabilitar scroll horizontal
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // inhabilitar scroll vertical
    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop); // ajustarlo arriba a la izquierda

    setCentralWidget(ui->graphicsView);

    this->scene = new QGraphicsScene(0, 0,screenSize.width(), screenSize.height()); // crear nueva escena
    this->scene->setSceneRect(0, 0, ui->graphicsView->width(), ui->graphicsView->height()); //definir el tamaño de la escena

    ui->graphicsView->setScene(scene); // añadir la escena al graphicsview

    this->audio_output = new QAudioOutput();  //volumen de la salida de audio
    this->audio_output->setVolume(1.0);

    //animaciones ============================

    //mapas de las escenas
    QPixmap initialBackground = QPixmap(":/public/images/Stage_2_KrustyLand-removebg-preview.png");
    initialBackground = initialBackground.scaled(scene->width(), scene->height(), Qt::IgnoreAspectRatio);

    background = new QGraphicsPixmapItem(initialBackground);
    scene->addItem(background);

    homeScreen();

    player = new Player(scene); //trabajar el jugador como objeto QGraphicsItem
    player->setFocus();

    ui->graphicsView->setMouseTracking(true);
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
    QList<QGraphicsItem*> items = scene->items();

    foreach (QGraphicsItem* item, items) {
        scene->removeItem(item);
        delete item;
    }

    if (toScene == "CHAPTER_ONE") evilBrotherScene();
    if (toScene == "CHAPTER_TWO") kodosAndKand();
}

void MainWindow::homeScreen(){ // pantalla de inicio
    this->theme_chapter = new QMediaPlayer();
    this->theme_chapter->setSource(QUrl("qrc:/public/audios/main_theme.mp3"));
    this->theme_chapter->setAudioOutput(audio_output);

    // this->theme_chapter->play();
    QPushButton *button = new QPushButton("INICIAR"); // boton inicio
    QPushButton *buttonOut = new QPushButton("SALIR AL ESCRITORIO");
    QPushButton *kodosAndKangButton = new QPushButton("KODOS AND KANG");

    QGraphicsProxyWidget *proxy = scene->addWidget(button); //necesario para poder tener el boton en la escena
    QGraphicsProxyWidget *proxyOut = scene->addWidget(buttonOut);
    QGraphicsProxyWidget *proxyKodosAndKang = scene->addWidget(kodosAndKangButton);

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
    kodosAndKangButton->setStyleSheet(
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

    proxyKodosAndKang->setPos((ui->graphicsView->width() - kodosAndKangButton->width()) / 2,
                              (ui->graphicsView->height() - kodosAndKangButton->height() + 250) / 2);

    connect(button, &QPushButton::clicked, [this, proxy, proxyOut](){ // funcion lambda para ejecucuon del evento click del boton
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

    connect(kodosAndKangButton, &QPushButton::clicked, [this, proxy, proxyOut, proxyKodosAndKang]() {
        qDebug() << "Kodos and Kang seleccionado";

        // Elimina los elementos de la escena de inicio
        scene->removeItem(proxy);
        scene->removeItem(proxyOut);
        scene->removeItem(proxyKodosAndKang);

        // Cambiar a la escena de Kodos and Kang
        changeScene("CHAPTER_TWO");
    });
}

//DISEÑO DEL CAPITULO UNO: EL HERMANO MALVADO DE BART
void MainWindow::evilBrotherScene(){ // capitulo uno: el hermano gemelo de bart

    QPixmap mapEvilBart = QPixmap(":/public/images/evil_bart_map.png");

    if (mapEvilBart.isNull()){
        qDebug() << "No se pudo cargar el mapa";
    }

    mapEvilBart = mapEvilBart.scaled(scene->width(), scene->height(),  Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    background = new QGraphicsPixmapItem(mapEvilBart); // fondo de la escena
    background->setPos(10,0); //posicion del fondo
    scene->addItem(background);

    //QGraphicsRectItem para definir muros de la escena
    //arriba a la izquierda
    walls.append(scene->addRect(10, 160, 830, 10));
    walls.append(scene->addRect(870, 200, 660, 10));
    walls.append(scene->addRect(10, 160, 50, 200));
    walls.append(scene->addRect(10, 350, 450, 10));

    //arriba a la derecha
    walls.append(scene->addRect(600, 350, 170, 10));
    walls.append(scene->addRect(770, 360, 20, 10));
    walls.append(scene->addRect(790, 370, 20, 10));
    walls.append(scene->addRect(810, 380, 20, 10));
    walls.append(scene->addRect(820, 390, 700, 10));
    walls.append(scene->addRect(790, 370, 20, 10));

    //izquierda abajo
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

    //derecha abajo
    walls.append(scene->addRect(790, 570, 700, 10));
    walls.append(scene->addRect(790, 760, 50, 10));
    walls.append(scene->addRect(840, 750, 20, 10));
    walls.append(scene->addRect(860, 740, 20, 10));
    walls.append(scene->addRect(870, 730, 20, 10));
    walls.append(scene->addRect(880, 720, 640, 10));

    for (int i = 0; i < walls.size(); ++i) {
        walls[i]->setBrush(Qt::darkGray);
        if (walls[i]->data(0).toString() != "wallStarway"){
               walls[i]->setData(0, "wall");
        }
    }

    QPointF position(70.0, 260.0);
    player->setPositonPlayer(position);
    scene->addItem(player);
}

void MainWindow::kodosAndKand(){ // capitulo dos: kodos y kang

    QList<QGraphicsItem*> items = scene->items();
    foreach (QGraphicsItem* item, items) {
        scene->removeItem(item);
        delete item;
    }

    delete scene;

    // nueva escena para Kodos y Kang
    scene = new QGraphicsScene(0, 0, ui->graphicsView->width(), ui->graphicsView->height());
    scene->setSceneRect(0, 0, ui->graphicsView->width(), ui->graphicsView->height());

    QPixmap KodosAndKangMap(":/public/images/springfield.png");
    if (KodosAndKangMap.isNull()) {
        qDebug() << "No se pudo cargar la imagen del mapa";
    }

    KodosAndKangMap = KodosAndKangMap.scaled(ui->graphicsView->width(), ui->graphicsView->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QGraphicsPixmapItem* backgroundItem = new QGraphicsPixmapItem(KodosAndKangMap);
    scene->addItem(backgroundItem);

    int sceneWidth = scene->width();  // Ancho de la escena
    int sceneHeight = scene->height();  // Alto de la escena

    // Pared superior
    walls.append(scene->addRect(0, 0, sceneWidth, 10));

    // Pared inferior (movida 80 pixeles hacia arriba)
    walls.append(scene->addRect(0, sceneHeight - 80 - 10, sceneWidth, 10));

    // Pared izquierda
    walls.append(scene->addRect(0, 0, 10, sceneHeight));

    // Pared derecha
    walls.append(scene->addRect(sceneWidth - 10, 0, 10, sceneHeight));

    for (int i = 0; i < walls.size(); ++i) {
        walls[i]->setBrush(Qt::NoBrush);
        walls[i]->setPen(Qt::NoPen);
        if (walls[i]->data(0).toString() != "wallStarway") {
            walls[i]->setData(0, "wall");
        }
    }

    Homero* homero = new Homero(scene);
    homero->setWalls(walls);
    scene->addItem(homero);

    KodosAndKang* kodosAndKang = new KodosAndKang(scene, homero);
    scene->addItem(kodosAndKang);
    homero->setEnemigo(kodosAndKang);

    ui->graphicsView->setScene(scene);
}

void MainWindow::microbialCivilization(){ //capitulo tres: civilizacion de microbios

}

//metodos protegidos
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

//getters
QGraphicsScene* MainWindow::getScene() const {
    return this->scene;
}

