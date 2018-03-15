#ifndef MESSAGEPARSE_H
#define MESSAGEPARSE_H

#include <QObject>
#include <QByteArray>

typedef QList<QByteArray> DataList;

#include <QMap>
typedef QMap<QString,QString> DataMap;
typedef QMap<QString,DataMap> SensorMap;

class MessageParse : public QObject
{
    Q_OBJECT
public:
    explicit MessageParse(QObject *parent = 0);

signals:
    void windDataSignal(SensorMap senMap); //风的数据信号
    void humiTempDataSignal(SensorMap senMap); //温湿度数据信号
    void rvrDataSignal(SensorMap senMap); //能见度和跑到视程数据信号
    void cloudDataSignal(SensorMap senMap); //云数据信号
    void atmospherePressDataSignal(SensorMap senMap); //大气压数据信号
    void rainDataSignal(SensorMap senMap); //降雨量数据信号
    void phenomenaWeatherDataSignal(SensorMap senMap); //（PW）天气现象数据信号
    void prevailingVisibilityDataSignal(SensorMap senMap);//(PV)主导能见度数据信号
    void manualInputDataDataSignal(SensorMap senMap);//人工输入数据信号

public slots:
    void getMessageBarry(QByteArray message);//获取消息

private:
    void messageParse(QByteArray message);//消息格式解析
    void sensorParse(DataList dataList);//传感器解析
    void windDataParse(DataList dataList); //风的数据解析
    void humiTempDataParse(DataList datalist); //温湿度数据解析
    void rvrDataParse(DataList datalist); //能见度和跑到视程数据解析
    void cloudDataParse(DataList dataList); //云数据解析
    void atmospherePressDataParse(DataList dataList); //大气压数据解析
    void rainDataParse(DataList datalist); //降雨量数据解析
    void phenomenaWeatherDataParse(DataList datalist); //（PW）天气现象数据解析
    void prevailingVisibilityDataParse(DataList datalist);//(PV)主导能见度数据解析
    void manualInputDataDataParse(DataList dataList);//人工输入数据解析
};

#endif // MESSAGEPARSE_H
