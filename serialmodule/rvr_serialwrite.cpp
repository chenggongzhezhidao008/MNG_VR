#include "rvr_serialwrite.h"
#include <QDebug>


RVR_SerialWorkThread::RVR_SerialWorkThread(RVR_serialwrite *pWork, QObject *)
{
    write_Work = pWork;
    R_wExit = false;
}

void RVR_SerialWorkThread::run()
{
    qDebug()<<"RVR_SerialWorkThread :"<<currentThreadId();
    while(!R_wExit){
        QCoreApplication::processEvents(QEventLoop::AllEvents, 20);
        msleep(30);
        write_Work->threadLoop();
    }
}

void RVR_SerialWorkThread::logHex(QByteArray bArry)
{
    QString strOut,st;
    for(int i = 0; i< bArry.length();i++){
        strOut += st.sprintf("%02X",(uchar)bArry[i]);
    }
   qDebug()<<strOut;
}

//==========

RVR_serialwrite::RVR_serialwrite(QObject *parent) :
    QObject(parent)
{
    R_thread = new RVR_SerialWorkThread(this);
    moveToThread(R_thread);
    R_thread->start();

}
void RVR_serialwrite::writeSerial(QByteArray bytes){
     R_lock.lock();
     if(messageQueue.size() > 40)
         messageQueue.clear();
     messageQueue.enqueue(bytes);
     R_lock.unlock();
}
void RVR_serialwrite::exit(){
    R_thread->R_wExit = true;
    R_thread->exit();
    R_thread->deleteLater();
}


void RVR_serialwrite::threadLoop(){
//    if(!R_serial){
//        qDebug()<<"serial is not malloc!";
//        return ;
//    }
    R_lock.lock();
     if(!messageQueue.isEmpty()){
//         if(!R_serial->openIsOk){
//             qDebug()<<"SerialPort is not open ,write data failed!";
//         }
          if(R_thread->R_wExit){
              qDebug()<<"the R_thread is out,it did not work!";
          }
          QByteArray bytes = messageQueue.dequeue();
          emit send_data(bytes,bytes.length());
//          R_serial->ser_writeData(bytes,bytes.length());
     }
     R_lock.unlock();
}
