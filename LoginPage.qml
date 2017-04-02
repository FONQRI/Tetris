import QtQuick 2.7
import QtQuick.Window 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtGraphicalEffects 1.0

Rectangle {
    anchors.fill: parent
    color:"transparent"
    id:itemLogin

    signal enterUserAccess();
    signal enterAdminAccess();

    Keys.onPressed: {
        if (event.key == 16777220 || event.key == 16777221) {
            if(usernameTextFild.text == "")
            {
                errorText.text="Enter Username"
                errorText.opacity=1
            }else if(passwordTextFild.text == "" )
            {
                errorText.text="Enter password"
                errorText.opacity=1
            }else{

                if(userInfo.login(usernameTextFild.text,passwordTextFild.text) == 1)
                {
                    enterUserAccess();
                }
                else if(userInfo.login(usernameTextFild.text,passwordTextFild.text) == 2)
                {
                    enterAdminAccess();
                }else
                {
                    errorText.text="Wrong Password or Username "
                    errorText.opacity=1
                }
            }
        }
    }

    TextField{
        id:usernameTextFild
        width: (parent.width/4)
        height: (parent.height/10)
        Material.accent:Material.Indigo
        leftPadding: 5
        rightPadding: 5
        focus: true
        font.pixelSize: 20
        placeholderText : "UserName"
        anchors.horizontalCenter: parent.horizontalCenter
        y:250

        onTextChanged:
        {

            entryButton.textColor=Material.color(Material.Blue)
            errorText.opacity=0
        }

        onFocusChanged: {
        }

    }

    TextField{
        id:passwordTextFild
        width: (parent.width/4)
        height: (parent.height/10)
        Material.accent:Material.Indigo
        echoMode : TextInput.Password
        leftPadding: 10
        rightPadding: 5
        focus: true
        font.pixelSize: 20
        placeholderText : "Password"
        anchors.horizontalCenter: parent.horizontalCenter
        y:300
        onTextChanged: {

            entryButton.textColor=Material.color(Material.Blue)
            errorText.opacity=0;
        }
        onFocusChanged: {
        }

    }


    Text{
        id:entryButton
        property string textColor: Material.color(Material.Blue)
        width: (parent.height/5)*2
        height: 50
        y:380

        text:"Enter"
        color: textColor
        horizontalAlignment:Text.AlignHCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 16
        MouseArea{
            anchors.fill: parent
            onClicked: {
                if(usernameTextFild.text == "")
                {
                    errorText.text="Enter Username"
                    errorText.opacity=1
                }else if(passwordTextFild.text == "" )
                {
                    errorText.text="Enter password"
                    errorText.opacity=1
                }else{

                    if(userInfo.login(usernameTextFild.text,passwordTextFild.text) == 1)
                    {
                        enterUserAccess();
                    }
                    else if(userInfo.login(usernameTextFild.text,passwordTextFild.text) == 2)
                    {
                        enterAdminAccess();
                    }else
                    {
                        errorText.text="Wrong Password or Username "
                        errorText.opacity=1
                    }
                }
            }



        }

    }
    Text{
        id:guestButton
        property string textColor: Material.color(Material.Blue)
        width: (parent.height/5)*2
        height: 50
        y:420
        text:"Enter as Guest"
        color: textColor
        horizontalAlignment:Text.AlignHCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 16

        MouseArea{
            anchors.fill: parent
            onClicked: {
                userInfo.usernameQml="Guest"
                enterUserAccess();
            }
        }


    }
    Text{
        id:errorText
        property string textColor: Material.color(Material.Red)
        width: (parent.height/5)*2
        height: 50
        y:250
        text:"Wrong Password or Username "
        color: textColor
        opacity: 0
        horizontalAlignment:Text.AlignHCenter
        anchors.horizontalCenter: parent.horizontalCenter



    }
}
