#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //configuraciones iniciales del graphicsview
    ui->graphicsView->setFrameShape(QFrame::NoFrame);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing); // suavizar bordes de los objetos
    ui->graphicsView->setRenderHints(QPainter::SmoothPixmapTransform); // suavizar bordes de las imagenes
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // inhabilitar scroll horizontal
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // inhabilitar scroll vertical
    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop); // ajustarlo arriba a la izquierda

    level = new Level("INICIO");
    level->setView(ui->graphicsView);
    level->setLevel0();

}

MainWindow::~MainWindow()
{
    delete level;
    delete ui;
}


void MainWindow::on_pushButton_clicked(){
    level->initGame();

    delete ui->pushButton;
}


