#include "appinitializer.h"

AppInitializer::AppInitializer()
    : _sessionManager()
    , _explorerDataProvider(&_sessionManager)
    , _mainViewModel(nullptr)
    , _connectDialogViewModel(nullptr)
    , _leftDataExplorerViewModel(nullptr)
    , _rightDataExplorerViewModel(nullptr)
    , _breadcrumbViewModel(nullptr)
{
}

void AppInitializer::setupContext(QQmlContext* context)
{
    _mainViewModel = new MainViewModel(context);
    context->setContextProperty("mainViewModel", _mainViewModel);

    _connectDialogViewModel = new ConnectDialogViewModel(&_sessionManager, _mainViewModel);
    context->setContextProperty("connectDialogViewModel", _connectDialogViewModel);

    _leftDataExplorerViewModel = new DataExplorerViewModel(DataExplorerViewModel::ViewState::FileInfos,
                                                           &_explorerDataProvider,
                                                           _mainViewModel);
    context->setContextProperty("leftDataExplorerViewModel", _leftDataExplorerViewModel);

    _rightDataExplorerViewModel = new DataExplorerViewModel(DataExplorerViewModel::ViewState::Clients,
                                                            &_explorerDataProvider,
                                                            _mainViewModel);
    context->setContextProperty("rightDataExplorerViewModel", _rightDataExplorerViewModel);

    _breadcrumbViewModel = new BreadcrumbViewModel(_mainViewModel);
    context->setContextProperty("breadcrumbViewModel", _breadcrumbViewModel);
}
