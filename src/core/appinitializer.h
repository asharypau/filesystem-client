#ifndef APPINITIALIZER_H
#define APPINITIALIZER_H

#include "../viewmodels/connectdialogviewmodel.h"
#include "../viewmodels/dataexplorerviewmodel.h"
#include "../viewmodels/mainviewmodel.h"
#include "dispatcher.h"
#include "qqmlcontext.h"
#include "sessionmanager.h"

class AppInitializer
{
public:
    explicit AppInitializer();

    void setupContext(QQmlContext* context);

private:
    Dispatcher _dispatcher;
    SessionManager _sessionManager;

    MainViewModel* _mainViewModel;
    ConnectDialogViewModel* _connectDialogViewModel;
    DataExplorerViewModel* _dataExplorerViewModel;
};

#endif // APPINITIALIZER_H
