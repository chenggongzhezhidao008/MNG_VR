#ifndef RVR_DATAPARSE_H
#define RVR_DATAPARSE_H

#include <QObject>
#include <QDebug>
#include <QMap>
#include <QStringList>

class RVR_DataParse : public QObject
{
    Q_OBJECT
public:
    explicit RVR_DataParse(QObject *parent = 0);

private:
    void baseInfoParse(QByteArray softinfo,QByteArray datainfo);
    void serialParse(QByteArray softinfo,QByteArray datainfo);
    void dataInfoParse(QByteArray softinfo,QByteArray datainfo);
    void gyroInitParse(QByteArray softinfo,QByteArray datainfo);
    void Threshold(QByteArray softinfo,QByteArray datainfo);
    void recoverFactoryParse(QByteArray softinfo,QByteArray datainfo);
    void RVRCalcData(QByteArray softinfo,QByteArray datainfo);
    void workModleParse(QByteArray softinfo,QByteArray datainfo);
    void senderMachineConfParse(QByteArray softinfo,QByteArray datainfo);
    void enableParse(QByteArray softinfo,QByteArray datainfo);
    void waringParse(QByteArray softinfo,QByteArray datainfo);
    void WaringUpSend(QByteArray softinfo,QByteArray datainfo);
    void groyXYZZero(QByteArray softinfo,QByteArray datainfo);
    void fullScaleInfo(QByteArray softinfo,QByteArray datainfo);
    void offsetValueInfo(QByteArray softinfo,QByteArray datainfo);
    void RVRSoftRecover(QByteArray softinfo,QByteArray datainfo);
    void lineTestValue(QByteArray softinfo,QByteArray datainfo);
signals:
    void baseInfo(QByteArray softInfo,QMap<QString,QString>dataMap);
    void serialInfo(QByteArray softInfo,QMap<QString,QString> dataMap);
    void enable(QByteArray softInfo,QMap<QString,QString>dataMap);
    void gyroInint(QByteArray softInfo,QMap<QString,QString> dataMap);
    void ThresholdValue(QByteArray softInfo,QMap<QString,QString>dataMap);
    void fullScaaleValueSignal(QByteArray softInfo,QMap<QString,QString>dataMap);
    void calibrationOffsetValue(QByteArray softInfo,QMap<QString,QString>dataMap);
    void RVRSoftRecover(QByteArray softInfo,QMap<QString,QString>dataMap);
    void lineValue(QByteArray softInfo,QMap<QString,QString>dataMap);
    void senderMachine(QByteArray softInfo,QMap<QString,QString>dataMap);
    void Rvr(QByteArray softInfo,QMap<QString,QString>dataMap);
    void waring(QByteArray softInfo,QMap<QString,QString>dataMap);
    void waringUp(QByteArray softInfo,QMap<QString,QString>dataMap);
    void groyXYZZeroValue(QByteArray softInfo,QMap<QString,QString>dataMap);
    void datalist(QByteArray softInfo,QMap<QString,QString>dataMap);
    void workmodle(QByteArray softInfo,QMap<QString,QString>dataMap);
    void recover(QByteArray softInfo,QMap<QString,QString>dataMap);
    void RVRData(QByteArray softInfo,QMap<QString,QString>dataMap);

public slots:
    void dataParse(QString mess_type,QByteArray data);
    void maintainRvrCalc(QString option,QMap<QString,QString> data);
    void enableRemainRVR(bool ok);
private:
//    RVR_serialparse *ser_par;
    QStringList functionlist;
    bool RVR_enable;
    double i;
    double et;
    double RVR_value_calc(int morvalue, double ivalue , double etvalue );
    float byteToFloat(QByteArray bytes);
};

#endif // RVR_DATAPARSE_H
