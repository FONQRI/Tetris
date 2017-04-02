#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "exposeclass.h"
#include "users.h"
#include "shape.h"
class Game : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isRunning READ isRunning WRITE setIsRunning NOTIFY isRunningChanged)
    Q_PROPERTY(int score READ score WRITE setScore NOTIFY scoreChanged)
    Q_PROPERTY(QString arryQML READ arryQML WRITE setArryQML NOTIFY arryQMLChanged)
public:
    explicit Game(QQmlApplicationEngine *engine, QObject *parent = 0);

~Game();
    Users *userinfo;
    Shape *shape;
    short boardArry[14][14]={};
    bool GameOver;
    ExposeClass *expose;

private:
    int Score=0;
    QString stringArrayQml;
    //
signals:
    void scoreChanged();
    void gameOver();
    void moveDone();
    void posChanged();
    void arryQMLChanged();
    void isRunningChanged();
public slots:
    int score() ;
    void setScore(int value);
    void createNewShape();
    void gameOverSlot();
    void pause();

    bool isRunning();
    void setIsRunning(bool value);

    //restart slot
    void restart();
    void start();

    //oebit slot ***************************************************************************
    void orbit(){shape->orbit ();}

    //move slots *************************************************************************
    void moveDown(){shape->moveDown ();}
    void moveLeft(){shape->moveLeft ();}
    void moveRight(){shape->moveRight ();}
    void doSoon(){shape->doSoon ();}

    //qml arry slots
    QString arryQML();
    void setArryQML(QString value = "");
};



#endif // GAME_H
