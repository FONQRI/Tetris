#include "users.h"
#include <QDebug>
#include <time.h>
#include "exposeclass.h"
Users::Users(QObject *parent) : QObject(parent)
{
    users=new User[10000];
    file = new QFile("data.txt");
    if (file->open(QIODevice::ReadWrite | QIODevice::Text))
    {

        QTextStream s (file);
        int lines=0;
        s >> lines;
        numberOfUsers = lines;
        for (int i = 0;i<lines;++i)
        {

            QString name;
            QString pass;
            s >> name;
            s >>  pass;
            users[i].name = name;
            users[i].score = "0";
            users[i].pass = pass;
            users[i].admin = i==0?"1":"0";
            users[i].date = "12/7/1394";

        }
    }
}

Users::~Users()
{
    update ();
}

void Users::update()
{
    qDebug () << "update";
    file = new QFile ("data.txt");
    if (file->open(QIODevice::WriteOnly | QIODevice::Text))
    {

        QTextStream s (file);
        s << numberOfUsers;
        for (int i = 0;i<numberOfUsers;++i)
        {
            s << "\n"
              << users[i].name
              << " "
              << users[i].score
              << " "
              << users[i].pass
              << " "
              << users[i].admin
              << " "
              << users[i].date
                 ;
        }
    }
}



int Users::login(QString name, QString pass)
{


    for (int i =0  ;i<numberOfUsers;++i)
        if (users[i].name == name && users[i].pass==pass && users[i].admin == "1")
            return 2;

    for (int i =0 ;i<numberOfUsers;++i)
        if (users[i].name == name && users[i].pass==pass)
        {
            setUsernameQml (name);
            return 1;
        }



    return 0;

}

void Users::AddUser(QString name, QString score, QString pass, QString admin, QString date)
{
    if( name != "" &&  score != ""&& pass != ""&& admin != ""&& date != "")
    {
        users[numberOfUsers].name = name;
        users[numberOfUsers].score = score;
        users[numberOfUsers].pass = pass;
        users[numberOfUsers].admin = admin;
        users[numberOfUsers].date = date;
        numberOfUsers++;
    }
}

void Users::deluser(int name)
{



    users[name].name = "";
    for (int i =0  ;i<numberOfUsers;++i)
    {
        if( users[numberOfUsers].name == "" )
        {
            qDebug()<<users[i].name <<"   +1  "<<users[i + 1].name;

            users[i].name = users[i + 1].name;
            users[i].score = users[i + 1].score;
            users[i].pass = users[i + 1].pass;
            users[i].admin = users[i + 1].admin;
            users[i].date = users[i + 1].date;
            users[i + 1].name="";

        }

    }
    update ();
    numberOfUsers--;



}

QString Users::findUser(QString name)
{
    for (int i =0  ;i<numberOfUsers;++i)
        if (users[i].name == name)
            return users[i].pass;
    return QString("not found");
}

void Users::setUsernameQml(QString value)
{
    Username = value;

    emit usernameQmlChanged ();
}

QString Users::usernameQml()
{
    return Username;
}



