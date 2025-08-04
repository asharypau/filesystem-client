#include "appinitializer.h"

AppInitializer::AppInitializer()
    : _dispatcher()
    , _sessionManager(&_dispatcher)
    , _mainViewModel(nullptr)
    , _connectDialogViewModel(nullptr)
    , _dataExplorerViewModel(nullptr)
{
}

void AppInitializer::setupContext(QQmlContext* context)
{
    _mainViewModel = new MainViewModel(context);
    context->setContextProperty("mainViewModel", _mainViewModel);

    _connectDialogViewModel = new ConnectDialogViewModel(&_sessionManager, _mainViewModel);
    context->setContextProperty("connectDialogViewModel", _connectDialogViewModel);

    _dataExplorerViewModel = new DataExplorerViewModel(_mainViewModel);
    context->setContextProperty("dataExplorerViewModel", _dataExplorerViewModel);
}
