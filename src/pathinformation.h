#pragma once

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
    QGeoPath geoPath() const { return _path; };

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

    Q_INVOKABLE QGeoCoordinate center() { return _path.center(); };
    Q_PROPERTY(QGeoCoordinate center READ center NOTIFY centerChanged)

    Q_INVOKABLE int loops() { return _loops; };
    Q_PROPERTY(int loops READ loops NOTIFY loopsChanged)

    /**
     * @brief Count the number of loops in trajectory
     *
     */
    void updateLoopCounter();

    const PathInformation& operator=(const PathInformation& other);

    ~PathInformation();

signals:
    void centerChanged();
    void loopsChanged();
    void pathChanged();

private:
    int _loops;
    QGeoPath _path;
};

Q_DECLARE_METATYPE(PathInformation*)
