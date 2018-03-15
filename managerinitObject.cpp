#include "rvr_manager.h"
#include "ui_rvr_manager.h"
int RVR_Manager::init_seialInfo()
{
    if(!ser_info){
        ser_info = new SerialInfo();
    }
    if(ser_info){return 1;}
    else{return -1;}
    return -1;
}

int RVR_Manager::init_staupUI()
{
    QStringList coms = ser_info->getSupplyCom();
    if(!startui){
        startui = new RVR_startUI(coms,this);
    }
    if(startui){
        connect(startui,SIGNAL(COM(QString)),this,SLOT(appInit(QString)));// 按照端口初始化VRMNG
        connect(this,SIGNAL(serInitStatus(bool)),startui,SLOT(okOrNo(bool)));// 回应初始化结果
        // connect(startui,SIGNAL(moveSignal(QPoint)),this,SLOT(moveThisWidget(QPoint)));//使登录界面能移动
        startui->setWindowFlags(Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint);
        startui->show();
        return 1;
    }
    else{return -1;}
    return -1;
}

int RVR_Manager::init_turnTimer()
{
    dataUpdateTime = 0;
    updatetimer = new QTimer();
    if(updatetimer){
        connect(updatetimer,SIGNAL(timeout()),this,SLOT(locationLoopUpdate()));
        updatetimer->start(1000);

        return 1;
    }
    else{ return -1;}
    return -1;
}

int RVR_Manager::init_Config()
{
    if(!config){
        config = new RVR_Configobject();
    }
    if(config){
        srialmap = config->getConfigData();
        return 1;
    }
    else{ return -1;}
    return -1;
}

int RVR_Manager::init_database()
{
    if(!databseDue){
        databseDue = new RVR_Data_Due();
    }
    if(databseDue){
        init_sqlite(config->tablesInfo());
        return 1;
    }
    else{
        return -1;
    }
    return -1;
}

void RVR_Manager::init_sqlite(tableInfo tables)
{
    QList<QString> namelits = tables.keys();
    QStringList fielStr;
    QString tableName;
    for(int i = 0;i < namelits.length();i++){
        tableName = namelits.value(i);
        fielStr = tables[tableName];
        databseDue->configDatabaseTable(tableName,fielStr);
    }
    return ;
}

int RVR_Manager::init_dataParse()
{
    if(!dataParse){dataParse = new RVR_DataParse();}
    if(dataParse){ return 1;}
    else{ return -1;}
}

int RVR_Manager::init_commit(QString port)
{
    if(port == "3616"){ //translate way is ZMQ
        init_ZMQ();
        commUse3600();
        //         setParseWriteWay(SerialPraseData,SerialWriteData);
        setParseWriteWay(MessagePraseData,MessageWriteData);
    }
    else if(port == "remote"){  // translate way is DTU CDMA
        init_REMOTE();
        commUseRemote();
        //         setParseWriteWay(SerialPraseData,SerialWriteData);
        setParseWriteWay(MessagePraseData,MessageWriteData);
    }
    else{  //translate way is mainter
        init_COMM();
        commUseSerialCom(port);
        setParseWriteWay(SerialPraseData,SerialWriteData);
    }
    emit serInitStatus(true);
    return 1;
}

int RVR_Manager::init_COMM()
{
    if(!Serial)
    {
        Serial = new SerialPort();
    }
    if(Serial)
    {
        Serial->initSerial();
        return 1;
    }
    else{ return -1;}
    return -1;
}

int RVR_Manager::init_commWrite()
{
    if(!ser_Write)
    {
        ser_Write = new RVR_serialwrite();
    }
    if(ser_Write){
        return 1;
    }
    else
    {
        return -1;
    }
    return -1;
}

int RVR_Manager::init_REMOTE()
{
    if(!remoteTran){
        remoteTran = new SetupThread();
        qDebug()<<"init remote";
    }
    if(remoteTran){
        return 1;
    }
    else
    {
        return -1;
    }
    return -1;
}

int RVR_Manager::init_ZMQ()
{
    if(!zmqworker){
        zmqworker = new RVR_Zmq_Worker();
    }
    if(zmqworker){
        return 1;
    }
    else
    {
        return -1;
    }
    return -1;
}

int RVR_Manager::init_rvrTool()
{
    if(!seri_mess)
    {
        seri_mess = new Serial_Message();
    }
    if(seri_mess)
    {
        seri_mess->initDir(QApplication::applicationDirPath());
        return 1;
    }
    else
    {
        return -1;
    }
    return -1;
}

int RVR_Manager::init_logStore()
{
    if(!logInfo)
    {
        logInfo = new RVR_LogOutStore();
    }
    if(logInfo)
    {
        logInfo->setfilePath(QApplication::applicationDirPath());
        return 1;
    }
    else{ return -1;}
    return -1;
}
void RVR_Manager::init_managerUI(){
    alignmentUi = new RVR_Alignment();
    alignmentUi->hide();
    currentStatusUi = new RVR_CurrentStatus(this);
    currentStatusUi->hide();

    if(messParse){
        currentStatusUi->init_message_data_tempHumUI();
        currentStatusUi->showState(true);
        ui->groupBox->hide();
    }
    calibrationUi = new RVR_Calibration();
    calibrationUi->hide();
    lineartestUi = new RVR_LinearTest();
    lineartestUi->setBaseline(config->getBaseLineLength());
    lineartestUi->setWindRainCover(config->getWindRainCover());
    lineartestUi->hide();
    defaultConUi = new RVR_DefaultConfig();
    defaultConUi->setDefaultInfo(srialmap);
    defaultConUi->hide();
    currentConUi = new RVR_Currentconfig();
    currentConUi->setSeialPort(this->currentPort);
    currentConUi->hide();
    defaultSetUi = new RVR_DefaultSet();
    defaultSetUi->setDefaultdata(srialmap);
    defaultSetUi->setBaseLine(config->getBaseLineLength());
    defaultSetUi->setWindRainCover(config->getWindRainCover());
    defaultSetUi->hide();
    RVRCalc  = new RVR_Calc_values();
    RVRCalc->hide();
}

int RVR_Manager::init_MessageParse()
{
    if(!messParse){
        messParse = new MessageParse(this);
    }
    if(messParse){return 1;}
    else{return -1;}
    return -1;
}
