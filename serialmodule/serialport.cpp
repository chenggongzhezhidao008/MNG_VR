#include "serialport.h"
#include <QDebug>
SerialPort::SerialPort(QObject *parent) :
    QObject(parent)
{
    R_Ser = NULL;
    openIsOk = false;
    i  = 0;
}

void SerialPort::initSerial()
{
    if(!R_Ser){
        R_Ser = new QSerialPort();
    }
}

//============================
//baud:
//4800 = 4800 baud.9600	= 9600 baud,19200=19200 baud,38400 = 38400 baud.
//dataNum:
//1	= Five bits,2 = Six bits,3 = Seven bits,4 = Eight bits.
//stopByte:
//1 = 1 stop bit,3 = 1.5 stop bits,2 = 2 stop bits.
//parity:
//1 = No parity,2 = Even parity,3 = Odd parity.
//=============================

bool SerialPort::setopenSerial(QString StrCom,
                               int baud,
                               int dataNum,
                               int stopByte,
                               int parity){
    // open serial
    R_Ser->setPortName(StrCom);
    openIsOk = R_Ser->open(QIODevice::ReadWrite);
    if(!openIsOk) {
        qDebug()<<StrCom+"open is faild!please check com!";
        return false;
    }

    switch (baud) {
    case 1200:
        R_Ser->setBaudRate(QSerialPort::Baud1200);
        break;
    case 2400:
        R_Ser->setBaudRate(QSerialPort::Baud2400);
        break;
    case 4800:
        R_Ser->setBaudRate(QSerialPort::Baud4800);
        break;
    case 9600:
        R_Ser->setBaudRate(QSerialPort::Baud9600);
        break;
    case 19200:
        R_Ser->setBaudRate(QSerialPort::Baud19200);
        break;
    case 38400:
        R_Ser->setBaudRate(QSerialPort::Baud38400);
        break;
    case 57600:
        R_Ser->setBaudRate(QSerialPort::Baud57600);
        break;
    case 115200:
        R_Ser->setBaudRate(QSerialPort::Baud115200);
        break;
    default:
        break;
    }

    switch (dataNum) {
    case 1:
        R_Ser->setDataBits(QSerialPort::Data5);
        break;
    case 2:
        R_Ser->setDataBits(QSerialPort::Data6);
        break;
    case 3:
        R_Ser->setDataBits(QSerialPort::Data7);
        break;
    case 4:
        R_Ser->setDataBits(QSerialPort::Data8);
        break;
    default:
        break;
    }
    switch (parity) {
    case 1:
        R_Ser->setParity(QSerialPort::NoParity);
        break;
    case 2:
        R_Ser->setParity(QSerialPort::EvenParity);
        break;
    case 3:
        R_Ser->setParity(QSerialPort::OddParity);
        break;
    case 4:
        R_Ser->setParity(QSerialPort::SpaceParity);
        break;
    case 5:
        R_Ser->setParity(QSerialPort::MarkParity);
        break;
    default:
        break;
    }
    // 停止位 为1 预留的。
    int stop = stopByte;
    stop = 1;
    switch (stop) {
    case 1:
        R_Ser->setStopBits(QSerialPort::OneStop);
        break;
    case 2:
        R_Ser->setStopBits(QSerialPort::OneAndHalfStop);
        break;
    case 3:
        R_Ser->setStopBits(QSerialPort::TwoStop);
        break;
    default:
        break;
    }
    R_Ser->setFlowControl(QSerialPort::NoFlowControl);
    connect(R_Ser,SIGNAL(readyRead()),this,SLOT(ser_newData()));
    return true;
}

void SerialPort::closeSerial(){
    if(R_Ser->isOpen()){
        R_Ser->close();
        openIsOk = false;
        disconnect(R_Ser,SIGNAL(readyRead()),this,SLOT(ser_newData()));
    }
    return ;
}

void SerialPort::ser_newData(){

    QByteArray newbArry = R_Ser->readAll();
    qDebug()<<"收到的数据"+QString::number(i,10)+"->>:"+newbArry.toHex();
    i++;
    emit newData(newbArry);
}

bool SerialPort::ser_writeData(QByteArray ser_data,int datalen){
    if(!R_Ser->isOpen()){
        qDebug()<<"serial is close,data write failed!";
        return false;
    }
    if(datalen == ((int)R_Ser->write(ser_data))) return true;
    qDebug()<<"write serial failed!,data lost,please resend.";
    return false;
}

QStringList SerialPort::SerialPortInfo(QString &serialstau){
    QStringList SeriaList;
    if(!R_Ser->isOpen()){
        serialstau = "serial ont open!";
        return SeriaList<<"";
    }
    serialstau = "allow";
    SeriaList<<R_Ser->portName();
    SeriaList<<QString::number(R_Ser->baudRate());
    SeriaList<<QString::number(R_Ser->dataBits());
    if(R_Ser->stopBits() == QSerialPort::OneStop){
        SeriaList<<"1 byte";}
    if(R_Ser->stopBits() == QSerialPort::OneAndHalfStop){
        SeriaList<<"1 byte";}
    if(R_Ser->stopBits() == QSerialPort::TwoStop){
        SeriaList<<"1 byte";}
    switch (R_Ser->parity()) {
    case 0:
        SeriaList<<"无校验";
        break;
    case 3:
        SeriaList<<"奇校验";
        break;
    case 2:
        SeriaList<<"偶校验";
        break;
    default:
        break;
    }
    return SeriaList;
}


