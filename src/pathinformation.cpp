#include "pathinformation.h"

#include <QFile>
#include <QFileInfo>
#include <QUrl>
#include <QXmlStreamReader>

Q_LOGGING_CATEGORY(PATH_INFORMATION, "run.path_information")

PathInformation::PathInformation(const QString& fileName, QObject* parent)
    : QObject(parent)
{
    open(fileName);
}

PathInformation::PathInformation(const PathInformation& other)
    : QObject(nullptr)
    , _path(other.geoPath())
{
    emit pathChanged();
}

void PathInformation::open(const QString& fileName)
{
    QList<QGeoCoordinate> path;
    QUrl gpxkmlUrl(fileName);
    QFileInfo gpxkmlFile(gpxkmlUrl.path());
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

const PathInformation& PathInformation::operator=(const PathInformation& other)
{
    _path = other._path;
    return *this;
}

PathInformation::~PathInformation() = default;
