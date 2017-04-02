import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
Item {
    anchors.fill: parent
    signal back()



    ListView {
        anchors.fill: parent
        model: ExposeModel // Our C++ model

        delegate: ItemDelegate {
            width: parent.width
            Row{
                width: parent.width
                spacing: 10
                topPadding: 10
                leftPadding: 10
                Rectangle{
                    width: (parent.width - 130 )/5
                    height: 50
                    border.color:"black"

                    color:Material.color(Material.Blue)
                    Text {
                        text: nameRole
                        anchors.centerIn: parent
                    }
                }

                Rectangle{
                    width: (parent.width - 130 )/5
                    border.color:"black"

                    height: 50
                    color:Material.color(Material.Blue)
                    Text {
                        text: scoreRole
                        anchors.centerIn: parent
                    }
                }

                Rectangle{
                    width: (parent.width - 130 )/5
                    border.color:"black"

                    height: 50
                    color:Material.color(Material.Blue)
                    Text {
                        text: passRole
                        anchors.centerIn: parent
                    }
                }

                Rectangle{
                    width: (parent.width - 130 )/5
                    border.color:"black"

                    height: 50
                    color:Material.color(Material.Blue)
                    Text {
                        text: adminRole
                        anchors.centerIn: parent
                    }
                }

                Rectangle{
                    width: (parent.width - 130 )/5
                    border.color:"black"

                    height: 50
                    color:Material.color(Material.Blue)
                    Text {
                        text: dateRole
                        anchors.centerIn: parent
                    }
                }

                Button{
                    width:50
                    height: 50
                    text:"X"
                    Material.background: Material.Red
                    Material.theme:Material.Light
                    onClicked: ExposeClass.deleteUser(nameRole)
                }
            }


        }
    }


    Row {
        id: row
        width  :parent.width
        spacing: 10
        leftPadding: 10
        anchors{
            bottom: parent.bottom
            left: parent.left
        }
        TextField {
            id: nameField
            placeholderText: "Enter Name"
            width: (parent.width - 90)/8
        }
        TextField {
            id: scoreField
            placeholderText: "Enter Score"
            width: (parent.width - 90)/8
        }
        TextField {
            id: passField
            placeholderText: "Enter Password"
            width: (parent.width - 90)/8
        }
        TextField {
            id: adminField
            placeholderText: "Enter Admin"
            width: (parent.width - 90)/8
        }


        TextField {
            id: dateField
            placeholderText: "Enter Date"
            width: (parent.width - 90)/8
        }


        Button {
            id: addButton
            text: "Add"
            width: (parent.width - 90)/8

            onClicked: {
                // Here we add the nameField's text to our model
                // Via the C++ function addNameToModel
                // If the nameField's text is empty it won't add it to model

                if (nameField.text != "")
                {
                    ExposeClass.adddata(nameField.text,scoreField.text,passField.text,adminField.text,dateField.text)
                }

                // Here we clear the nameField's text
                //nameField.clear()

                // Here we give the focus back to nameField
                //nameField.focus = true
            }
        }

        Button {
            id: clearButton
            text: "Clear"
            width: (parent.width - 90)/8

            onClicked: {
                // Here we clear our model
                ExposeClass.clearModel()

                // Here we give the focus back to nameField
                nameField.focus = true
            }
        }

        Button {
            id: exitButton
            text: "Back"
            width: (parent.width - 90)/8

            onClicked: {
               back();
            }
        }
    }
}
