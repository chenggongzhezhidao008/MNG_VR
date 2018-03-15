#ifndef RVR_CURRENTSTATUS_H
#define RVR_CURRENTSTATUS_H

#include <QDialog>
#include <QMap>
#include <QTextCharFormat>
#include <QWidget>
#include <QMdiSubWindow>
#include <QLineEdit>
#include <QTextEdit>

//RVR calc values
#include "ui/rvr_calc_values.h"
#include "windPlugins/windmeter.h"


typedef QList<QByteArray> DataList;
typedef QMap<QString,QString> DataMap;
typedef QMap<QString,DataMap> SensorMap;


namespace Ui {
class RVR_CurrentStatus;
}

class RVR_CurrentStatus : public QDialog
{
    Q_OBJECT

public:
    explicit RVR_CurrentStatus(QWidget *parent = 0);
    ~RVR_CurrentStatus();
    void init_message_data_tempHumUI();//消息数据时初始化界面

protected:
    //      bool eventFilter(QObject *obj, QEvent *event);

private:
    void init_ui();
    void selectWindMeter(int index,WindMeter *windMeter,DataMap windData);//在表盘上显示风数据
    void selectVis(int index,QLineEdit *visTable,DataMap visData);//在rvr显示标签上显示mor
    void selectHumiTemp(int index,DataMap humiTempData);//在界面上显示温湿度数据

signals:
    void RVR_calc_option(QString option,QMap<QString,QString> data);
    void privateVisData(QByteArray version,QMap<QString,QString>);//0109 数据发送到日志以便保存

public slots:
    //serial data
    void current_data_info(QByteArray softlist,QMap<QString,QString> dataMap);
    void current_rvr_data(QByteArray softlist,QMap<QString,QString> dataMap);
    //messgae data
    void windData(SensorMap senMap); //风的数据
    void rvrData(SensorMap senMap); //能见度和跑到视程数据
    void humiTempData(SensorMap senMap); //温湿度数据
    void showState(bool open);//显示各传感器状态


private:
    QMdiSubWindow *sub;
    Ui::RVR_CurrentStatus *ui;
    RVR_Calc_values *RVRCalc;

    //支持最多四个传感器的数据表盘显示的开始值
    int meterOneStart;
    int meterTwoStart;
    int meterThreeStart;
    int meterFourStart;

};

#endif // RVR_CURRENTSTATUS_H
