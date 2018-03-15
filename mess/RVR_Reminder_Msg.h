#ifndef RVR_REMINDER_MSG_H
#define RVR_REMINDER_MSG_H
#include "mess/messgae.h"
#include <QtCore>
#include <QtGui>
#include "datadue/rvr_datawrite.h"

class Reminder_Mseg : public QObject
{
public:
    static void showMessageboxInfo(QString info){
        Messgae *msg = new Messgae;
        msg->setMessage(info,1);
        msg->exec();
    }
    static void showMessageboxError(QString info){
        Messgae *msg = new Messgae;
        msg->setMessage(info,3);
        msg->exec();
    }
    static void showMessageboxQuestion(QString info){
        Messgae *msg = new Messgae;
        msg->setSendFlage(true);
        msg->setMessage(info,2);
        msg->exec();
    }
};
#endif // RVR_REMINDER_MSG_H
