#ifndef USERS_H
#define USERS_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QString>

#include "user.h"

class Users : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString usernameQml READ usernameQml WRITE setUsernameQml NOTIFY usernameQmlChanged)
public:
    explicit Users(QObject *parent = 0);
    ~Users();


    QString Username="";
    QFile *file;
    int numberOfUsers;
    User *users;

    void update();
private:

signals:
    void usernameQmlChanged();
public slots:
    int login(QString name, QString pass);
    void AddUser (QString name, QString score, QString pass, QString admin, QString date);
    void deluser(int name);
    QString findUser(QString name );


    //QString for username to show in qml
    void setUsernameQml(QString value);
    QString usernameQml();
};

#endif // USERS_H
