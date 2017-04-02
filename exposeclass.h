#ifndef EXPOSECLASS_H
#define EXPOSECLASS_H

// We include our model here
#include <exposemodel.h>

#include <QObject>
#include <QStandardItemModel>
#include <QTimer>
#include "users.h"


class ExposeClass : public QObject
{
    Q_OBJECT

    // This is the model that we want to expose to QML
    Q_PROPERTY(QString fild READ fild WRITE setFild NOTIFY fildChanged)
    Q_PROPERTY(QString idFild READ idFild WRITE setIdFild NOTIFY idFildChanged)
    QStandardItemModel *m_model;


public:
    // Our data enum containing our roles
    enum DataRoles {
        ScoreRole ,
        Score1Role ,
        Score2Role ,
        PassRole,
        DateRole,
        AdminRole,
        NameRole,
    };

    explicit ExposeClass(Users *userinfo, QObject *parent = 0);

    // The getter for our model
    QStandardItemModel *model() const;

signals:
    void fildChanged();
    void idFildChanged();
public slots:
    // The names explain themselves
    void clearModel();
    void updateModel();
    void updateSort();
    void deleteUser(QString name);
    void adddata(QString name , QString score, QString pass, QString admin, QString date);

    QString fild();
    void setFild(QString value);
    QString idFild();
    void setIdFild(QString value);
private:
    QString Fild;
    QString IDFild;
    Users *userinfo;

};

#endif // EXPOSECLASS_H
