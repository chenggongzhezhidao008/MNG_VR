#include "rvr_manager.h"
#include "ui_rvr_manager.h"

#include "mess/RVR_Reminder_Msg.h"
#include <QStatusBar>


RVR_Manager::RVR_Manager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RVR_Manager)
{
    ui->setupUi(this);
    this->setGeometry(270,40,920,644);
    this->setAttribute(Qt::WA_QuitOnClose,true);
    this->setWindowTitle("VRMNG");
    rvrCalcenble = false;
    openflage = false;
    havecoms = false;
    parseWay = NotWay;
    writeWay = NotWay;
    ui->label_Waring->hide();
    ui->label_WaringText->hide();

    //functions
    init_Config();
    init_seialInfo();
    init_staupUI();
    init_turnTimer();
    init_database();
}

RVR_Manager::~RVR_Manager()
{
    delete ui;
}

// ================== init app functions ===============
void RVR_Manager::appInit(QString comName)
{
    this->StrCom = comName;
    if(init_commit(comName) < 0)
    {
        qDebug()<<"通讯初始化失败！";
        return ;
    }
    // init data due
    init_dataDue();

    //  init ui
    init_managerUI();

    //  init connections
    init_connections();

    //==============****************
    //调试工具部分
    // init rvr manager tool
    init_rvrTool();
    // put  Database out
    connect(seri_mess,SIGNAL(outputTable(QString)),this,SLOT(outputDatabaseData(QString)));//导出数据库中的RVr设备数据
    connect(this,SIGNAL(databaseData(QList<lineData>)),seri_mess,SLOT(tableData(QList<lineData>)));//数据库建表
    // log data source connect
    if(Serial)
    {
        connect(Serial,SIGNAL(newData(QByteArray)),seri_mess,SLOT(showData(QByteArray)));//显示收取数据16进制
    }
    if(zmqworker)
    {
        connect(zmqworker,SIGNAL(newData(QByteArray)),seri_mess,SLOT(showData(QByteArray)));//显示收取数据16进制
    }
    if(remoteTran)
    {
        connect(remoteTran,SIGNAL(reciMessage(QByteArray)),seri_mess,SLOT(showData(QByteArray)));//显示收取数据16进制
    }

    if(this->parseWay == SerialPraseData) //私有协议下的数据存储
    {
        connect(dataParse,SIGNAL(datalist(QByteArray,QMap<QString,QString>)),seri_mess,SLOT(showLogData(QByteArray,QMap<QString,QString>)));
        connect(seri_mess,SIGNAL(sendData(QString,QByteArray)),dataWrite,SLOT(writeMonitor(QString,QByteArray)));
    }
    if(this->parseWay == MessagePraseData)//消息协议下的数据存储
    {
        connect(currentStatusUi,SIGNAL(privateVisData(QByteArray,QMap<QString,QString>)),seri_mess,SLOT(showLogData(QByteArray,QMap<QString,QString>)));
    }
    seri_mess->hide();
    //  调试工具部分
    //==============****************


    //==============****************
    //私有报文RVR数据存储和导出部分
    // init log data store
    logInfo = new RVR_LogOutStore();
    logInfo->setfilePath(QApplication::applicationDirPath());

    //database store set
    connect(seri_mess,SIGNAL(storeDatabase(QMap<QString,QString>)),this,SLOT(sqlLiteStore(QMap<QString,QString>)));
    // excel store set
    connect(seri_mess,SIGNAL(storeExceldata(QMap<QString,QString>)),logInfo,SLOT(ExcelStoreFile(QMap<QString,QString>)));
    // txt store set
    connect(seri_mess,SIGNAL(storeTxtdata(QMap<QString,QString>)),logInfo,SLOT(TxtStoreFile(QMap<QString,QString>)));
    //私有报文RVR数据存储和导出部分
    //==============****************

    //==============***************
    //初始化成功标志
    openflage = true;
    //初始化成功标志
    //==============***************

    // open first ui
    subWin = new QMdiSubWindow();
    subWin->setGeometry(0,0,900,600);
    subWin->setMinimumSize(900,600);
    subWin->setMaximumSize(900,600);
    openWin = ui->mdiArea->addSubWindow(subWin,Qt::FramelessWindowHint);
    subWin->setWidget(currentStatusUi);
    currentStatusUi->show();

    // =================*******************
    //显示告警状态部分 RVR私有报文协议才有
    ui->label_Waring->show();
    ui->label_Waring->setEnabled(false);
    ui->label_Waring->setStyleSheet("QLabel#label_Waring{border-radius:10px;color: gray; background-color:#00FF00;font-size:14px;border-style:none;}");
    ui->label_WaringText->show();
    //显示告警状态部分 RVR私有报文协议才有
    // =================*******************

    //================***********
    //显示主页部分
    defaultSetUi->setCurrentData();
    //显示主页部分
    //================***********
}

// ================== appinit sub functions ============

void RVR_Manager::quit_app(bool flage)
{
    if(flage){
        this->eventclosed->accept();
    }
    else{
        this->eventclosed->ignore();
    }
}

int RVR_Manager::commUse3600()
{
    if(init_zmq3600() < 0){
        emit serInitStatus(false);
        return -1;
    }
    else {
        serialCommit = false;
        rvrCalcenble = true;//打开zmq的RVR计算
        return 1;
    }
    return -1;
}

int RVR_Manager::commUseRemote()
{
    if(init_Transfer() < 0){
        emit serInitStatus(false);
        return -1;
    }
    else {
        serialCommit = false;
        rvrCalcenble = true;
        return 1;
    }
    return -1;
}

int RVR_Manager::commUseSerialCom(QString port)
{
    if (init_serial(port) < 0){
        emit serInitStatus(false);
        return -1;
    }
    return 1;
}

void RVR_Manager::init_dataDue()
{
    selectDataParseWay(this->parseWay);
    selectDataWriteWay(this->writeWay);
}

void RVR_Manager::selectDataParseWay(DataWays way)
{
    if(way == SerialPraseData)//use serial parse private message commd
    {
        qDebug()<<"DataWay::SerialPraseData";
        // serial data parse
        if(!ser_Parse){
            ser_Parse = new RVR_serialparse();
        }
        if(zmqworker){
            connect(zmqworker,SIGNAL(newData(QByteArray)),ser_Parse,SLOT(parse_serial(QByteArray)));
        }
        if(remoteTran){
            connect(remoteTran,SIGNAL(reciMessage(QByteArray)),ser_Parse,SLOT(parse_serial(QByteArray)));
        }
        if(Serial){
            connect(Serial,SIGNAL(newData(QByteArray)),ser_Parse,SLOT(parse_serial(QByteArray)));
        }

        //private from data prase
        init_dataParse();
        connect(ser_Parse,SIGNAL(mess_Data(QString,QByteArray)),dataParse,SLOT(dataParse(QString,QByteArray)));
    }
    else if(way == MessagePraseData)
    {
        qDebug()<<"DataWay::MessagePraseData";
        if(init_MessageParse() > 0){qDebug()<<"data due way is message";}
        if(zmqworker){
            connect(zmqworker,SIGNAL(newData(QByteArray)),messParse,SLOT(getMessageBarry(QByteArray)));
        }
        if(remoteTran){
            connect(remoteTran,SIGNAL(reciMessage(QByteArray)),messParse,SLOT(getMessageBarry(QByteArray)));
        }
    }
    else{
        return ;
    }
}

void RVR_Manager::selectDataWriteWay(DataWays way)
{
    if(way == SerialWriteData)//use message private message commd
    {
        qDebug()<<"DataWay::SerialWriteData";
        if(!dataWrite){
            dataWrite = new RVR_DataWrite();
        }
        if(zmqworker){
            connect(dataWrite,SIGNAL(writeComm(QByteArray)),zmqworker,SLOT(writezmq(QByteArray)));
        }
        if(remoteTran){
            connect(dataWrite,SIGNAL(writeComm(QByteArray)),remoteTran,SIGNAL(writeCDMA(QByteArray)));
        }
        if(ser_Write){
            connect(dataWrite,SIGNAL(writeComm(QByteArray)),ser_Write,SLOT(writeSerial(QByteArray)));
        }
    }
    else if(way == MessageWriteData)
    {
        qDebug()<<"DataWay::MessageWriteData";
    }
    else{
        return ;
    }
}

void RVR_Manager::outputDatabaseData(QString tableName)
{
    emit databaseData(databseDue->getData(tableName));
}

// ================== location functions ===============
void RVR_Manager::askDataLoopUpdate()
{
    QMap<QString,QString> map;
    map["ask_data"] = "0109";
    dataWrite->writeData("data_info_ask",map);
}

void RVR_Manager::heartbeatLoop()
{
    QMap<QString,QString> map;
    map["hearbeat"] = "heart";
    dataWrite->writeData("hearbeat",map);
}

//show  widget from
void RVR_Manager::defaultShow(QWidget *Widget)
{
    if(openWin->widget()!= Widget){
        ui->mdiArea->removeSubWindow(openWin);
        subWin->setWidget(Widget);
        openWin = ui->mdiArea->addSubWindow(subWin,Qt::FramelessWindowHint);
        Widget->show();
    }
    else
        return ;
}

//recover factory set message show slot
void RVR_Manager::recover_message(QByteArray /*softInfo*/, QMap<QString, QString> dataMap)
{
    if(dataMap["recover"] == "ok"){
        Reminder_Mseg::showMessageboxInfo("已成功恢复出厂设置");
    }
    else return ;
}

// ================== option slots =====================
void RVR_Manager::on_actionAlignment_triggered()
{
    if( openflage == false) return ;
    defaultShow(alignmentUi);
    return ;
}

void RVR_Manager::on_actionCalibration_triggered()
{
    if( openflage == false) return ;
    defaultShow(calibrationUi);
}

void RVR_Manager::on_actionLinearTest_triggered()
{
    if( openflage == false) return ;
    defaultShow(lineartestUi);
}

void RVR_Manager::on_actionDefaultSet_triggered()
{
    if( openflage == false) return ;
    defaultShow(defaultSetUi);
}

void RVR_Manager::on_actionCurrentconfig_triggered()
{
    if( openflage == false) return ;
    defaultShow(currentConUi);
}

void RVR_Manager::on_actionDefaultConfig_triggered()
{
    if( openflage == false) return ;
    defaultShow(defaultConUi);
}

void RVR_Manager::on_actionCurrentstatus_triggered()
{
    if( openflage == false) return ;
    defaultShow(currentStatusUi);
}

void RVR_Manager::on_action_triggered()
{
    if( openflage == false) return ;
    if(seri_mess->isHidden()){
        seri_mess->show();
    }
    else{
        seri_mess->show();
        Reminder_Mseg::showMessageboxInfo("管理工具已经打开\n请查看状态栏显示.");
    }
    return ;
}

void RVR_Manager::on_action_soft_reset_triggered()
{
    if( openflage == false) return ;
    QString str = "RVR软件复位";
    Reminder_Mseg::showMessageboxQuestion(str);
}

void RVR_Manager::closeEvent(QCloseEvent *e)
{
    this->eventclosed = e;
    Reminder_Mseg::showMessageboxQuestion("确定要退出VRMNG吗？");
}

void RVR_Manager::on_action_Version_triggered()
{
    Reminder_Mseg::showMessageboxInfo("当前版本为 VRMNG1.0.0");
}

void RVR_Manager::on_action_exit_triggered()
{
    this->close();
}

void RVR_Manager::on_actionRVR_triggered()
{
    if(RVRCalc)
    {
        RVRCalc->setWindowFlags(Qt::WindowStaysOnTopHint);
        RVRCalc->show();
    }
    else{
        return ;
    }
}
