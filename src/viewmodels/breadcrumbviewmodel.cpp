#include "breadcrumbviewmodel.h"

BreadcrumbViewModel::BreadcrumbViewModel(QObject* parent)
    : QObject(parent)
{
    _pathItems.append("part1");
    _pathItems.append("part2");
    _pathItems.append("part3");
    _pathItems.append("part4");
    _pathItems.append("part5");
    _pathItems.append("part6");
    _pathItems.append("part7");
}
