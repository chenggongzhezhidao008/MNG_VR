#include "serialinfo.h"

SerialInfo::SerialInfo(QObject *parent) :
    QObject(parent)
{
}

QStringList SerialInfo::getSupplyCom()
{
    if(!ser_Info){
        ser_Info = new QSerialPortInfo();
    }
    QStringList comNameList;
    QList<QSerialPortInfo> list = QSerialPortInfo::availablePorts();
    for(int i = 0;i < list.length();i++){
        comNameList << list.at(i).portName();
    }
    return comNameList;
}
