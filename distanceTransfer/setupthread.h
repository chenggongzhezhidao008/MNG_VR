#ifndef SETUPTHREAD_H
#define SETUPTHREAD_H

#include <QObject>
#include "cdmatransport.h"
#include <QByteArray>
#include <QDebug>
#include <QTimer>

class SetupThread : public QObject
{
    Q_OBJECT
public:
    explicit SetupThread(QObject *parent = 0);

signals:
    void setup();
    void reciMessage(QByteArray data);
    void writeCDMA(QByteArray data);

private:
    CDMATransport *cdma;

};

#endif // SETUPTHREAD_H
