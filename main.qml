import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Window 2.0

ApplicationWindow {
    visible: true

    //setting window size
    maximumHeight: 700
    minimumHeight: 700
    maximumWidth: 1000
    minimumWidth: 1000

    //setting position of window
    x:Screen.width/2-width/2
    y:Screen.height/2 - height/2

    //setting title
    title: qsTr("Tetris")

    //setting theme
    Material.theme :Material.Dark
    Component.onCompleted:
    {
        mainLoader.sourceComponent=menuComp

    }
  

    //Game Component
    Component{
        id:gameComp
        GamePage{
onBack: mainLoader.sourceComponent=menuComp
        }
    }


    //menu Component
    Component{
        id:menuComp
        MenuPage{
            onScoreBoard: mainLoader.sourceComponent=scoreBoardComp
            onStartGame: mainLoader.sourceComponent=gameComp
        }
    }

    //Admin Component
    Component{
        id:adminComp
        AdminPage{
onBack: mainLoader.sourceComponent=loginComp
        }
    }


    //ScoreBoard Component
    Component{
        id:scoreBoardComp
        ScoreBoard{
onBack: mainLoader.sourceComponent=menuComp
        }
    }


    //login Component
    Component{
        id:loginComp
        LoginPage{
            onEnterUserAccess: mainLoader.sourceComponent=menuComp
            onEnterAdminAccess: mainLoader.sourceComponent=adminComp
        }
    }


    //Loader of main
    Loader{
        id:mainLoader
        anchors.fill: parent


    }

}
