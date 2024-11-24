#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

    ui->graphicsView->setMouseTracking(true);
}


void MainWindow::changeScene(QString toScene){ // cambiar de escena
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
}

//DISEÑO DEL CAPITULO UNO: EL HERMANO MALVADO DE BART
void MainWindow::evilBrotherScene(){ // capitulo uno: el hermano gemelo de bart
    player = new Player(scene, 0.0, 238.0, enemies);
    player->setFocus();

    QPixmap mapEvilBart = QPixmap(":/public/images/map.png");

    if (mapEvilBart.isNull()){
        qDebug() << "No se pudo cargar el mapa";
    }

    mapEvilBart = mapEvilBart.scaled(scene->width(), scene->height(),  Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    background = new QGraphicsPixmapItem(mapEvilBart); // fondo de la escena
    background->setPos(10,0); //posicion del fondo
    scene->addItem(background);

    //QGraphicsRectItem para definir muros de la escena
   // walls.append(scene->addRect(45, 190, 830, 10));
    walls.append(scene->addRect(60, 190, 30, 10));
    walls.append(scene->addRect(90, 150, 10, 50));
    walls.append(scene->addRect(90, 150, 150, 10));
    walls.append(scene->addRect(240, 150, 10, 50));
    walls.append(scene->addRect(240, 200, 110, 10));
    walls.append(scene->addRect(340, 150, 10, 50));
    walls.append(scene->addRect(350, 150, 335, 10));
    walls.append(scene->addRect(685, 150, 10, 50));
    walls.append(scene->addRect(685, 200, 150, 10));
    walls.append(scene->addRect(835, 100, 10, 110));
    walls.append(scene->addRect(45, 160, 20, 150));
    walls.append(scene->addRect(870, 100, 660, 10));
    walls.append(scene->addRect(1500, 100, 40, 200));
    walls.append(scene->addRect(60, 307, 2000, 10));

    walls.append(scene->addRect(60, 600, 10, 160));
    walls.append(scene->addRect(70, 640, 30, 10));
    walls.append(scene->addRect(100, 600, 10, 40));
    walls.append(scene->addRect(100, 600, 180, 10));
    walls.append(scene->addRect(280, 600, 10, 40));
    walls.append(scene->addRect(290, 640, 100, 10));
    walls.append(scene->addRect(390, 600, 10, 40));
    walls.append(scene->addRect(400, 600, 380, 10));
    walls.append(scene->addRect(780, 550, 110, 10));
    walls.append(scene->addRect(890, 500, 10, 50));
    walls.append(scene->addRect(890, 510, 210, 10));
    walls.append(scene->addRect(1100, 500, 10, 50));
    walls.append(scene->addRect(1100, 550, 440, 10));
    walls.append(scene->addRect(1520, 550, 10, 210));
    walls.append(scene->addRect(60, 745, 1600, 10));


    for (int i = 0; i < walls.size(); ++i) {
        walls[i]->setBrush(Qt::transparent);
        walls[i]->setData(0, "wall");
    }

    QPointF position(70.0, 238.0);
    player->setPositonPlayer(position);
    scene->addItem(player);

    //enemigos
    enemies.append(new Enemy(scene ,"FLY_CIRCLE", player));

    for (const auto& enemy: enemies){
        enemy->setPosition(370.0, 208.0);
        scene->addItem(enemy);
    }
}

void MainWindow::kodosAndKand(){ // capitulo dos: kodos y kang

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

MainWindow::~MainWindow()
{
    delete scene;
    delete theme_chapter;
    delete audio_output;
    // delete effectOpacity;
    // delete animation;
    delete ui;
}
