import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.0

Item {
    visible: true
    anchors.fill: parent
    signal back();
    Rectangle{
        id:header
        height: 50
        width: parent.width
        color:Material.color(Material.Blue)
        z:0
        Text {
            id: searchText
            text: qsTr("مرتب سازی بر اساس :")
            anchors.right: parent.right
            anchors.verticalCenter: header.verticalCenter
            rightPadding: 63
            leftPadding: 20
        }

        ComboBox{
            id:searchCombo
            anchors.right: searchText.left
            width: 200
            height: 50
            textRole: "key"
            Component.onCompleted: ExposeClass.fild=comboModel.get(currentIndex).key
            model: ListModel {
                id:comboModel
                ListElement { key: "Score"}
                ListElement { key: "Date" }
            }
            onCurrentIndexChanged: ExposeClass.fild=comboModel.get(currentIndex).key

        }


        ComboBox{
            id:deinCombo
            anchors.right: searchCombo.left
            width: 200
            height: 50
            textRole: "key"
            Component.onCompleted: ExposeClass.idFild=deinModel.get(currentIndex).key
            model: ListModel {
                id:deinModel
                ListElement { key: "Ascending"}
                ListElement { key: "Descending" }
            }
            onCurrentIndexChanged: ExposeClass.idFild=deinModel.get(currentIndex).key

        }

    }

    ListView {
        width:parent.width
        height: parent.height-100
        anchors.top:header.bottom
        model: ExposeModel // Our C++ model
        z:-1
        delegate: ItemDelegate {
            // text: nameRole + scoreRole  // Defined in exposemodel.h
            width: parent.width
            Row{
                width: parent.width

                Rectangle{
                    width: parent.width/5
                    height: 50
                    color:"yellow"
                    Text {
                        text: nameRole
                        anchors.centerIn: parent
                    }
                }

                Rectangle{
                    width: parent.width/5
                    height: 50
                    color:"red"
                    Text {
                        text: scoreRole
                        anchors.centerIn: parent
                    }
                }

                Rectangle{
                    width: parent.width/5
                    height: 50
                    color:"blue"
                    Text {
                        text: passRole
                        anchors.centerIn: parent
                    }
                }

                Rectangle{
                    width: parent.width/5
                    height: 50
                    color:"green"
                    Text {
                        text: adminRole
                        anchors.centerIn: parent
                    }
                }

                Rectangle{
                    width: parent.width/5
                    height: 50
                    color:"white"
                    Text {
                        text: dateRole
                        anchors.centerIn: parent
                    }
                }
            }


        }
    }
    Button{
        width:100
        height: 50
        text:"back"
        anchors{
            right:parent.right
            bottom: parent.bottom

        }
        onClicked: back();
    }

}
