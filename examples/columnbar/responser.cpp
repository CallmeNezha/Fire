#include "responser.h"
#include <QMessageBox>

Responser::Responser(QObject *parent) : QObject(parent)
{

}

void Responser::onColBarClicked(int index)
{
    QMessageBox::information(Q_NULLPTR, "", QString("Column Bar button %1 clicked").arg(index));
}
