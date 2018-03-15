#ifndef RVR_SERIALPORT_H
#define RVR_SERIALPORT_H

#include <QObject>
#include <QSerialPort>
#include <QByteArray>

class RVR_Serialport : public QObject
{
    Q_OBJECT
public:
    explicit RVR_Serialport(QObject *parent = 0);
    int initSerialprot(QString strcom,int baud,int betys,int stop,QString parity);

signals:
    void newDataCom(QByteArray byte);
public slots:
    int  writeSerialData(QByteArray byte,qint64 len);

private slots:
    void serialNewdata();

private:
     QSerialPort* R_pSer;

};

#endif // RVR_SERIALPORT_H

















