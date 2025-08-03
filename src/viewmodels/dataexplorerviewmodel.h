#ifndef DATAEXPLORERVIEWMODEL
#define DATAEXPLORERVIEWMODEL

#include <QObject>

class DataExplorerViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject* model READ model NOTIFY modelChanged)

public:
    explicit DataExplorerViewModel(QObject* parent = nullptr);

    QObject* model() { return _model; }

signals:
    void modelChanged();

private:
    QObject* _model;
};

#endif // DATAEXPLORERVIEWMODEL
