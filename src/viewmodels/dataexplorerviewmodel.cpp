#include "dataexplorerviewmodel.h"
#include "../models/clientexplorermodel.h"
#include "../models/fileexplorermodel.h"

DataExplorerViewModel::DataExplorerViewModel(QObject *parent)
    : QObject(parent)
    , _fileExplorerModel(new FileExplorerModel(this))
    , _clientExplorerModel(new ClientExplorerModel(this))
{
}
