#pragma once

#include <QDateTime>
#include <QGeoPath>
#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(PATH_INFORMATION)

/**
 * @brief Manage the project GpxManager
 *
 */
class PathInformation : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Construct a new Path Information Object
     *
     */
    PathInformation(const QString& fileName, QObject* parent = nullptr);
    PathInformation(const PathInformation& other);

    /**
     * @brief Open a file and extract useful information
     *
     */
    void open(const QString& fileName);

    /**
     * @brief Get path with QGeoPath type
     *
     * @return QGeoPath
     */
    QGeoPath geoPath() const { return _pathContent.path; };

    /**
     * @brief Get path in a QML friendly way
     *
     * @return QVariantList
     */
    Q_INVOKABLE QVariantList path() {
        // This is the only way that I know to share paths with QML
        QVariantList variantList;
        for(const auto& i : geoPath().path()) {
            variantList.append(QVariant::fromValue(i));
        }
        return variantList;
    };
    Q_PROPERTY(QVariantList path READ path NOTIFY pathChanged)

    Q_INVOKABLE QGeoCoordinate center() { return _pathContent.path.center(); };
    Q_PROPERTY(QGeoCoordinate center READ center NOTIFY pathChanged)

    Q_INVOKABLE int loops() { return _loops; };
    Q_PROPERTY(int loops READ loops NOTIFY loopsChanged)

    Q_INVOKABLE QString name() { return _name; };
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)

    Q_INVOKABLE QVariantList timeStamps() {
        QVariantList variantList;
        for(const auto& i : _pathContent.timeStamps) {
            variantList.append(QVariant::fromValue(i));
        }
        return variantList;
    };
    Q_PROPERTY(QVariantList timeStamps READ timeStamps NOTIFY pathChanged)

    /**
     * @brief Count the number of loops in trajectory
     *
     */
    void updateLoopCounter();

    const PathInformation& operator=(const PathInformation& other);

    ~PathInformation();

signals:
    void loopsChanged();
    void nameChanged();
    void pathChanged();

private:
    struct PathContent {
        QGeoPath path;
        QVector<double> elevations;
        QVector<double> heartRates;
        QVector<QDateTime> timeStamps;

        void sync() {
            if(path.size() == 0) { return; };
            while(path.size() > elevations.size() && elevations.size()) elevations.append(elevations.last());
            while(path.size() > heartRates.size() && heartRates.size()) heartRates.append(heartRates.last());
            while(path.size() > timeStamps.size() && timeStamps.size()) timeStamps.append(timeStamps.last());
        }
    } _pathContent;

    int _loops;
    QString _name;
};

Q_DECLARE_METATYPE(PathInformation*)
