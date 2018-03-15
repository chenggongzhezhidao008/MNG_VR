#include "messageparse.h"
#include <QDebug>
#include <QTime>

MessageParse::MessageParse(QObject *parent) :
    QObject(parent)
{

}

void MessageParse::getMessageBarry(QByteArray message)
{
    message.remove(0,1);
    message.remove(((message.length())-2),2);
    messageParse(message);
}

void MessageParse::messageParse(QByteArray message)
{
    char before[] = { 0x03, 0x02};
    QByteArray beforeBarry(before,2);
    char after[] = { 0x03};
    QByteArray afterBarry(after,1);
    message.replace(beforeBarry,afterBarry);
    DataList dataList = message.split(char(0x03));
    sensorParse(dataList);
}

void MessageParse::sensorParse(DataList dataList)
{
    DataList headDataList = (dataList.value(0)).split(char(0x7c));
    QString sensorFlag = (QString)(headDataList.value(3));
    //    qDebug()<<"Time:"<<QTime::currentTime().toString();
    if(sensorFlag == "CLOUD"){
        qDebug()<<"CLOUD";
        cloudDataParse(dataList);
    }
    else if(sensorFlag == "HUMITEMP"){
        qDebug()<<"HUMITEMP";
        humiTempDataParse(dataList);
    }
    else if(sensorFlag == "PRESS"){
        qDebug()<<"PRESS";
        atmospherePressDataParse(dataList);
    }
    else if(sensorFlag == "RAIN"){
        qDebug()<<"RAIN";
        rainDataParse(dataList);
    }
    else if(sensorFlag == "VIS"){
        qDebug()<<"VIS";
        rvrDataParse(dataList);
    }
    else if(sensorFlag == "WIND"){
        qDebug()<<"wind";
        windDataParse(dataList);
    }
    else if(sensorFlag == "PW"){
        qDebug()<<"PW";
        phenomenaWeatherDataParse(dataList);
    }
    else if(sensorFlag == "PV"){
        qDebug()<<"PV";
        prevailingVisibilityDataParse(dataList);
    }
    else if(sensorFlag == "Manual"){
        qDebug()<<"Manual";
        manualInputDataDataParse(dataList);
    }
    else{
        return;
    }
}

void MessageParse::windDataParse(DataList dataList)
{
    SensorMap sMap;
    DataMap hMap;
    DataMap dMap;
    DataList headDataList = (dataList.value(0)).split(char(0x7c));
    hMap["windVersion"] = (QString)(headDataList.value(0));
    hMap["windUnixTime"] = (QString)(headDataList.value(2));
    hMap["windID"] = (QString)(headDataList.value(4));
    for(int i = 1;i < dataList.length();i++){
        DataList subList = (dataList.value(i)).split(char(0x7c));
        QString dataName = (QString)(subList.value(0));
        if((QString)(subList.value(4)) == ""){
            dMap[dataName] = (QString)(subList.value(3));
        }
        else{
            dMap[dataName] = (QString)(subList.value(3)) + ":" + (QString)(subList.value(4));
        }
    }
    sMap["windHead"] = hMap;
    sMap["windData"] = dMap;

//    qDebug()<<"wind Head:"<<hMap;
//    qDebug()<<"wind body:"<<dMap;

    emit windDataSignal(sMap);
}

void MessageParse::humiTempDataParse(DataList datalist)
{
    SensorMap sMap;
    DataMap hMap;
    DataMap dMap;
    DataList headDataList = (datalist.value(0)).split(char(0x7c));
    hMap["humAndTempVersion"] = (QString)(headDataList.value(0));
    hMap["humAndTempUnixTime"] = (QString)(headDataList.value(2));
    hMap["humAndTempID"] = (QString)(headDataList.value(4));
    for(int i = 1;i < datalist.length();i++){
        DataList subList = (datalist.value(i)).split(char(0x7c));
        QString dataName = (QString)(subList.value(0));
        if((QString)(subList.value(4)) == ""){
            dMap[dataName] = (QString)(subList.value(3));
        }
        else{
            dMap[dataName] = (QString)(subList.value(3)) + ":" + (QString)(subList.value(4));
        }
    }
    sMap["humAndTempHead"] = hMap;
    sMap["humAndTempData"] = dMap;

//    qDebug()<<"hum And Temp Head:"<<hMap;
//    qDebug()<<"hum And Temp body:"<<dMap;

    emit humiTempDataSignal(sMap);
}

void MessageParse::rvrDataParse(DataList datalist)
{
    for(int i = 0;i < datalist.length();i++){
        //qDebug()<<"VIS dataXXXX:"+QString("%1:").arg(i)<<datalist.value(i);qDebug()<<"\n";
    }
    SensorMap sMap;
    DataMap hMap;
    DataMap dMap;
    DataList headDataList = (datalist.value(0)).split(char(0x7c));
    hMap["VISVersion"] = (QString)(headDataList.value(0));
    hMap["VISUnixTime"] = (QString)(headDataList.value(2));
    hMap["VISID"] = (QString)(headDataList.value(4));
    for(int i = 1;i < datalist.length();i++){
        DataList subList = (datalist.value(i)).split(char(0x7c));
        QString dataName = (QString)(subList.value(0));
        if((QString)(subList.value(4)) == ""){
            dMap[dataName] = (QString)(subList.value(3));
        }
        else{
            dMap[dataName] = (QString)(subList.value(3)) + ":" + (QString)(subList.value(4));
        }
    }
    sMap["VISHead"] = hMap; qDebug()<<"VIS Head:"<<hMap;
    sMap["VISData"] = dMap; qDebug()<<"VIS body 9999999:"<<dMap;
    emit rvrDataSignal(sMap);
}

void MessageParse::cloudDataParse(DataList /*dataList*/)
{

}

void MessageParse::atmospherePressDataParse(DataList /*dataList*/)
{

}

void MessageParse::rainDataParse(DataList /*datalist*/)
{

}

void MessageParse::phenomenaWeatherDataParse(DataList /*datalist*/)
{

}

void MessageParse::prevailingVisibilityDataParse(DataList /*datalist*/)
{

}

void MessageParse::manualInputDataDataParse(DataList /*dataList*/)
{

}




