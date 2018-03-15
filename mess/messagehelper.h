#ifndef MESSAGEHELPER_H
#define MESSAGEHELPER_H

#include <QObject>
#include <QMutex>
#include <QMutexLocker>

#include <QLabel>
#include <QPushButton>

#include <QFont>
#include <QFontDatabase>

#include <QApplication>

class MessageHelper : public QObject
{
    Q_OBJECT

private:
    QFont font;
    static MessageHelper *_MessHelper;
public:
    explicit MessageHelper(QObject *parent = 0);

    static MessageHelper *instance(){
        static QMutex mutex;
        if(!_MessHelper){
           QMutexLocker lock(&mutex);
           if(!_MessHelper){
               _MessHelper = new MessageHelper;
           }
        }
        return _MessHelper;
    }
    void setLable(QLabel *lab,QChar c,int size = 10);
    void setButton(QPushButton *button,QChar c, int size = 10);
signals:

public slots:

};

#endif // MESSAGEHELPER_H
