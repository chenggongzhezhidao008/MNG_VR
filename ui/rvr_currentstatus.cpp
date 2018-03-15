#include "rvr_currentstatus.h"
#include "ui_rvr_currentstatus.h"
#include <QTextCharFormat>
#include <QLineEdit>
#include <QDebug>
#include <QLineEdit>
#include <QFont>
#include <QPropertyAnimation>


RVR_CurrentStatus::RVR_CurrentStatus(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RVR_CurrentStatus)
{
    ui->setupUi(this);
    init_ui();
    showState(false);
    //    ui->Wind_widget->installEventFilter(this);
}

RVR_CurrentStatus::~RVR_CurrentStatus()
{
    delete ui;
}

//bool RVR_CurrentStatus::eventFilter(QObject *obj, QEvent *event)
//{
//    if(obj == ui->Wind_widget)
//    {
//        if (event->type() == QEvent::MouseButtonPress) {
//            event->accept();
//        }
//        if (event->type() == QEvent::MouseMove) {
//            event->accept();
//        }
//    }
//    else{
//        return QObject::eventFilter(obj, event);
//    }
//}

void RVR_CurrentStatus::init_ui()
{
    ui->lineEdit_AD->setAlignment(Qt::AlignCenter);
    ui->lineEdit_Mor->setAlignment(Qt::AlignCenter);
    ui->lineEdit_RVR->setAlignment(Qt::AlignCenter);
    ui->textEdit_reciver_humidity->setAlignment(Qt::AlignCenter);
    ui->textEdit_reciver_temperature->setAlignment(Qt::AlignCenter);
    ui->textEdit_send_humidity->setAlignment(Qt::AlignCenter);
    ui->textEdit_send_temperature->setAlignment(Qt::AlignCenter);

    ui->lineEdit_AD->setReadOnly(true);
    ui->lineEdit_Mor->setReadOnly(true);
    ui->lineEdit_RVR->setReadOnly(true);
    ui->textEdit_reciver_humidity->setEnabled(false);
    ui->textEdit_reciver_temperature->setEnabled(false);
    ui->textEdit_send_humidity->setEnabled(false);
    ui->textEdit_send_temperature->setEnabled(false);
    QMap<QString,QString> map;
    map["MOR"] = "///";
    map["rvr_value"] = "///";
    map["reciver_temperature"] = "///";
    map["reciver_humidity"] = "///";
    map["send_temperature"] = "///";
    map["send_humidity"] = "///";
    current_data_info(QByteArray(),map);
}

void RVR_CurrentStatus::init_message_data_tempHumUI()
{
    ui->groupBox_send->setTitle("温度传感器");
    ui->groupBox_recvi->setTitle("湿度传感器");

    ui->label_send_hum->hide();
    ui->label_reciv_temp->hide();

    ui->textEdit_send_humidity->hide();
    ui->textEdit_reciver_temperature->hide();

    ui->label_send_temp->setGeometry(50,60,26,19);
    ui->label_reciv_hum->setGeometry(50,60,26,19);

    ui->textEdit_send_temperature->setGeometry(80,50,141,41);
    ui->textEdit_reciver_humidity->setGeometry(80,50,141,41);
}
void RVR_CurrentStatus::selectWindMeter(int index, WindMeter *windMeter, DataMap windData)
{
    QString tenAvSpeed = (windData["WS10A"].split(":")).value(0);
    QString tenAvAngle = (windData["WD10A"].split(":")).value(0);
    int twoAvAngle = ((windData["WD2A"].split(":")).value(0)).toInt();
    int tenMinAngle = ((windData["WD10M"].split(":")).value(0)).toInt();
    int tenMaxAngle = ((windData["WD10X"].split(":")).value(0)).toInt();
    //    qDebug()<<"真北十分钟平均风速:"<<tenAvSpeed<<"真北十分钟平均风向:"<<tenAvAngle<<"两分钟平均风向（箭头）:"<<twoAvAngle<<"真北十分钟最小风向:"<<tenMinAngle<<"真北十分钟最大风向:"<<tenMaxAngle;
    windMeter->setWindCurrentSpeed(tenAvSpeed);
    windMeter->setWindCurrentAngle(tenAvAngle.toInt());
    windMeter->setTenWindMinAngle(tenMinAngle);
    windMeter->setTenWindMaxAngle(tenMaxAngle);
    windMeter->setTwoWindAvAngle(twoAvAngle);

    QPropertyAnimation *animation = new QPropertyAnimation(windMeter,"twoWindAvAngle");
    animation->setDuration(500);
    if(index == 1){
        animation->setStartValue(meterOneStart);
        meterOneStart = twoAvAngle;
        animation->setEndValue(twoAvAngle);
        animation->start();
    }
    else if(index == 2){   //在此修改显示的数据已达到一个表盘显示不同传感器数据
        //        animation->setStartValue(meterTwoStart);
        meterTwoStart = twoAvAngle;
        //        animation->setEndValue(twoAvAngle);
        //        animation->start();
    }
    else if(index == 3){
        //        animation->setStartValue(meterThreeStart);
        meterThreeStart = twoAvAngle;
        //        animation->setEndValue(twoAvAngle);
        //        animation->start();
    }
    else if(index == 4){
        //        animation->setStartValue(meterFourStart);
        meterFourStart = twoAvAngle;
        //        animation->setEndValue(twoAvAngle);
        //        animation->start();
    }
    else{
        return ;
    }
    animation->deleteLater();
}

void RVR_CurrentStatus::selectVis(int /*index*/, QLineEdit *visTable, DataMap visData)
{
    visTable->setText(visData["MOR"]);//    qDebug()<<"VisBody:"<<visData;
    visData["RVR"] = "///";
    ui->lineEdit_RVR->setText(visData["RVR"]);
}

void RVR_CurrentStatus::selectHumiTemp(int /*index*/, DataMap humiTempData)
{
    //    qDebug()<<"zzzkkkkkk:"<<humiTempData;
    QString str = ((humiTempData["TAINS"]).split(":")).value(0);
    int len = str.length() + 1;
    ui->textEdit_send_temperature->setText(" "+str+"0C");
    QTextCharFormat fmt2;
    fmt2.setVerticalAlignment(QTextCharFormat::AlignSuperScript);
    QTextCursor cursorr(ui->textEdit_send_temperature->textCursor());
    cursorr.setPosition(len, QTextCursor::MoveAnchor);
    cursorr.setPosition(len+1, QTextCursor::KeepAnchor);
    cursorr.setCharFormat(fmt2);
    ui->textEdit_send_temperature->setAlignment(Qt::AlignCenter);
    str = ((humiTempData["RHINS"]).split(":")).value(0);
    ui->textEdit_reciver_humidity->setText(""+str+"%");
    ui->textEdit_reciver_humidity->setAlignment(Qt::AlignCenter);
}

void RVR_CurrentStatus::current_data_info(QByteArray,QMap<QString,QString> dataMap)
{
    QTextCharFormat fmt;
    fmt.setVerticalAlignment(QTextCharFormat::AlignSuperScript);
    ui->lineEdit_AD->setText(dataMap["AD"]);
    ui->lineEdit_Mor->setText(dataMap["MOR"]);
    ui->lineEdit_RVR->setText(dataMap["rvr_value"]);
    QString str = dataMap["reciver_temperature"].trimmed();
    int len = str.length() + 1;
    ui->textEdit_reciver_temperature->setText(" "+str+"0C");
    QTextCharFormat fmt2;
    fmt2.setVerticalAlignment(QTextCharFormat::AlignSuperScript);
    QTextCursor cursorr(ui->textEdit_reciver_temperature->textCursor());
    cursorr.setPosition(len, QTextCursor::MoveAnchor);
    cursorr.setPosition(len+1, QTextCursor::KeepAnchor);
    cursorr.setCharFormat(fmt2);
    ui->textEdit_reciver_temperature->setAlignment(Qt::AlignCenter);
    str = dataMap["send_temperature"].trimmed();
    len = str.length() + 1;
    ui->textEdit_send_temperature->setText(" "+str+"0C");
    QTextCursor cursors(ui->textEdit_send_temperature->textCursor());
    cursors.setPosition(len, QTextCursor::MoveAnchor);
    cursors.setPosition(len+1, QTextCursor::KeepAnchor);
    cursors.setCharFormat(fmt2);
    ui->textEdit_send_temperature->setAlignment(Qt::AlignCenter);
    str = dataMap["reciver_humidity"].trimmed();
    ui->textEdit_reciver_humidity->setText(""+str+"%");
    ui->textEdit_reciver_humidity->setAlignment(Qt::AlignCenter);
    str = dataMap["send_humidity"].trimmed();
    ui->textEdit_send_humidity->setText(""+str+"%");
    ui->textEdit_send_humidity->setAlignment(Qt::AlignCenter);
}

void RVR_CurrentStatus::current_rvr_data(QByteArray /*softlist*/, QMap<QString, QString> dataMap)
{
    int mor = ui->lineEdit_Mor->text().trimmed().toInt();
    qDebug()<<"mor"<<mor;
    ui->lineEdit_RVR->setText(dataMap["rvr_value"]);
}

void RVR_CurrentStatus::windData(SensorMap senMap)
{
    DataMap headmap = senMap["windHead"];
    DataMap bodymap = senMap["windData"];
    QStringList keysList = bodymap.keys();
    for(int keynum = 0; keynum < keysList.length(); keynum++){
        if(keysList.value(keynum) == "SC_WIND_Alive"){
            if((bodymap["state"].trimmed()).toInt() == 1){
                qDebug()<<"收到WIND设备在线状态";
                ui->label_windState->setStyleSheet("QLabel#label_windState{border-radius:5px;color: green; background-color:#00FF00;font-size:14px;border-style:none;}");

            }
            if((bodymap["state"].trimmed()).toInt() == 0){
                qDebug()<<"收到WIND设备下线状态";
                ui->label_windState->setStyleSheet("QLabel#label_windState{border-radius:5px;color: red; background-color:#00FF00;font-size:14px;border-style:none;}");

            }
            return ;
        }
    }
    int index = (headmap["windID"]).toInt();
    //风数据不正常时要修改此处的id号方能使风数据表盘显示正常。
    if(index == 0){
        selectWindMeter(0,ui->Wind_widget,bodymap);
    }
    if(index == 2){
        selectWindMeter(2,ui->Wind_widget,bodymap);
    }
    if(index == 3){
        selectWindMeter(3,ui->Wind_widget,bodymap);
    }
    if(index == 4){
        selectWindMeter(4,ui->Wind_widget,bodymap);
    }
}

void RVR_CurrentStatus::rvrData(SensorMap senMap)
{
    DataMap headmap = senMap["VISHead"];qDebug()<<"vis head /////:"<<headmap;
    DataMap bodymap = senMap["VISData"];qDebug()<<"vis body \\\\\:"<<bodymap;
    QStringList keysList = bodymap.keys();
    for(int keynum = 0; keynum < keysList.length(); keynum++){
        if(keysList.value(keynum) == "SC_RVR_Alive"){
            if((bodymap["state"].trimmed()).toInt() == 1){
                qDebug()<<"收到RVR设备在线状态";
                ui->label_Rstate->setStyleSheet("QLabel#label_Rstate{border-radius:5px;color: green; background-color:#00FF00;font-size:14px;border-style:none;}");
            }
            if((bodymap["state"].trimmed()).toInt() == 0){
                qDebug()<<"收到RVR设备下线状态";
                ui->label_Rstate->setStyleSheet("QLabel#label_Rstate{border-radius:5px;color: red; background-color:#00FF00;font-size:14px;border-style:none;}");
            }
            return ;
        }
        if(keysList.value(keynum) == "SC_RVR_DataBack"){
            qDebug()<<"私有报文协议数据";
            QMap<QString,QString> dataMap;
            dataMap["AD"] = bodymap["ADValueBack"];
            dataMap["send_temperature"] = bodymap["TxTem"];
            dataMap["send_humidity"] = bodymap["TxHum"];
            dataMap["reciver_temperature"] = bodymap["RxTem"];
            dataMap["reciver_humidity"] = bodymap["RxHum"];
            dataMap["MOR"] = bodymap["MOR"];                   //qDebug()<<"all dataMap"<<dataMap;
            emit privateVisData(QByteArray(),dataMap);
//            return ;////////////
        }
    }
    int index = (headmap["VISID"]).toInt();qDebug()<<"index  IDID:"<<QString("%1").arg(index);
    if(index == 1){
        selectVis(1,ui->lineEdit_Mor,bodymap);
    }
    else{
        return ;
    }
}

void RVR_CurrentStatus::humiTempData(SensorMap senMap)
{
    DataMap headmap = senMap["humAndTempHead"];
    DataMap bodymap = senMap["humAndTempData"];
    QStringList keysList = bodymap.keys();
    for(int keynum = 0; keynum < keysList.length(); keynum++){
        if(keysList.value(keynum) == "SC_HMP155_Alive"){
            if((bodymap["state"].trimmed()).toInt() == 1){
                qDebug()<<"收到TempHum设备在线状态";
                ui->label_htState->setStyleSheet("QLabel#label_htState{border-radius:5px;color: green; background-color:#00FF00;font-size:14px;border-style:none;}");

            }
            if((bodymap["state"].trimmed()).toInt() == 0){
                qDebug()<<"收到TempHum设备下线状态";
                ui->label_htState->setStyleSheet("QLabel#label_htState{border-radius:5px;color: red; background-color:#00FF00;font-size:14px;border-style:none;}");
            }
            return ;
        }
    }
    int index = (headmap["humAndTempID"]).toInt();
    if(index == 1){
        selectHumiTemp(1,bodymap);
    }
}

void RVR_CurrentStatus::showState(bool open)
{
    qDebug()<<"状态显示："<<open;
    if(open){
        ui->label_HT->show();
        ui->label_WIN->show();
        ui->label_RV->show();
        ui->label_htState->show();
        ui->label_windState->show();
        ui->label_Rstate->show();
        ui->label_htState->setStyleSheet("QLabel#label_htState{border-radius:5px;color: gray; background-color:gray;font-size:14px;border-style:none;}");
        ui->label_Rstate->setStyleSheet("QLabel#label_Rstate{border-radius:5px;color: gray; background-color:gray;font-size:14px;border-style:none;}");
        ui->label_windState->setStyleSheet("QLabel#label_windState{border-radius:5px;color: gray; background-color:gray;font-size:14px;border-style:none;}");
    }
    else{
        ui->label_HT->hide();
        ui->label_WIN->hide();
        ui->label_RV->hide();
        ui->label_htState->hide();
        ui->label_windState->hide();
        ui->label_Rstate->hide();
    }
}








