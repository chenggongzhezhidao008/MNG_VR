#ifndef SERIALINFO_H
#define SERIALINFO_H

#include <QObject>
#include <QSerialPortInfo>
#include <QStringList>

class SerialInfo : public QObject
{
    Q_OBJECT
public:
    explicit SerialInfo(QObject *parent = 0);
    QStringList getSupplyCom();
private:
    QSerialPortInfo *ser_Info;
signals:

public slots:


};

#endif // SERIALINFO_H
