#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QSerialPort>
#include <QByteArray>
#include <QStringList>
#include <QString>

class SerialPort : public QObject
{
    Q_OBJECT
public:
    explicit SerialPort(QObject *parent = 0);
    void initSerial();
    bool setopenSerial(QString StrCom,
                       int baud,
                       int dataNum,
                       int stopByte,
                       int parity);
    void closeSerial();
    bool openIsOk;
    QStringList SerialPortInfo(QString &serialstau);
private:

signals:
    void newData(QByteArray data);

public slots:
    bool ser_writeData(QByteArray ser_data,int datalen);

private slots:
    void ser_newData();


private:
    QSerialPort *R_Ser;
    int i;
};

#endif // SERIALPORT_H
