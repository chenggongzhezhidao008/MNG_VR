#ifndef RVR_MANAGER_H
#define RVR_MANAGER_H

#include <QMainWindow>
#include "comm.h"
#include <QMessageBox>
#include <QApplication>
#include <QMdiSubWindow>
#include <QPushButton>
#include <QEvent>
#include <QVariantList>
#include "mess/messgae.h"

#include <QMap>
#include <QVariant>
typedef QMap<QString,QVariant> lineData;
#include <QList>

typedef QMap<QString,QStringList> tableInfo;

namespace Ui {
class RVR_Manager;
}

class RVR_Manager : public QMainWindow
{
    Q_OBJECT
    Q_ENUMS(DataWay)
    Q_FLAGS(DataWays)

public:
    enum DataWay {
        SerialPraseData = 0x01,
        MessagePraseData = 0x02,
        SerialWriteData = 0x05,
        MessageWriteData = 0x06,
        NotWay = 0x00
    };
    Q_DECLARE_FLAGS(DataWays, DataWay)

    explicit RVR_Manager(QWidget *parent = 0);
    ~RVR_Manager();
    int  init_seialInfo();//功能：获取串口端口
    int  init_staupUI();//条件：需要串口端口信息
    int  init_turnTimer();//轮寻时钟
    int  init_Config();
    int  init_database();//需要数据表配置信息
    void init_sqlite(tableInfo tables);
    int  init_dataParse();
    int  init_commit(QString port);
    int  init_serial(QString comstr);
    int  init_COMM();
    int  init_commWrite();
    int  init_REMOTE();
    int  init_ZMQ();
    int  init_rvrTool();
    int  init_logStore();
    void init_managerUI();
    int  init_MessageParse();

    int  init_zmq3600();
    int  init_Transfer();
    void init_connections();
    void quit_app(bool flage);
    int  commUse3600();
    int  commUseRemote();
    int  commUseSerialCom(QString port);

    void init_dataDue();
    void selectDataParseWay(DataWays way);
    void selectDataWriteWay(DataWays way);

public slots:
    void outputDatabaseData(QString tableName);

private:
    void defaultShow(QWidget *Widget);
    bool openflage;


private:
    QString currentPort;
    bool havecoms;
    QTimer *updatetimer;
    int dataUpdateTime ;

    DataWays parseWay;
    DataWays writeWay;

    QMap<QString,QString> srialmap;
    QMdiSubWindow *openWin;
    QMdiSubWindow *subWin;

signals:
    void serInitStatus(bool falge);
    void maintainRVRCalcEnable(bool ok);
    void databaseData(QList<lineData> data);

private slots:
    void appInit(QString comName);

    void locationLoopUpdate();

    void setParseWriteWay(DataWays parseWay,DataWays writeWay);

    void askDataLoopUpdate();

    void  heartbeatLoop();

    void recover_message(QByteArray softInfo,QMap<QString,QString>dataMap);

    void updateSerialComm(QString option,QMap<QString,QString> data);

    void faultReportWaring(QByteArray softInfo,QMap<QString,QString>dataMap);

    void showRVRRecoverMessage(QByteArray softInfo,QMap<QString,QString>dataMap);

    void sqlLiteStore(QMap<QString,QString>dataMap);

    void on_actionAlignment_triggered();

    void on_actionCalibration_triggered();

    void on_actionLinearTest_triggered();

    void on_actionDefaultSet_triggered();

    void on_actionCurrentconfig_triggered();

    void on_actionDefaultConfig_triggered();

    void on_actionCurrentstatus_triggered();

    void on_action_triggered();

    void on_action_soft_reset_triggered();

    void on_action_Version_triggered();

    void on_action_exit_triggered();

    void on_actionRVR_triggered();



protected:
    void closeEvent(QCloseEvent *e);

private:
    QCloseEvent *eventclosed;
    bool serialCommit;
    bool rvrCalcenble;
    QString StrCom;
    Ui::RVR_Manager *ui;

};

Q_DECLARE_OPERATORS_FOR_FLAGS(RVR_Manager::DataWays)

#endif // RVR_MANAGER_H
