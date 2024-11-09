#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QAudioOutput>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QGraphicsPixmapItem>
#include <QVector>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

protected:
    void changeScene(QString toScene);
    void resizeEvent(QResizeEvent* event) override;

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    QMediaPlayer* theme_chapter;
    QAudioOutput* audio_output;
    QGraphicsOpacityEffect* effectOpacity;
    QPropertyAnimation* animation;
    QGraphicsPixmapItem* background;


    //nivel 1
    QGraphicsPixmapItem* imgLeftTop;
    QGraphicsPixmapItem* imgleftDown;
    QGraphicsPixmapItem* imgRigthTop;
    QGraphicsPixmapItem* imgRigthDown;

    void homeScreen();
    void evilBrotherScene();
    void kodosAndKand();
    void microbialCivilization();

};
#endif // MAINWINDOW_H
