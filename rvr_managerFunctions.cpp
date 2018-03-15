#include "rvr_manager.h"
#include "ui_rvr_manager.h"

#include "mess/RVR_Reminder_Msg.h"
#include <QStatusBar>

//初始化链接函数
void RVR_Manager::init_connections()
{

    // ============== read data =================
    //gyro init data
    qDebug()<<"dataParse:"<<dataParse<<alignmentUi;
    //私有报文形式处理数据
    if(this->parseWay == SerialPraseData)
    {
        connect(dataParse,SIGNAL(gyroInint(QByteArray,QMap<QString,QString>)),alignmentUi,SLOT(update_data(QByteArray,QMap<QString,QString>)));
        connect(dataParse,SIGNAL(waring(QByteArray,QMap<QString,QString>)),alignmentUi,SLOT(waring_signal(QByteArray,QMap<QString,QString>)));
        connect(dataParse,SIGNAL(groyXYZZeroValue(QByteArray,QMap<QString,QString>)),alignmentUi,SLOT(show_groyXYZZeroValue(QByteArray,QMap<QString,QString>)));
        //rvr mor ad gyro real data
        connect(dataParse,SIGNAL(datalist(QByteArray,QMap<QString,QString>)),currentStatusUi,SLOT(current_data_info(QByteArray,QMap<QString,QString>)));
        //calc after rvr value
        connect(dataParse,SIGNAL(RVRData(QByteArray,QMap<QString,QString>)),currentStatusUi,SLOT(current_rvr_data(QByteArray,QMap<QString,QString>)));
        //recover factory
        connect(dataParse,SIGNAL(recover(QByteArray,QMap<QString,QString>)),this,SLOT(recover_message(QByteArray,QMap<QString,QString>)));
        //calibrationValue
        connect(dataParse,SIGNAL(ThresholdValue(QByteArray,QMap<QString,QString>)),calibrationUi,SLOT(cal_fact(QByteArray,QMap<QString,QString>)));
        //clibration message show
        connect(dataParse,SIGNAL(fullScaaleValueSignal(QByteArray,QMap<QString,QString>)),calibrationUi,SLOT(fullScaaleValueSlot(QByteArray,QMap<QString,QString>)));
        connect(dataParse,SIGNAL(calibrationOffsetValue(QByteArray,QMap<QString,QString>)),calibrationUi,SLOT(calibrationOffsetValue(QByteArray,QMap<QString,QString>)));
        //RVrsoftRecover
        connect(dataParse,SIGNAL(RVRSoftRecover(QByteArray,QMap<QString,QString>)),this,SLOT(showRVRRecoverMessage(QByteArray,QMap<QString,QString>)));
        //waring up send
        connect(dataParse,SIGNAL(waringUp(QByteArray,QMap<QString,QString>)),this,SLOT(faultReportWaring(QByteArray,QMap<QString,QString>)));
        //maintain port RVR calc two value
        connect(currentStatusUi,SIGNAL(RVR_calc_option(QString,QMap<QString,QString>)),dataParse,SLOT(maintainRvrCalc(QString,QMap<QString,QString>)));
        //enable maintain port RVR calc
        connect(this,SIGNAL(maintainRVRCalcEnable(bool)),dataParse,SLOT(enableRemainRVR(bool)));
        if(serialCommit || rvrCalcenble) emit maintainRVRCalcEnable(true);
        //defualtset ui show message
        connect(dataParse,SIGNAL(serialInfo(QByteArray,QMap<QString,QString>)),defaultSetUi,SLOT(showOptionMessage(QByteArray,QMap<QString,QString>)));
        connect(dataParse,SIGNAL(lineValue(QByteArray,QMap<QString,QString>)),lineartestUi,SLOT(setTValue(QByteArray,QMap<QString,QString>)));
    }

    if(this->writeWay == SerialWriteData)
    {
        //=============== write data =================
        connect(defaultSetUi,SIGNAL(default_set_option(QString,QMap<QString,QString>)),dataWrite,SLOT(writeData(QString,QMap<QString,QString>)));
        connect(alignmentUi,SIGNAL(groyOption(QString,QMap<QString,QString>)),dataWrite,SLOT(writeData(QString,QMap<QString,QString>)));
        connect(currentStatusUi,SIGNAL(RVR_calc_option(QString,QMap<QString,QString>)),dataWrite,SLOT(writeData(QString,QMap<QString,QString>)));
        connect(calibrationUi,SIGNAL(calibrationOption(QString,QMap<QString,QString>)),dataWrite,SLOT(writeData(QString,QMap<QString,QString>)));
        //update serial
        connect(defaultSetUi,SIGNAL(default_set_option(QString,QMap<QString,QString>)),this,SLOT(updateSerialComm(QString,QMap<QString,QString>)));
        //=============== each other ui objects connection ======
        //defalut and crrent ui connection
        connect(lineartestUi,SIGNAL(lineTest(QString,QMap<QString,QString>)),dataWrite,SLOT(writeData(QString,QMap<QString,QString>)));
    }

    //消息形式处理数据
    if(this->parseWay == MessagePraseData)
    {
        //wind
        connect(messParse,SIGNAL(windDataSignal(SensorMap)),currentStatusUi,SLOT(windData(SensorMap)));
        connect(messParse,SIGNAL(rvrDataSignal(SensorMap)),currentStatusUi,SLOT(rvrData(SensorMap)));
        connect(messParse,SIGNAL(humiTempDataSignal(SensorMap)),currentStatusUi,SLOT(humiTempData(SensorMap)));
        //        connect(messParse,SIGNAL(cloudDataSignal(SensorMap)),awosUI,SLOT(cloudData(SensorMap)));
        //        connect(messParse,SIGNAL(atmospherePressDataSignal(SensorMap)),awosUI,SLOT(atmospherePressData(SensorMap)));
        //        connect(messParse,SIGNAL(rainDataSignal(SensorMap)),awosUI,SLOT(rainData(SensorMap)));
        //        connect(messParse,SIGNAL(phenomenaWeatherDataSignal(SensorMap)),awosUI,SLOT(phenomenaWeatherData(SensorMap)));
        //        connect(messParse,SIGNAL(prevailingVisibilityDataSignal(SensorMap)),awosUI,SLOT(prevailingVisibilityData(SensorMap)));
        //        connect(messParse,SIGNAL(manualInputDataDataSignal(SensorMap)),awosUI,SLOT(manualInputDataData(SensorMap)));

    }

    if(this->writeWay == MessageWriteData)
    {

    }

    //===============*********
    //各部分ui链接部分
    //defalut and crrent ui connection
    connect(defaultSetUi,SIGNAL(current_commit_info(QMap<QString,QString>)),currentConUi,SLOT(getcurrentInfo(QMap<QString,QString>)));
    connect(defaultSetUi,SIGNAL(current_commit_info(QMap<QString,QString>)),config,SLOT(updateCurrentCommit(QMap<QString,QString>)));
    //init baseline and windRain length
    connect(defaultSetUi,SIGNAL(baseSignal(QString)),lineartestUi,SLOT(setBaseline(QString)));
    connect(defaultSetUi,SIGNAL(rainWindSignal(QString)),lineartestUi,SLOT(setWindRainCover(QString)));
    //init rvr calc
    connect(RVRCalc,SIGNAL(calc_Value(QString,QMap<QString,QString>)),currentStatusUi,SIGNAL(RVR_calc_option(QString,QMap<QString,QString>)));
    //各部分ui链接部分
    //===============*********
}

//本地循环时钟
void RVR_Manager::locationLoopUpdate()
{
    dataUpdateTime++;

    // start updata
    if(!openflage&&(dataUpdateTime%2 == 0)){
        startui->updatecoms(ser_info->getSupplyCom());
    }

    // run update
    if(openflage){
        QStringList portList = ser_info->getSupplyCom();
        defaultSetUi->init_UI_data(portList);
        //使用ZMQ通讯（不需要轮询）的时候必须关掉此条，不然会内部冲突，死机。
//        if(dataUpdateTime%12 == 0) //注释掉这个判断条件就成为主动回应，没有轮讯
//        {
//            askDataLoopUpdate();
//        }
        if(dataUpdateTime%4 == 0){
            logInfo->memeryWrite();
        }

        //        if(dataUpdateTime%30 == 0){ //没有0109时要发此心跳
        //             heartbeatLoop();
        //        }
        //        if(dataUpdateTime%3 == 0){
        //            QMap<QString,QString> map;
        //            map["waring_ask"] = "0108";
        //          dataWrite->writeData("waring_ask",map);
        //        }
        //        if(dataUpdateTime%5 == 0){
        //            QMap<QString,QString> map;
        //            map["serial_ask"] = "0108";
        //            dataWrite->writeData("serial_ask",map);
        //        }
        //        if(dataUpdateTime%2 == 0)                                                          //胡工要求关闭此条命令轮寻，还要求关闭ad显示
        //        {
        //            QMap<QString,QString> map;
        //            map["gyro_xyz"] = "0104";
        //            dataWrite->writeData("gyro_xyz",map);
        //        }
    }
}

void RVR_Manager::setParseWriteWay(DataWays parseWay, DataWays writeWay)
{
    this->parseWay = parseWay;
    this->writeWay = writeWay;
}

//重新设置串口通讯属性参数
void RVR_Manager::updateSerialComm(QString option, QMap<QString, QString> data)
{
    if(option != "update_commit") return ;
    if(!serialCommit) return;

    int baud = data["baud"].toInt();
    int dataNum = 0;
    int parity = 0;
    int stopByte = 0;
    ////   2017-2-6
    if(data["stop"].toFloat()== 1.0){
        stopByte = 1;
    }
    else if(data["stop"].toFloat()== 1.5){
        stopByte = 2;
    }
    else if(data["stop"].toFloat()== 2){
        stopByte = 3;
    }
    //    qDebug()<<"验证》》》stop:::"<<QString::number(stopByte);
    /////
    switch (data["datas"].toInt()) {
    case 5:dataNum = 1;
        break;
    case 6:dataNum = 2;
        break;
    case 7:dataNum = 3;
        break;
    case 8:dataNum = 4;
        break;
    default:
        break;
    }
    if(data["parity"] == "无校验")parity = 1;
    if(data["parity"] == "偶校验")parity = 2;
    if(data["parity"] == "奇校验")parity = 3;
    Serial->closeSerial();
    Serial->setopenSerial(StrCom,baud,dataNum,stopByte,parity);
    return ;
}

//初始化维护端口
int RVR_Manager::init_serial(QString comstr){
    this->currentPort = comstr;
    nameList = ser_info->getSupplyCom();
    if(nameList.length() < 1){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,"温馨提示", "没有可用的串行接口!",
                                      QMessageBox::Yes|QMessageBox::Cancel);
        if(reply == QMessageBox::Yes)
        {
            return  -1;
        }
    }
    int baud = this->srialmap["baud"].toInt();
    int dataNum = 0;
    int stopByte = 0;
    int parity = 0;
    switch (this->srialmap["datas"].toInt())
    {
    case 5:dataNum = 1;
        break;
    case 6:dataNum = 2;
        break;
    case 7:dataNum = 3;
        break;
    case 8:dataNum = 4;
        break;
    default:
        break;
    }
    if(this->srialmap["stop"].toFloat()== 1.0)
    {
        stopByte = 1;
    }
    else if(this->srialmap["stop"].toFloat()== 1.5)
    {
        stopByte = 2;
    }
    else if(this->srialmap["stop"].toFloat()== 2)
    {
        stopByte = 3;
    }
    qDebug()<<"stop:::"<<QString::number(stopByte);
    if(this->srialmap["parity"] == "无校验")
    {
        parity = 1;
    }
    if(this->srialmap["parity"] == "偶校验")
    {
        parity = 2;
    }
    if(this->srialmap["parity"] == "奇校验")
    {
        parity = 3;
    }
    bool openFlag;

    openFlag = Serial->setopenSerial(comstr,baud,dataNum,stopByte,parity);

    if(openFlag)
    {
        qDebug()<<"open serial succeed.";
        serialCommit = true;
    }
    else{
        return -1;
    }

    init_commWrite();
    if(ser_Write){
        connect(ser_Write,SIGNAL(send_data(QByteArray,int)),Serial,SLOT(ser_writeData(QByteArray,int)),Qt::QueuedConnection);
    }

    //    if(!ser_Parse)
    //    {
    //        ser_Parse = new RVR_serialparse();
    //        connect(Serial,SIGNAL(newData(QByteArray)),ser_Parse,SLOT(parse_serial(QByteArray)));
    //    }

    //    if(!dataWrite)
    //    {
    //        dataWrite = new RVR_DataWrite();
    //        connect(dataWrite,SIGNAL(writeComm(QByteArray)),ser_Write,SLOT(writeSerial(QByteArray)));
    //    }

    return 1;
}

//初始化3600端口
int RVR_Manager::init_zmq3600()
{
    if(zmqworker->initZmq() < 0){
        emit serInitStatus(false);
        return -1;
    }
    if(zmqworker->setPort() < 0){
        emit serInitStatus(false);
        return -1;
    }

    //    //use serial parse private message commd
    //    if(!ser_Parse)
    //    {
    //        ser_Parse = new RVR_serialparse();
    //        connect(zmqworker,SIGNAL(newData(QByteArray)),ser_Parse,SLOT(parse_serial(QByteArray)));
    //    }

    //    //use message private message commd
    //    if(!dataWrite)
    //    {
    //        dataWrite = new RVR_DataWrite();
    //        connect(dataWrite,SIGNAL(writeComm(QByteArray)),zmqworker,SLOT(writezmq(QByteArray)));
    //    }
    return 1;
}

//初始化远程传输端口
int RVR_Manager::init_Transfer()
{
    //    if(init_messParse() > 0){
    //        qDebug()<<"messgae init ok.";
    //        connect(remoteTran,SIGNAL(reciMessage(QByteArray)),
    //                messParse,SLOT(getMessageBarry(QByteArray)));
    //    }

    //use serial parse private message commd
    //    if(!ser_Parse)
    //    {
    //        ser_Parse = new RVR_serialparse();
    //        connect(remoteTran,SIGNAL(reciMessage(QByteArray)),ser_Parse,SLOT(parse_serial(QByteArray)));
    //    }
    //    //use message private message commd
    //    if(!dataWrite)
    //    {
    //        dataWrite = new RVR_DataWrite();
    //        connect(dataWrite,SIGNAL(writeComm(QByteArray)),remoteTran,SIGNAL(writeCDMA(QByteArray)));
    //    }
    return 1;
}

//report the waring informations
void RVR_Manager::faultReportWaring(QByteArray /*softInfo*/, QMap<QString, QString> dataMap)
{
    qDebug()<<"map"<<dataMap;
    bool reciflage = false,sendFlage = false,fault485Flage = false;
    QString waringStr = "接收机",warStr;
    if(dataMap["reci_temp_down"] == "yes"){
        waringStr += "温度超低,";
        reciflage = true;
    }

    if(dataMap["reci_temp_hight"] == "yes"){
        waringStr += "温度超高,";
        reciflage = true;
    }

    if(dataMap["reci_hum_out_standard"] == "yes"){
        waringStr += "湿度超标,";
        reciflage = true;
    }

    if(reciflage){
        warStr += waringStr;
    }

    waringStr = "发射机";
    if(dataMap["send_temp_down"] == "yes")
    {
        waringStr += "温度超低,";
        sendFlage = true;
    }

    if(dataMap["send_temp_hight"] == "yes")
    {
        waringStr += "温度超高,";
        sendFlage = true;
    }

    if(dataMap["send_hum_out_standard"] == "yes")
    {
        waringStr += "湿度超标,";
        sendFlage = true;
    }

    if(sendFlage){
        warStr += waringStr;
    }

    waringStr = "485通讯";
    if(dataMap["485_line_woring"] == "yes"){
        waringStr += "故障";
        fault485Flage = true;
    }

    if(fault485Flage){
        warStr += waringStr;
    }
    qDebug()<<"warStr"<<warStr;
    if((fault485Flage == true) || (sendFlage == true) || (reciflage == true)){
        ui->label_Waring->setStyleSheet("QLabel#label_Waring{border-radius:10px;color: gray; background-color:#FF0000;font-size:14px;border-style:none;}");
        ui->label_WaringText->setText(warStr.trimmed());
    }
    else{
        ui->label_Waring->setStyleSheet("QLabel#label_Waring{border-radius:10px;color: gray;background-color:#00FF00;font-size:14px;border-style:none;}");
        ui->label_WaringText->setText("当前状况良好");
    }
    return ;
}

void RVR_Manager::showRVRRecoverMessage(QByteArray /*softInfo*/, QMap<QString, QString> /*dataMap*/)
{
    Reminder_Mseg::showMessageboxInfo("RVR软件复位成功.");
}

void RVR_Manager::sqlLiteStore(QMap<QString, QString> dataMap)
{
    if(!databseDue) return ;
    QVariantList list;
    list<<dataMap["time"];
    list<<(dataMap["AD"]).toInt();
    list<<(dataMap["MOR"]).toInt();
    list<<(dataMap["reciver_temperature"]).toInt();
    list<<(dataMap["reciver_humidity"]).toInt();
    list<<(dataMap["send_temperature"]).toInt();
    list<<(dataMap["send_humidity"]).toInt();
    databseDue->addData("vrmngtable",list);
}

