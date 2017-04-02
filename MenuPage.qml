import QtQuick 2.7
import QtQuick.Controls.Material 2.0
import QtQuick.Controls 2.0
Item {
    anchors.fill: parent
    signal scoreBoard()
    signal startGame()
    Button{
        width :parent.width/5
        height: 70
        anchors.horizontalCenter: parent.horizontalCenter
        y:200
        text:"Start"
        Material.foreground: "black"

        Material.theme: Material.Light
        Material.background:Material.LightBlue

        onClicked:  {

            startGame()
            myGame.start();
        }

    }

    Button{
        width :parent.width/5
        height: 70
        anchors.horizontalCenter: parent.horizontalCenter
        y:280
        text:"Score Board"
        Material.foreground: "black"
        Material.theme: Material.Light
        Material.background:Material.LightBlue
        onClicked: scoreBoard()
    }


    Button{
        width :parent.width/5
        height: 70
        anchors.horizontalCenter: parent.horizontalCenter
        y:360
        text:"Exit"
        Material.foreground: "black"
        Material.theme: Material.Light
        Material.background:Material.LightBlue
        onClicked: Qt.quit()
    }

    Rectangle{
        width: showUsername.width + 50
        height: 50
        radius: 10
        anchors{

            rightMargin: 20
            right: parent.right
            top: parent.top
            topMargin:20
        }
        color:Material.color( Material.Teal)

        Text {
            id: showUsername
            text: userInfo.usernameQml

            anchors.centerIn: parent
            font.pixelSize: 20
            color:"black"
        }
    }
}
