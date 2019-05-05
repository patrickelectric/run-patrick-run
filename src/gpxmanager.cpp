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

void GpxManager::open(const QString& fileNames)
{
    open(fileNames.split("\n"));
}

void GpxManager::open(const QStringList& fileNames)
{
    _paths.clear();
    _paths_ptr.clear();

    for(const auto& fileName : fileNames) {
        _paths.append(PathInformation{fileName, this});
        _paths_ptr.append(QVariant::fromValue(&_paths.last()));
    }

    emit pathsChanged();
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
