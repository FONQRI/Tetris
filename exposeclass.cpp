#include "exposeclass.h"
#include <QDebug>
ExposeClass::ExposeClass(Users *userinfo, QObject *parent) : QObject(parent)
{
    this->userinfo=userinfo;
    //     We assign our model to the model that we created in exposemodel.h
    m_model = new ExposeModel(this);

    //query.exec ("select * from users");
    //qDebug()<<(userinfo.Username);
    for (int i = 0;i<(userinfo->numberOfUsers);i++)
    {
        // Here we create the item we want to have the data
        QStandardItem *item = new QStandardItem;
        // Here we give the data to the item
        item->setData("0", Score1Role);
        item->setData(userinfo->users[i].name, NameRole);
        item->setData(userinfo->users[i].score,ScoreRole);
        item->setData(userinfo->users[i].pass, PassRole);
        item->setData(userinfo->users[i].admin, AdminRole);
        item->setData(userinfo->users[i].date, DateRole);
        //here we add the item to the model
        m_model->appendRow(item);
    }

}

QStandardItemModel *ExposeClass::model() const
{
    return m_model;
}


void ExposeClass::clearModel()
{
    m_model->clear();
}

void ExposeClass::updateModel()
{
    m_model->clear();
    for (int i = 0;i<(userinfo->numberOfUsers);i++)
    {
        // Here we create the item we want to have the data
        QStandardItem *item = new QStandardItem;
        // Here we give the data to the item
        item->setData("0", Score1Role);
        item->setData(userinfo->users[i].name, NameRole);
        item->setData(userinfo->users[i].score,ScoreRole);
        item->setData(userinfo->users[i].pass, PassRole);
        item->setData(userinfo->users[i].admin, AdminRole);
        item->setData(userinfo->users[i].date, DateRole);
        //here we add the item to the model
        m_model->appendRow(item);
    }
}

void ExposeClass::updateSort()
{
    qDebug()<<(QString("5") > QString("4"));

    User  * temp=new User();
    if(Fild== QString("Score") && IDFild == QString("Descending"))
        for(int i=0;i<userinfo->numberOfUsers;i++)
        {
            for(int j=0;j<userinfo->numberOfUsers -1;j++)
            {
                if(userinfo->users[j].score<userinfo->users[i+1].score)
                {
                    temp->name=userinfo->users[j].name;
                    temp->score=userinfo->users[j].score;
                    temp->pass=userinfo->users[j].pass;
                    temp->admin=userinfo->users[j].admin;
                    temp->date=userinfo->users[j].date;

                    userinfo->users[j].name=userinfo->users[j +1].name;
                    userinfo->users[j].score=userinfo->users[j +1].score;
                    userinfo->users[j].pass=userinfo->users[j +1].pass;
                    userinfo->users[j].admin=userinfo->users[j +1].admin;
                    userinfo->users[j].date=userinfo->users[j +1].date;

                    userinfo->users[j +1].name=temp->name;
                    userinfo->users[j +1].score=temp->score;
                    userinfo->users[j +1].pass=temp->pass;
                    userinfo->users[j +1].admin=temp->admin;
                    userinfo->users[j +1].date=temp->date;
                }
                //delete temp;
                qDebug()<<"  S  A  ";
            }
            updateModel ();

        }
    else
        if(Fild == QString("Score") && IDFild == QString("Ascending"))
        {
            for(int i=0;i<userinfo->numberOfUsers;i++)
                for(int j=0;j<userinfo->numberOfUsers -1;j++)
                {
                    if(userinfo->users[j].score>userinfo->users[i+1].score)
                    {
                        temp->name=userinfo->users[j].name;
                        temp->score=userinfo->users[j].score;
                        temp->pass=userinfo->users[j].pass;
                        temp->admin=userinfo->users[j].admin;
                        temp->date=userinfo->users[j].date;

                        userinfo->users[j].name=userinfo->users[j +1].name;
                        userinfo->users[j].score=userinfo->users[j +1].score;
                        userinfo->users[j].pass=userinfo->users[j +1].pass;
                        userinfo->users[j].admin=userinfo->users[j +1].admin;
                        userinfo->users[j].date=userinfo->users[j +1].date;

                        userinfo->users[j +1].name=temp->name;
                        userinfo->users[j +1].score=temp->score;
                        userinfo->users[j +1].pass=temp->pass;
                        userinfo->users[j +1].admin=temp->admin;
                        userinfo->users[j +1].date=temp->date;
                    }
                    updateModel ();
                    qDebug()<<"  S  D  ";
                }
            updateModel ();

        }else
            if(Fild == "Date" && IDFild == "Descending")
                m_model->sort (5,Qt::DescendingOrder);
            else
                if(Fild == "Date" && IDFild == "Ascending")
                    m_model->sort (5,Qt::AscendingOrder);
}

void ExposeClass::deleteUser(QString name)
{
    for (int i = 0;i<(userinfo->numberOfUsers);i++)
    {
        if(userinfo->users[i].name==name)
        {
            qDebug()<<i;
            userinfo->deluser (i);
        }
    }
    updateModel ();
}

void ExposeClass::adddata(QString name , QString score, QString pass, QString admin, QString date)
{
    QStandardItem *item = new QStandardItem;
    // Here we give the data to the item

    item->setData ("0",Score1Role);
    item->setData (score,ScoreRole);
    item->setData(pass, PassRole);
    item->setData(date, DateRole);
    item->setData(admin, AdminRole);
    item->setData(name, NameRole);
    userinfo->AddUser (name,score,pass,admin,date);
    userinfo->update ();
    //here we add the item to the model
    m_model->appendRow(item);




}

QString ExposeClass::fild()
{
    return Fild;
}

void ExposeClass::setFild(QString value)
{
    Fild=value;
    emit fildChanged();
    updateSort();

}

QString ExposeClass::idFild()
{
    return IDFild;
}

void ExposeClass::setIdFild(QString value)
{
    IDFild=value;
    updateSort();
    emit idFildChanged ();
}
