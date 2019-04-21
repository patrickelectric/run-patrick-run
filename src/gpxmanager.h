#pragma once

#include <QGeoPath>
#include <QLoggingCategory>

class QJSEngine;
class QQmlEngine;

Q_DECLARE_LOGGING_CATEGORY(GPX_MANAGER)

/**
 * @brief Manage the project GpxManager
 *
 */
class GpxManager : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Return GpxManager pointer
     *
     * @return GpxManager*
     */
    static GpxManager* self();

    Q_INVOKABLE void open(const QUrl& fileName);
    /**
     * @brief Return a pointer of this singleton to the qml register function
     *
     * @param engine
     * @param scriptEngine
     * @return QObject*
     */
    static QObject* qmlSingletonRegister(QQmlEngine* engine, QJSEngine* scriptEngine);

    QGeoPath geoPath() { return _path; };
    Q_PROPERTY(QVariantList path READ path NOTIFY pathChanged)

    Q_INVOKABLE QVariantList path() {
        QVariantList b;
        for(auto i : geoPath().path()) {
            b.append(QVariant::fromValue(i));
        }
        return b;
    };

signals:
    void pathChanged();

private:
    /**
     * @brief Construct a new Network Manager object
     *
     */
    GpxManager();

    QGeoPath _path;
};
