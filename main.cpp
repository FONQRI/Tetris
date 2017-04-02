#include <QGuiApplication>
#include <QQuickStyle>
#include <QQmlApplicationEngine>
#include <QQmlContext>


#include "users.h"
#include "game.h"
#include "user.h"

Game *game;

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Material");

    //

    QQmlApplicationEngine engine;


    game = new Game(&engine);

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));



    return app.exec();
}
