#ifndef DATAEXPLORERVIEWMODEL
#define DATAEXPLORERVIEWMODEL

#include <QObject>

static int _counter;

class DataExplorerViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject* model READ model NOTIFY modelChanged)

public:
    explicit DataExplorerViewModel(QObject* parent = nullptr);

    QObject* model() { return _counter++ == 0 ? _fileExplorerModel : _clientExplorerModel; }

signals:
    void modelChanged();

private:
    QObject* _fileExplorerModel;
    QObject* _clientExplorerModel;
};

#endif // DATAEXPLORERVIEWMODEL
