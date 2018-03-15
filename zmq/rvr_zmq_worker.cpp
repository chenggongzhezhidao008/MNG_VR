#include <QDebug>
#include "rvr_zmq_worker.h"
Zmq_Worker_Thread::Zmq_Worker_Thread(RVR_Zmq_Worker *zmqWork,QObject *)
{
    worker = zmqWork;
    exitFlag = false;
}

void Zmq_Worker_Thread::run()
{
    qDebug()<<"zmq thread id:"<<currentThreadId();
    while (!exitFlag) {
        QCoreApplication::processEvents(QEventLoop::AllEvents,20);
        msleep(30);
        if(worker){
            worker->loopZmq();
        }
    }
}

//Zmq Worker
RVR_Zmq_Worker::RVR_Zmq_Worker(QObject *parent) :
    QObject(parent)
{
    workerThread = new Zmq_Worker_Thread(this);
    moveToThread(workerThread);
    // start thread
    workerThread->start();
}

int RVR_Zmq_Worker::initZmq()
{
    if(((pCtx = zmq_ctx_new()) == NULL)||((sCtx = zmq_ctx_new()) == NULL)){
        qDebug()<<"ctx create faild!";
        return -1;
    }

    if((pSocket = zmq_socket(pCtx,ZMQ_PUSH)) == NULL){
        qDebug()<<"Psocket create faild!";
        zmq_ctx_destroy(pCtx);
        return -1;
    }

    if((sSocket = zmq_socket(pCtx,ZMQ_SUB)) == NULL){
        qDebug()<<"Ssocket create faild!";
        zmq_ctx_destroy(pCtx);
        return -1;
    }
    return 1;
}

int RVR_Zmq_Worker::setPort(QString /*ip*/, int /*reciPort*/, int /*sendPort*/)
{
    //sub
    int flage;
//    const char *sAddr = "tcp://192.168.68.11:6690";
    if((flage = zmq_connect(sSocket,"tcp://192.168.68.12:6690")) < 0){
        qDebug()<<"connect to sub faild!";
        zmq_close(sSocket);
        zmq_ctx_destroy(sCtx);
        return -1;
    }

    int iRcvTimeout = 200;
    if(zmq_setsockopt(sSocket,ZMQ_RCVTIMEO,&iRcvTimeout,sizeof(iRcvTimeout)) < 0){
        printf("ZMq connect out time ,will be faild!");
        return -1;
    }

    char data_flag = 0x01;
    if((flage = zmq_setsockopt(sSocket,ZMQ_SUBSCRIBE,&data_flag,0)) < 0){
        qDebug()<<"set socket faild!";
    }
    //pub
    const char *pAddr = "tcp://192.168.68.12:6686";
    if((flage = zmq_connect(pSocket,pAddr))< 0){
        qDebug()<<"connect to push faild!";
        return -1;
    }
    qDebug()<<"send port:"<<pAddr;
//    qDebug()<<"recive port:"<<sAddr;
    return 1;
}

void RVR_Zmq_Worker::writezmq(QByteArray barr)
{
    Rlock.lock();
    if(commdQueue.length() > 30){
        commdQueue.clear();
    }
    else{
        commdQueue.enqueue(barr);
    }
    Rlock.unlock();
}

int RVR_Zmq_Worker::readData()
{
    char buf[1024] = {0};
    QByteArray bArr;
    int size = 0;
    if((size = zmq_recv(sSocket,buf,1024,0))> 0){
        qDebug()<<"reciv data size:"<<size;
        QString strOut,st;
        for(int i = 0 ;i < size;i++){
            strOut += "0x"+st.sprintf("%02X",(uchar)buf[i])+" ";
            bArr.push_back((uchar)buf[i]);
        }
//        qDebug()<<"zmq reciv data:"<<strOut;
    }
    else{
//        qDebug()<<"wait data come";
        return 0;
    }
    emit newData(bArr);
    return 1;
}

bool RVR_Zmq_Worker::writeData()
{
    Rlock.lock();
    char update[1024];
    if(commdQueue.length() != 0){
        QByteArray barr = commdQueue.dequeue();
        int len = barr.length();
        for(int i = 0;i < len;i++){
            update[i] = barr[i];
            if(i == 9) update[i] = 0xfe;
            if(i == 10) update[i] = 0x01;
        }
        int flage = zmq_send(pSocket,update,len,0);
        if(flage < 0){
            qDebug()<<"add data faild!";
        }
        else {
            ;//qDebug()<<"send data succeed.";
        }
    }
    Rlock.unlock();
  return true;
}

int RVR_Zmq_Worker::exit()
{
    workerThread->exitFlag = true;
    workerThread->exit(0);
    delete workerThread;
    if(pSocket){
        zmq_close(pSocket);
    }
    if(pCtx){
        zmq_ctx_destroy(pCtx);
    }
    if(sSocket){
        zmq_close(sSocket);
    }
    if(sCtx){
        zmq_ctx_destroy(sCtx);
    }
    return 1;
}

void RVR_Zmq_Worker::loopZmq()
{
    readData();
    writeData();
}

