#ifndef CDMATRANSPORT_H
#define CDMATRANSPORT_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>
#include <QThread>
#include <QCoreApplication>
#include <QDebug>
#include <QByteArray>
#include <QQueue>
#include <QMutex>

class CDMATransportThread;
class CDMATransport : public QObject
{
    Q_OBJECT
public:
    explicit CDMATransport(QObject *parent = 0);
    void threadLoop();
signals:
    void reciData(QByteArray recData);
private slots:
    void newTcpSocket();
    void newDataCome();

public slots:
    void initCDMATransport();
    void writeCDMAData(QByteArray data);

private:
    QTcpServer *tcpCDMASever;
    QTcpSocket *tcpCDMASocket;
    CDMATransportThread *CDMAThread;
    QQueue<QByteArray> commdQueue;
    QMutex commdLock;
    void writeData();
};

// the work thread
class CDMATransportThread : public QThread
{
    Q_OBJECT
public:
    explicit CDMATransportThread(CDMATransport* cdma,QObject *parent = 0);
    bool cdmaExit;
    void logHex(QByteArray bArry);

private:
    CDMATransport* cdmatransport;
    virtual void run();
};

#endif // CDMATRANSPORT_H
