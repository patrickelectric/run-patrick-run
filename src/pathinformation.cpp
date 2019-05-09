#include "pathinformation.h"

#include <QFile>
#include <QFileInfo>
#include <QUrl>
#include <QXmlStreamReader>

#include <math.h>

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

    _name = gpxkmlFile.baseName();
    emit nameChanged();

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
    emit centerChanged();
    emit pathChanged();
    updateLoopCounter();
}

void PathInformation::updateLoopCounter()
{
    /**
     * @brief This can be done via the 'Winding number', 'Gauss map' or 'Total curvature' methods
     *  the one used here is the first one
     */

    const auto& path = _path.path();
    auto lastPoint = path.first();
    double totalAngle = 0;
    auto center = _path.center();
    for(const auto& point : path) {
        // https://en.wikipedia.org/wiki/Law_of_cosines
        // gamma = \arccos{\frac {a^{2}+b^{2}-c^{2}}{2ab}}
        double a = center.distanceTo(lastPoint);// hypot(point.latitude() - center.latitude(), point.longitude() - center.longitude());
        double b = center.distanceTo(point);//hypot(lastPoint.latitude() - center.latitude(), lastPoint.longitude() - center.longitude());
        double c = lastPoint.distanceTo(point);//hypot(lastPoint.latitude() - point.latitude(), lastPoint.longitude() - point.longitude());
        double gamma = acos((pow(a, 2) + pow(b, 2) - pow(c, 2))/(2.0f*a*b));
        totalAngle += gamma;
        lastPoint = point;
    }
    _loops = floor(totalAngle/(2*M_PI));

}

const PathInformation& PathInformation::operator=(const PathInformation& other)
{
    _path = other._path;
    return *this;
}

PathInformation::~PathInformation() = default;
