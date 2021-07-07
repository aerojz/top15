#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include <qqmlcontext.h>

#include "engtop.h"

int main(int argc, char ** argv)
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine qmlEngine;

    qRegisterMetaType<Session::RESULT>("Session::RESULT");
    qRegisterMetaType<CalcFreqWord::AllRatingWord>("CalcFreqWord::AllRatingWord");

    EngTop engTop;

    QQmlContext *context = qmlEngine.rootContext();
    context->setContextProperty("engTop", &engTop);
    qmlEngine.load(QUrl("qrc:/view.qml"));

    return app.exec();
}

