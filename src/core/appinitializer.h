#ifndef APPINITIALIZER_H
#define APPINITIALIZER_H

#include "../viewmodels/connectdialogviewmodel.h"
#include "../viewmodels/dataexplorerviewmodel.h"
#include "../viewmodels/mainviewmodel.h"
#include "qqmlcontext.h"

class AppInitializer
{
public:
    explicit AppInitializer();

    void setupContext(QQmlContext* context);

private:
    MainViewModel* _mainViewModel;
    ConnectDialogViewModel* _connectDialogViewModel;
    DataExplorerViewModel* _dataExplorerViewModel;
};

#endif // APPINITIALIZER_H
