#ifndef LEVEL_H
#define LEVEL_H

#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QAudioOutput>

class Level{
public:
    Level(QString nameLevel);

    void setView(QGraphicsView *view);
    void changeScene();
    QGraphicsScene *getScene() const;

    void setLevel0();
    void setLevel1();
    void setLevel2();
    void setLevel3();

    void initGame();
    ~Level();

private:
    QGraphicsView *m_view;
    QGraphicsScene *a_scene;
    QMediaPlayer *main_theme;
    QAudioOutput *audioOutput;

    QString nameLevel;

};

#endif // LEVEL_H
