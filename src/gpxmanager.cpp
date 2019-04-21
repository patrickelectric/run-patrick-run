#include "gpxmanager.h"

#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QQmlEngine>
#include <QUrl>
#include <QXmlStreamReader>

Q_LOGGING_CATEGORY(GPX_MANAGER, "run.gpx_manager")

GpxManager::GpxManager() = default;

void GpxManager::open(const QUrl& fileName)
{
    QList<QGeoCoordinate> path;
    //QString gpxkmlPath(file);
    QFileInfo gpxkmlFile(fileName.path());
    QFile file(gpxkmlFile.absoluteFilePath());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "can't open file";
        return;
    }

    QXmlStreamReader xmlReader(&file);
    //Parse the XML until we reach end of it
    while(!xmlReader.atEnd()) {
        if(xmlReader.tokenType() == QXmlStreamReader::StartDocument) {
            xmlReader.readNext();
            continue;
        }
        if (xmlReader.tokenType() == QXmlStreamReader::StartElement) {
            if (xmlReader.name() == "trkpt") {
                path.append({xmlReader.attributes().value("lat").toDouble(), xmlReader.attributes().value("lon").toDouble()});
            } else if (xmlReader.name() == "heartrate") {
                //qDebug() << xmlReader.readElementText();
            } else if (xmlReader.name() == "time") {
                //qDebug() << xmlReader.readElementText();
            } else if (xmlReader.name() == "ele") {
                //qDebug() << xmlReader.readElementText();
            }
        }
        xmlReader.readNext();
    }

    _path.setPath(path);
    emit pathChanged();
}

QObject* GpxManager::qmlSingletonRegister(QQmlEngine* engine, QJSEngine* scriptEngine)
{
    Q_UNUSED(scriptEngine)

    engine->setObjectOwnership(self(), QQmlEngine::CppOwnership);

    return self();
}

GpxManager* GpxManager::self()
{
    static GpxManager self;
    return &self;
}
