#include "core/appinitializer.h"
#include "qguiapplication.h"
#include "qqmlapplicationengine.h"

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.loadFromModule("filesystem-client", "Main");

    AppInitializer appInitializer;
    appInitializer.setupContext(engine.rootContext());

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    return app.exec();
}
