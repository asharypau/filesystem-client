#ifndef APPINITIALIZER_H
#define APPINITIALIZER_H

#include "../services/explorerdataprovider.h"
#include "../viewmodels/breadcrumbviewmodel.h"
#include "../viewmodels/connectdialogviewmodel.h"
#include "../viewmodels/dataexplorerviewmodel.h"
#include "../viewmodels/mainviewmodel.h"
#include "qqmlcontext.h"
#include "sessionmanager.h"

class AppInitializer
{
public:
    explicit AppInitializer();

    void setupContext(QQmlContext* context);

private:
    SessionManager _sessionManager;
    ExplorerDataProvider _explorerDataProvider;

    MainViewModel* _mainViewModel;
    ConnectDialogViewModel* _connectDialogViewModel;
    DataExplorerViewModel* _leftDataExplorerViewModel;
    DataExplorerViewModel* _rightDataExplorerViewModel;
    BreadcrumbViewModel* _breadcrumbViewModel;
};

#endif // APPINITIALIZER_H
