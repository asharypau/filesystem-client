#include "core/appinitializer.h"
#include "qguiapplication.h"
#include "qqmlapplicationengine.h"

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    AppInitializer appInitializer;
    appInitializer.setupContext(engine.rootContext());

    engine.loadFromModule("filesystem-client", "Main");

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    return app.exec();
}
