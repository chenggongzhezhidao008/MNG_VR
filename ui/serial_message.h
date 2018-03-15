#ifndef SERIAL_MESSAGE_H
#define SERIAL_MESSAGE_H

#include <QWidget>
#include <QTime>
#include <QByteArray>

#include <QMap>
#include <QVariant>
typedef QMap<QString,QVariant> lineData;
typedef QMap<QString,QString> lineStrData;
#include <QList>

#include <QDebug>
#include <QTextCodec>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include "xlsx/xlsxdocument.h"


namespace Ui {
class Serial_Message;
}

class Serial_Message : public QWidget
{
    Q_OBJECT

public:
    explicit Serial_Message(QWidget *parent = 0);
    ~Serial_Message();
    void initDir(QString pathStr);

public slots:
    void showData(QByteArray str);
    void showLogData(QByteArray soft,QMap<QString,QString> dataMap);
    void tableData(QList<lineData> tabData);
    void ouputProgresss(int value);

signals:
    void sendData(QString option,QByteArray data);
    void storeDatabase(QMap<QString,QString> stroeMap);
    void storeExceldata(QMap<QString,QString> stroeMap);
    void storeTxtdata(QMap<QString,QString> stroeMap);
    void outputTable(QString table);
    void outputProgresssSignal(int value);

private slots:
    void on_pushButtonSendData_clicked();

    void on_pushButtonexcel_clicked();

    void on_pushButton_txt_clicked();

    void on_pushButton_from_set_clicked();

    void on_pushButtonok_clicked();

    void outputDatabase();

private:
    bool isSaveExcel;
    QString path;
    QStringList messlist;
    Ui::Serial_Message *ui;
    QString formatContrl(int length ,QString str);
    QTimer *outputTimer;
    bool  writeFlage;
    QFile *file;
    QList<lineData> tabledata;
    int lineTotal;
    int outputedLines;
    void createDataFile();

};

#endif // SERIAL_MESSAGE_H
