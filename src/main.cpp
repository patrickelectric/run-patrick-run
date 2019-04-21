#include <QApplication>

#include <QQmlApplicationEngine>
#include <QtQml>
#include <QUrl>
#include <QColor>

#include "gpxmanager.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    qmlRegisterSingletonType<GpxManager>("GpxManager", 1, 0, "GpxManager", GpxManager::qmlSingletonRegister);

    QQmlApplicationEngine engine;

    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    if (engine.rootObjects().isEmpty()) {
        return -77;
    }

    return app.exec();
}
