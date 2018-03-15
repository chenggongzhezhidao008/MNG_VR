#include "rvr_serialport.h"

RVR_Serialport::RVR_Serialport(QObject *parent) :
    QObject(parent)
{
    R_pSer = NULL;
}
int RVR_Serialport::initSerialprot(QString strcom,int baud,int betys,int stop,QString parity)
{
    if(R_pSer == NULL){
        R_pser = new QSerialPort();
    }
    if(!R_pSer)return -1;
    if(R_pSer->isOpen())R_pSer->close();
    R_pSer->setPortName(strcom);
    R_pSer->setBaudRate(baud);
    R_pSer->setDataBits(betys);
    R_pSer->setStopBits(stop);
    R_pSer->setParity(parity);
    if(!R_pSer->open(QIODevice::ReadWrite))return -1;
    connect(R_pSer,SIGNAL(readyRead()),this,SLOT(serialNewdata()));
    return 1;
}
vooid RVR_Serialport::serialNewdata(){
   QByteArray byte = R_pSer->readAll();
   emit newDataCom(byte);
}
int  RVR_Serialport::writeSerialData(QByteArray byte,qint64 len){
    int length = int(R_pSer->write(byte,len));
    return length;
}
