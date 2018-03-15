#include "setupthread.h"


SetupThread::SetupThread(QObject *parent) :
    QObject(parent)
{
    cdma = new CDMATransport();
    connect(this,SIGNAL(setup()),cdma,SLOT(initCDMATransport()),Qt::QueuedConnection);
    emit setup();
    connect(cdma,SIGNAL(reciData(QByteArray)),this,SIGNAL(reciMessage(QByteArray)));
    connect(this,SIGNAL(writeCDMA(QByteArray)),cdma,SLOT(writeCDMAData(QByteArray)),Qt::QueuedConnection);
}



