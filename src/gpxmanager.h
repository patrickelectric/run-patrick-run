#pragma once

#include <QGeoPath>
#include <QLoggingCategory>

#include "pathinformation.h"

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

    /**
     * @brief Open list of files
     *
     * @param fileNames
     */
    Q_INVOKABLE void open(const QString& fileNames);
    Q_INVOKABLE void open(const QStringList& fileNames);

    /**
     * @brief Return a pointer of this singleton to the qml register function
     *
     * @param engine
     * @param scriptEngine
     * @return QObject*
     */
    static QObject* qmlSingletonRegister(QQmlEngine* engine, QJSEngine* scriptEngine);

    Q_PROPERTY(QVariantList paths READ paths NOTIFY pathsChanged)

    Q_INVOKABLE QVariantList paths() {
        return  _paths_ptr;
    };

signals:
    void pathsChanged();

private:
    QList<PathInformation> _paths;
    QVariantList _paths_ptr;
    /**
     * @brief Construct a new Network Manager object
     *
     */
    GpxManager();
};
