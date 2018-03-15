#ifndef RVR_DATAWRITE_H
#define RVR_DATAWRITE_H

#include <QObject>
#include <QStringList>
#include <QDebug>
#include <QMap>

class RVR_DataWrite : public QObject
{
    Q_OBJECT

public:
    explicit RVR_DataWrite(QObject *parent = 0);
    void initRVRDataMap();

private:
    void serialPortAsk();
    void SerialPortSet(QMap<QString,QString> data);
    void deviceSet(QMap<QString,QString> data);
    void dataInfoAsk();
    void recoverFactorySet();
    void waringask();
    void getgyro();
    void reciinitgyro(QMap<QString,QString> data);
    void sendinitgyro(QMap<QString,QString> data);
    void setWindRain(QMap<QString,QString> data);
    void enable_RVR(QMap<QString,QString> data);
    void enable_hinder_light(QMap<QString,QString> data);
    void enable_send_blower(QMap<QString,QString> data);
    void enable_reci_blower(QMap<QString,QString> data);
    void message_model(QMap<QString,QString> data);
    void Threshold_set(QMap<QString,QString> data);
    void RVR_Calc_parameter(QMap<QString,QString> data);
    void sender_arguments_set(QMap<QString,QString> data);
    void RVR_calc_input_value(QMap<QString,QString> data);
    void offsetCalibration(QMap<QString,QString> data);
    void fullScaleCalibration(QMap<QString,QString> data);
    void RVRReset(QMap<QString,QString> data);
    void groySetZero(QMap<QString,QString> data);
    void lineTest(QMap<QString,QString> data);
    void hearbeat(QMap<QString,QString> data);
    void commmand(QByteArray fram,QByteArray commd,QByteArray data);

signals:
    void writeComm(QByteArray com);

public slots:
   void writeData(QString option, QMap<QString,QString> data);
   void writeMonitor(QString option,QByteArray data);

private:
   char groyinitData[9];
   char enableData[5];
   char Threshold[21];
   char RVRparameter[10];
   char senderparameter[3];
   char RVRcalcValues[4];
   void atHeadAddSeq(QByteArray data);
   int seq;

};

#endif // RVR_DATAWRITE_H
