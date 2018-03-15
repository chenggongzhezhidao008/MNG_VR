#ifndef RVR_SERIALPARSE_H
#define RVR_SERIALPARSE_H

#include <QObject>
#include <QByteArray>

class RVR_serialparse : public QObject
{
    Q_OBJECT
public:
    explicit RVR_serialparse(QObject *parent = 0);

private:
    int  find_head_rear(char *serData,int len,int &startPos);
    void message_parse(QByteArray message);
signals:
    void mess_Data(QString mess_type,QByteArray base);
public slots:
    void parse_serial(QByteArray newdata);

private:
    QByteArray serialbuff;
};

#endif // RVR_SERIALPARSE_H
