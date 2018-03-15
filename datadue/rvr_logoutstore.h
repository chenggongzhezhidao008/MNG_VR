#ifndef RVR_LOGOUTSTORE_H
#define RVR_LOGOUTSTORE_H

#include <QObject>
#include <QMap>
#include <QDebug>
#include <QTextCodec>
#include <QFile>
#include <QDateTime>
#include <QIODevice>
#include <QTextStream>
#include "xlsx/xlsxdocument.h"

typedef QMap<QString,QString> datMap;
class RVR_LogOutStore : public QObject
{
    Q_OBJECT
public:
    explicit RVR_LogOutStore(QObject *parent = 0);
    void setfilePath(QString globalPath);

signals:
    void lostdata(QMap<QString, QString> dataMap);

public slots:
    void TxtStoreFile(QMap<QString, QString> dataMap);
    void ExcelStoreFile(QMap<QString, QString> dataMap);
    void memeryWrite();

private slots:
    void saveLostData(QMap<QString, QString> dataMap);

private:
    QString lastFileName;
    QString memeryLastFileName;
    QString pathStr;
    QString headStr;
    bool textHead;
    bool excelHead;
    bool excelSelect;
    int excerow;
    bool writeFlage;
    QList<datMap> memerylist;
    QString path;
    QFile *file;
    QTextCodec *codec;
    int backnumber;
};

#endif // RVR_LOGOUTSTORE_H
