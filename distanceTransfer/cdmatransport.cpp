#include "cdmatransport.h"


CDMATransport::CDMATransport(QObject *parent) :
    QObject(parent)
{
    tcpCDMASever = NULL;
    tcpCDMASocket = NULL;
    CDMAThread  = new CDMATransportThread(this);
    moveToThread(CDMAThread);
    CDMAThread->start();
}

void CDMATransport::threadLoop()
{
    writeData();
}

void CDMATransport::initCDMATransport()
{
    qDebug()<<"CDMA init succeed.";
    tcpCDMASever = new QTcpServer();
    tcpCDMASever->listen(QHostAddress::Any,2016);
    connect(tcpCDMASever,SIGNAL(newConnection()),this,SLOT(newTcpSocket()));
}

void CDMATransport::writeCDMAData(QByteArray data)
{
    commdLock.lock();
    if(commdQueue.length()>100)
    {
        commdQueue.clear();
    }
    commdQueue.enqueue(data);
    commdLock.unlock();
    return ;
}

void CDMATransport::writeData()
{
    commdLock.lock();
    if((commdQueue.length() != 0)&&(tcpCDMASocket))
    {
        if(tcpCDMASocket->isOpen())
        {
            QByteArray byte = commdQueue.dequeue();
            tcpCDMASocket->write(byte);
        }
        else
        {
            qDebug()<<"tcp socket is not open";
        }
    }
    commdLock.unlock();
    return ;
}

void CDMATransport::newTcpSocket()
{
    qDebug()<<"Have new connection come.";
    tcpCDMASocket = tcpCDMASever->nextPendingConnection();
    connect(tcpCDMASocket,SIGNAL(readyRead()),this,SLOT(newDataCome()));
}

void CDMATransport::newDataCome()
{
    qDebug()<<"have new datas come.";
    QByteArray newData = tcpCDMASocket->readAll();
//    qDebug()<<"remote data:"<<newData.toHex();
    emit reciData(newData);
}

//cdma  Transport Thread
CDMATransportThread::CDMATransportThread(CDMATransport *cdma, QObject *)
{
    cdmatransport = cdma;
    cdmaExit = false;
}

void CDMATransportThread::run()
{
    qDebug()<<"TmSerialWorkThread :"<<currentThreadId();
    while (!cdmaExit) {
        QCoreApplication::processEvents(QEventLoop::AllEvents,200);
        msleep(30);
        cdmatransport->threadLoop();
    }
}
