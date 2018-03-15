#ifndef RVR_SERIALWRITE_H
#define RVR_SERIALWRITE_H

#include <QObject>
#include <QThread>
#include <QCoreApplication>
#include <QQueue>
#include <QMutex>
#include <QByteArray>

class RVR_SerialWorkThread;
class RVR_serialwrite : public QObject
{
    Q_OBJECT
public:
    explicit RVR_serialwrite(QObject *parent = 0);
    void threadLoop();
    void exit();
private:
    RVR_SerialWorkThread *R_thread;
    QQueue<QByteArray> messageQueue;
    QMutex R_lock;
signals:
    void send_data(QByteArray commd,int length);

public slots:
    void writeSerial(QByteArray bytes);
};
//==========================================
class RVR_SerialWorkThread : public QThread
{
    Q_OBJECT
public:
    explicit RVR_SerialWorkThread(RVR_serialwrite* pWork,QObject *parent = 0);
    bool R_wExit;
    void logHex(QByteArray bArry);
private:
    RVR_serialwrite* write_Work;
    virtual void run();
};

#endif // RVR_SERIALWRITE_H
