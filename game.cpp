#include "game.h"
#include "shape.h"
#include <QDebug>
#include <iostream>
using namespace std;
Game::Game(QQmlApplicationEngine *engine, QObject *parent) : QObject(parent)
{

    userinfo=new Users();
    QQmlContext *ctx =engine->rootContext();
    //sending object for user information
    ctx->setContextProperty ("userInfo" , userinfo);
    ctx->setContextProperty ("myGame" , this);

    expose=new ExposeClass(userinfo);

    //Here we expose both the class and the model to QML
    ctx->setContextProperty("ExposeClass", expose);
    ctx->setContextProperty("ExposeModel", expose->model());


    GameOver=false;

    QObject::connect (this,SIGNAL(moveDone()),this,SLOT(createNewShape()));
    QObject::connect (this,SIGNAL(gameOver()),this,SLOT(gameOverSlot()));
    if(userinfo->numberOfUsers == 0)
    {
        userinfo->AddUser("ali","0000","pass","0","13950712");
        userinfo->AddUser ("admin","0000","pass","1","19951004");
        delete(userinfo);
        userinfo=new Users();

    }



}

Game::~Game()
{
    delete(userinfo);
}

void Game::start()
{
    createNewShape ();
}

int Game::score()
{
    return Score;
}


void Game::setScore(int value)
{
    Score = value;
    emit scoreChanged();
}

void Game::createNewShape()
{
    if(!GameOver)
        shape=new Shape();
}


void Game::gameOverSlot()
{
    cout<<endl<<"moveing down";
    shape->timer->stop ();

    for(int i=0;i<14;i++)
    {
        cout<<endl;
        for(int j=0;j<14;j++)
            cout<<boardArry[j][i];
    }
    cout<<endl<<"Game Over";

}

void Game::pause()
{
    if(shape->isStillRunning)
    {
        shape->timer->stop ();
        shape->isStillRunning=false;
    }else
    {
        shape->timer->start();
        shape->isStillRunning=true;
    }
}

bool Game::isRunning()
{
    return shape->isStillRunning;
}

void Game::setIsRunning(bool value)
{
    shape->isStillRunning=value;
    emit isRunningChanged ();
}

void Game::restart()
{
    for(int i=0;i<14;i++)
        for(int j=0;j<14;j++)
            boardArry[i][j]=0;
    shape->timer->start ();
    GameOver=false;
    delete shape;
    createNewShape ();
    setScore (0);
}

QString Game::arryQML()
{
    return stringArrayQml;
}

void Game::setArryQML(QString value)
{
    for(int i=0;i<14;i++)
        for(int j=0;j<14;j++)
        {
            stringArrayQml[i*14+ j]=QString::number(boardArry[i][j]).at(0);

        }

    emit arryQMLChanged ();
}
