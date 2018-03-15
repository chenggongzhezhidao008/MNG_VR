#ifndef RVR_ZMQ_WORKER_H
#define RVR_ZMQ_WORKER_H
#include <QCoreApplication>
#include <QByteArray>
#include <QThread>
#include <QObject>
#include <QQueue>
#include <QMutex>
#include "zmq.h"
#include "time.h"

class Zmq_Worker_Thread;

class RVR_Zmq_Worker : public QObject
{
    Q_OBJECT
public:
    explicit RVR_Zmq_Worker(QObject *parent = 0);
    void loopZmq();
signals:
    void newData(QByteArray bytes);

public slots:
    int  initZmq();
    int  setPort(QString ip = "",int reciPort  = 0,int sendPort = 0);
    void writezmq(QByteArray barr);
    int  exit();

private:
    void * pCtx;
    void * sCtx;
    void * pSocket;
    void * sSocket;
    Zmq_Worker_Thread *workerThread;
    QQueue<QByteArray> commdQueue;
    QMutex Rlock;
    int  readData();
    bool writeData();

};

class Zmq_Worker_Thread : public QThread
{
    Q_OBJECT
public:
    Zmq_Worker_Thread(RVR_Zmq_Worker *zmqWork,QObject *parent = 0);
    bool exitFlag;
private:
    RVR_Zmq_Worker *worker;
    virtual void run();
};
#endif // RVR_ZMQ_WORKER_H
