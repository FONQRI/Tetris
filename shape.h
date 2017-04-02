#ifndef SHAPE_H
#define SHAPE_H

#include <QObject>
#include <QTimer>

class Shape : public QObject
{
    Q_OBJECT
public:
    explicit Shape(QObject *parent = 0 );
    ~Shape();

    //public values
    int pos[2];
    int direction;
    bool isStillRunning;
    int type;
    QTimer *timer;
    int blocks[3][3] = {};
    int tempArray[3][3] ={};
    int color;
int checkRowToDelete;//for chacking if row is full delete it
    // enums *************************************************************************************

    enum colortype {
        white,
        red,
        reds,
        green,
        greens,
        blue,
        blues,
        yellow,
        yellows
    };

    enum directiontype{
        left,
        right,
        up,
        down
    };

    enum typetype{
        lShape,
        nShape,
        squareShape,
        pyrmidShape,
        linerShape,
        plusShape
    };

    //fill blocks arry
    void fillBlocks();

//change color of blocks at the end
    void Sblocks();

    //map blocks from blocks to board array
    void mapBlocksToBoard();

public slots:

    //oebit slot ***************************************************************************
   void orbit();

    //move slots *************************************************************************
    void moveDown();
    void moveLeft();
    void moveRight();
    void doSoon() ;


    //position slots **********************************************************************
    void setPos(int valuex, int valuey);






};



#endif // SHAPE_H
