import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
Item {
    anchors.fill: parent
    id:root
    property bool isPause: false
    property bool isRunning: true
    signal back()

    Connections{
        target: myGame
        onPosChanged:canvas.requestPaint();
        onGameOver:gameOverCover.visible=true;
    }

    focus: true
    Shortcut {
        sequence: "Left"
        onActivated:myGame.moveLeft();
    }
    Shortcut {
        sequence: "Right"
        onActivated:myGame.moveRight()
    }
    Shortcut {
        sequence: "Up"
        onActivated:myGame.orbit();
    }
    Shortcut {
        sequence: "Down"
        onActivated:myGame.doSoon();
    }


    //main Rectangle for game scene
    Canvas {
        id: canvas
        height: parent.height
        width:700
        anchors{
            top:parent.top
            left:parent.left
        }

        antialiasing: true


        // onTimeSecChanged: requestPaint()


        onPaint: {
            var ctx = getContext("2d");
            ctx.save();
            ctx.clearRect(0, 0, canvas.width, canvas.height);
            ctx.fillStyle = "white"
            ctx.fillRect(0, 0, width, height);
            //createmain circle
            // Create gradient
            // console.log(myGame.arryQML)

            // Fill with gradient
            for(var i=0;i<14;i++)
                for(var j=0;j<14;j++)
                {

                    if((myGame.arryQML[i*14 + j]) == "1"  || ( myGame.arryQML[i*14 + j]) == "2" )
                    {
                        ctx.fillStyle = "#F44336";
                        ctx.fillRect(i*50,j*50,50,50);
                    }

                    if((myGame.arryQML[i*14 + j]) == "3"  || ( myGame.arryQML[i*14 + j]) == "4" )
                    {
                        ctx.fillStyle = "#4CAF50";
                        ctx.fillRect(i*50,j*50,50,50);
                    }
                    if((myGame.arryQML[i*14 + j]) == "5"  || ( myGame.arryQML[i*14 + j]) == "6" )
                    {
                        ctx.fillStyle = "#2196F3";
                        ctx.fillRect(i*50,j*50,50,50);
                    }
                    if((myGame.arryQML[i*14 + j]) == "7"  || ( myGame.arryQML[i*14 + j]) == "8" )
                    {
                        ctx.fillStyle = "#FFC107";
                        ctx.fillRect(i*50,j*50,50,50);
                    }

                }
        }


    }

    Rectangle {
        id: gameOverCover
        visible: false
        height: parent.height
        width:700
        color:"green"
        anchors{
            top:parent.top
            left:parent.left
        }

        Text {

            text: "Game Over \n Your Score is :\n          "+myGame.score
            color: "black"

            anchors.centerIn:parent
        }



    }

    //Rectangle for showing next shap
//    Rectangle{
//        id:nextshapRect
//        color:"white"
//        width: parent.width/4 - 100
//        height: parent.width/4 - 100
//        anchors{
//            right: parent.right
//            top:parent.top
//            rightMargin: 50
//            topMargin: parent.height/8*2
//        }
//        radius: 5
//    }



    //Rectangle for showing score
    Rectangle{
        color:Material.color(Material.Blue)
        id:scoreLabel

        Text {

            text: myGame.score
            color: "black"

            anchors.centerIn: parent
        }
        width: 150
        height: 50

        anchors{
            top:parent.top
            right: parent.right
            rightMargin: 50
            topMargin: parent.height/16

        }
        radius: 10
    }


    //pause button
    Button{
        id:pauseButton
        text:"Pause"
        width: parent.width/4 - 100
        height: 50
        Material.theme :Material.Light
        onClicked: {

            myGame.pause()
            if(text ==="Pause")
                text="Contnue";
            else
                text="Pause";
        }
        Material.background: isPause ?Material.DeepOrange:Material.Green
        anchors{
            top:parent.top
            right:parent.right
            topMargin: parent.height/8*4
            rightMargin: 50
        }

    }
    //Restart button
    Button{
        id:reStartButton
        Material.theme :Material.Light
        text:"Restart"
        Material.background:  Material.DeepOrange
        onClicked: {

            myGame.restart()
            gameOverCover.visible=false;
        }
        width: parent.width/4 - 100
        height: 50
        anchors{
            top:parent.top
            right:parent.right
            topMargin: parent.height/8*5
            rightMargin: 50
        }

    }
    //Back button
    Button{
        id:exitButton
        text:"Back"
        Material.theme :Material.Light
        Material.background: Material.Red

        width: parent.width/4 - 100
        height: 50
        anchors{
            top:parent.top
            right:parent.right
            topMargin: parent.height/8*6
            rightMargin: 50
        }
        onClicked: {

            back()
            myGame.restart();
            myGame.pause();
        }
    }

}


