#include "shape.h"
#include <QDebug>
#include <QTime>
#include "game.h"
extern Game *game;

#include <iostream>
using namespace std;

Shape::Shape(QObject *parent) : QObject(parent)
{
    //setposition of start of blocks
    pos[0]=5;
    pos[1]= -2;
    isStillRunning=true;
    emit game->isRunningChanged ();

    uint seed=QTime::currentTime ().second ();
    qsrand(seed);

    color=(qrand()%8+1);
    if(color %2==0)
        color -=1;
    type=qrand()%6;

    fillBlocks ();


    timer=new QTimer();
    timer->start (1000);
    QObject::connect (timer,SIGNAL(timeout()),this,SLOT(moveDown()));

    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if (blocks[i][j] == color && game->boardArry[pos[0] +i][pos[1] + j + 1] != 0 && game->boardArry[pos[0] +i][pos[1] + j + 1] %2 ==0  && pos[1] + j + 1 >=0)
            {
                cout<<endl<<"down";
                game->GameOver=true;
                emit game->gameOver ();
                timer->stop ();
                isStillRunning=false;
                emit game->isRunningChanged ();

            }
    if(isStillRunning)
        mapBlocksToBoard();
}

Shape::~Shape()
{

}

void Shape::fillBlocks()
{
    switch (type) {
    case lShape:
        blocks[1][2]=color;
        blocks[1][1]=color;
        blocks[1][0]=color;
        blocks[2][2]=color;
        break;
    case nShape:
        blocks[0][2]=color;
        blocks[0][1]=color;
        blocks[1][0]=color;
        blocks[1][1]=color;
        break;
    case squareShape:
        blocks[0][0]=color;
        blocks[0][1]=color;
        blocks[1][0]=color;
        blocks[1][1]=color;
        break;
    case pyrmidShape:
        blocks[0][2]=color;
        blocks[1][1]=color;
        blocks[1][2]=color;
        blocks[2][2]=color;
        break;
    case linerShape:
        blocks[1][0]=color;
        blocks[1][1]=color;
        blocks[1][2]=color;
        break;
    case plusShape:
        blocks[1][0]=color;
        blocks[0][1]=color;
        blocks[1][1]=color;
        blocks[1][2]=color;
        blocks[2][1]=color;
        break;

    }

}

void Shape::Sblocks()
{
    for(int i=0;i<14;i++)
        for(int j=0;j<14;j++)
        {
            switch (game->boardArry[i][j]) {
            case red:
                game->boardArry[i][j]=reds;
                break;
            case blue:
                game->boardArry[i][j]=blues;
                break;
            case green:
                game->boardArry[i][j]=greens;
                break;
            case yellow:
                game->boardArry[i][j]=yellows;
                break;
            default:
                break;
            }
        }

}

void Shape::mapBlocksToBoard()
{

    for(int i=0;i<14;i++)
        for(int j=0;j<14;j++)
            if(game->boardArry[i][j] %2 == 1)
                game->boardArry[i][j] = 0;


    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(blocks[i][j] == color && pos[1] +j >= 0 && pos[1] +i <14 )
            {
                if(game->boardArry[pos[0]+i][pos[1] +j] ==0)
                    game->boardArry[pos[0]+i][pos[1] +j]=color;

            }

    emit game->posChanged ();
    game->setArryQML();
}

void Shape::orbit()
{


    tempArray[0][0] = blocks[2][0];
    tempArray[0][1] = blocks[1][0];
    tempArray[0][2] = blocks[0][0];
    tempArray[1][0] = blocks[2][1];
    tempArray[1][1] = blocks[1][1];
    tempArray[1][2] = blocks[0][1];
    tempArray[2][0] = blocks[2][2];
    tempArray[2][1] = blocks[1][2];
    tempArray[2][2] = blocks[0][2];

    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if( tempArray[i][j] == color && (pos[0] +i >=14 || pos[0] +i<0  ) || (pos[1] +j >=14 ) ||( game->boardArry[pos[0] +i][pos[1] + j] != 0 &&  (game->boardArry[pos[0] +i][pos[1] + j])%2 ==0 ))
                return;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            blocks[i][j] = tempArray[i][j];
    mapBlocksToBoard ();

}

void Shape::moveDown()
{
    setPos (pos[0],pos[1] + 1);
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(  (blocks[i][j] == color  && (game->boardArry[pos[0] +i][pos[1] + j+ 1] == 0 || game->boardArry[pos[0] +i][pos[1] + j + 1] % 2 == 1)&& pos[1]+j +1 >=14 ) ||
                 (blocks[i][j] == color && game->boardArry[pos[0] +i][pos[1] + j + 1] != 0 && game->boardArry[pos[0] +i][pos[1] + j + 1] %2 ==0 )  )
            {

                Sblocks ();

                checkRowToDelete=0;
                for(int s=0;s<14;s++)
                {
                    checkRowToDelete=0;
                    for(int s1=0;s1<14;s1++)
                        if(game->boardArry[s1][s]%2 ==0 && game->boardArry[s1][s] !=0)
                            checkRowToDelete++;
                    if(checkRowToDelete == 14)
                    {
                        for(int s2=0;s2<14;s2++)
                            game->boardArry[s2][s]=0;

                        for(int mdi=13;mdi>=0;mdi--)
                            for(int mdj=13;mdj>=0;mdj--)
                                if(game->boardArry[mdi][mdj] %2 == 0 && game->boardArry[mdi][mdj + 1] ==0 && mdj + 1 <14 )
                                {
                                    game->boardArry[mdi][mdj + 1 ] = game->boardArry[mdi][mdj] ;
                                    game->boardArry[mdi][mdj] =0;

                                }
                        game->setScore (game->score ()+1);
                    }
                }

                for(int k=0;k<3;k++)
                    for(int k1=0;k1<3;k1++)
                        if(blocks[k][k1] == color && pos[1] + k1 <0)
                        {
                            game->GameOver=true;
                            emit game->gameOver ();
                        }


                timer->stop ();
                isStillRunning=false;
                emit game->isRunningChanged ();

                emit game->moveDone ();
                return;
            }

}

void Shape::moveLeft()
{
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(blocks[i][j] == color && ( pos[0] + i - 1 <0 || game->boardArry[pos[0] +i - 1][pos[1] + j] != 0 &&  game->boardArry[pos[0] +i - 1][pos[1] + j ]%2==0) )
                return;


    setPos (pos[0] - 1,pos[1]);

}

void Shape::moveRight()
{
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(blocks[i][j] == color &&( pos[0] + i + 1 >=14 || game->boardArry[pos[0] +i + 1][pos[1] + j] != 0 &&  game->boardArry[pos[0] +i +1][pos[1] + j ] != color ))
                return;
    setPos (pos[0] +1,pos[1]);
}

void Shape::doSoon()
{
    while(isStillRunning)
        moveDown ();
}

void Shape::setPos(int valuex, int valuey)
{

    pos[0]=valuex;
    pos[1]=valuey;
    mapBlocksToBoard ();
}


