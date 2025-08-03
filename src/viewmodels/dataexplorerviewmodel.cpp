#include "dataexplorerviewmodel.h"
#include "../models/fileexplorermodel.h"

DataExplorerViewModel::DataExplorerViewModel(QObject *parent)
    : QObject(parent)
    , _model(new FileExplorerModel(this))
{
}
