#include "serial_message.h"
#include "ui_serial_message.h"
#include <QDebug>
#include <QDate>
#include "mess/RVR_Reminder_Msg.h"


Serial_Message::Serial_Message(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Serial_Message)
{
    ui->setupUi(this);
    //数据导出处理
    outputTimer = new QTimer();
    writeFlage = false;
    connect(outputTimer,SIGNAL(timeout()),this,SLOT(outputDatabase()));
    outputTimer->start(500);
    //数据导出进度
    outputedLines = 0;
    lineTotal = 0;
    connect(this,SIGNAL(outputProgresssSignal(int)),
            this,SLOT(ouputProgresss(int)));
    ui->progressBar_outputProgress->hide();
    //设置程序退出操作
    this->setAttribute(Qt::WA_QuitOnClose,false);

    ui->textEditReci->setReadOnly(true);
    isSaveExcel = true;
    QString messHead = formatContrl(6,"");
    messHead += formatContrl(14,"时间");
    messHead += formatContrl(5,"AD");
    messHead += formatContrl(6,"MOR值");
    messHead += formatContrl(6,"接收机温度");
    messHead += formatContrl(7,"接收机湿度");
    messHead += formatContrl(7,"发射机温度");
    messHead += formatContrl(5,"发射机湿度\n");

    messlist.push_back(messHead);
    this->setWindowTitle("管理工具");
    ui->pushButtonexcel->setEnabled(false);
    ui->pushButtonexcel->setStyleSheet("color:gray");
    ui->textEditLogShow->setReadOnly(true);
    ui->groupBox_return_set->setGeometry(20,900,701,40);
}

Serial_Message::~Serial_Message()
{
    delete ui;
}

void Serial_Message::initDir(QString pathStr)
{
    this->path = pathStr;
}

void Serial_Message::showData(QByteArray str)
{
    int length = str.size();
    QString strOut,st;
    for(int i = 0 ;i < length;i++){
        strOut += "0x"+st.sprintf("%02X",(uchar)str[i])+" ";
    }
    ui->textEditReci->setText(strOut);
}

void Serial_Message::showLogData(QByteArray,QMap<QString, QString> dataMap)
{
    //给数据打上时间戳
    QString strData = QDate::currentDate().toString("yyyy/MM/dd ")+
            QTime::currentTime().toString("hh:mm:ss")+" ";
    dataMap["time"] = strData;
    //存储日志
    emit storeDatabase(dataMap);
    if(isSaveExcel){
        emit storeExceldata(dataMap);
    }
    else{
        emit storeTxtdata(dataMap);
    }
    //显示日志
    strData += formatContrl(1,QString(""));
    strData += formatContrl(6,dataMap["AD"]);
    strData += formatContrl(7,dataMap["MOR"]);
    strData += formatContrl(10,dataMap["reciver_temperature"]);
    strData += formatContrl(11,dataMap["reciver_humidity"]);
    strData += formatContrl(11,dataMap["send_temperature"]);
    strData += formatContrl(11,dataMap["send_humidity"]);
    messlist.insert(1,strData+"\n");
    strData = "";
    if(messlist.length() > 15) messlist.removeLast();;
    for(int i = 0;i < messlist.length();i++){
        strData += messlist.value(i);
    }
    ui->textEditLogShow->setPlainText(strData);
}


void Serial_Message::tableData(QList<lineData> tabData)
{
    this->tabledata = tabData;
    this->lineTotal = tabData.length();
    ui->progressBar_outputProgress->setRange(0,tabData.length());
    ui->progressBar_outputProgress->setValue(0);
    ui->pushButton_from_set->setEnabled(false);
    writeFlage = true;
}

void Serial_Message::ouputProgresss(int value)
{
    ui->progressBar_outputProgress->setValue(value);
    if(value == this->lineTotal){
          Reminder_Mseg::showMessageboxInfo("数据导出完毕");
          ui->progressBar_outputProgress->hide();
          ui->pushButton_from_set->setEnabled(true);
          this->outputedLines = 0;
    }
}

void Serial_Message::on_pushButtonSendData_clicked()
{
    char buff[100];
    QString uiData = ui->lineEdit_sendData->text().trimmed();                              //                                                  //**************************qDebug()<<"not NULL"<<(uiData.simplified()).replace(QString(" "),QString(""));
    uiData = (uiData.simplified()).replace(QString(" "),QString(""));                      //                                                  //**************************qDebug()<<"len"<<uiData.length();
    if(uiData.length() % 2 != 0){
        Reminder_Mseg::showMessageboxError("命令字符串出错!");
    }
    int len = uiData.length() / 2;
    bool ok;
    for(int i = 0; i < len;i++){                                                           //                                                   //**************************qDebug()<<"buffData:"<<QString::number(((uiData.mid(2*i,2)).toInt(&ok,16)),10);
        ok = false;
        buff[i] = (uchar)((uiData.mid(2*i,2)).toInt(&ok,16));
    }
    emit sendData("monitor",QByteArray(buff,len));
}

void Serial_Message::on_pushButtonexcel_clicked()
{
    isSaveExcel = true;
    ui->pushButtonexcel->setEnabled(false);
    ui->pushButtonexcel->setStyleSheet("color:gray");
    ui->pushButton_txt->setEnabled(true);
    ui->pushButton_txt->setStyleSheet("color:white");
}

void Serial_Message::on_pushButton_txt_clicked()
{
    isSaveExcel = false;
    ui->pushButton_txt->setEnabled(false);
    ui->pushButton_txt->setStyleSheet("color:gray");
    ui->pushButtonexcel->setEnabled(true);
    ui->pushButtonexcel->setStyleSheet("color:white");
}

void Serial_Message::on_pushButton_from_set_clicked()
{

    emit outputTable("vrmngtable");                    //    ui->groupBox_return_set->setGeometry(20,497,701,40);
    //**************************qDebug()<<"1";                                     //    ui->pushButton_txt->hide();
    ui->progressBar_outputProgress->show();            //    ui->pushButtonexcel->hide();
    //    ui->pushButton_from_set->hide();
}

void Serial_Message::on_pushButtonok_clicked()
{
    ui->groupBox_return_set->setGeometry(20,900,701,40);
    ui->pushButton_txt->show();
    ui->pushButtonexcel->show();
    ui->pushButton_from_set->show();
}

QString Serial_Message::formatContrl(int length ,QString string)
{
    QString str = string;
    int strLength = str.trimmed().length();
    for(int i = strLength;i < length;i++){
        str = str + " ";
    }
    return str;
}


void Serial_Message::outputDatabase()
{
    if(this->tabledata.length() > 0){
        //**************************qDebug()<<"have data";
        if(writeFlage){
            createDataFile();
        }
    }
    //**************************qDebug()<<"not have data ,timer return";
}

void Serial_Message::createDataFile()
{
    this->writeFlage = false;
    int len = this->tabledata.length();
    //定义导出算法变量
    bool nameChangWriteData = false;
    bool jump = false;
    bool excelHead = false;
    bool excelSelect = false;
    int  excerow = 3;
    lineData value;
    value = this->tabledata.value(0);
    QString date = value["datetime"].toString();
    date = date.trimmed();
    QStringList strList = date.split(" ") ;
    //**************************qDebug()<<"日期列表:"<<strList;
    QString datetime = strList.value(0);
    //**************************qDebug()<<"首次解析的日期:"<<datetime;

    if(datetime.length() > 10){
        this->tabledata.removeAt(0);
        this->writeFlage = true;
        //**************************qDebug()<<"非法日期格式:"<<datetime;
        return ;
    }

    QString path = QApplication::applicationDirPath()+"/database/";
    //构造文件路径及名称
    QStringList datelist = datetime.split("/");
    for(int i = 0;i < datelist.length();i++){
        if(i == 0){path = path + datelist.value(0)+"年";}
        else if(i == 1){path = path + datelist.value(1)+"月";}
        else if(i == 2){path = path + datelist.value(2)+"日";}
    }
    path = path+"data.xlsx";
    //**************************qDebug()<<"首次合成的日期:"<<path;
    //判断文件是否存在
    if(file->exists(path)){
        excelHead = true;
        excelSelect = false;
    }
    else{
        excelHead = false;
        excelSelect = false;
        file = new QFile(path);
        file->open(QIODevice::ReadWrite);
        file->close();
    }
    //开始操作Execl数据格式
    QXlsx::Document memeryXlsx(path);
    if(!excelHead){
        excelHead = true;
        memeryXlsx.write("B3","时间");
        memeryXlsx.write("D3","AD值");
        memeryXlsx.write("F3","mor值");
        memeryXlsx.write("H3","发射机温度");
        memeryXlsx.write("J3","发射机湿度");
        memeryXlsx.write("L3","接收机温度");
        memeryXlsx.write("N3","接收机湿度");
    }

    while (!excelSelect) {
        if(((memeryXlsx.read(QString("D%1").arg(excerow))).toString()) == ""){
            excelSelect = true;
            break;
            //**************************qDebug()<<QString("检查到文件%1存在%2条数据。").arg(path).arg(excerow-1);
        }
        excerow++;
    }
    //具体操作每部分数据
    QString subDate;
    for(int i = 0;i < len ;i++){
        value = this->tabledata.at(i);
        //判断数据数据是否为同一个文件
        subDate = value["datetime"].toString();
        subDate = subDate.trimmed();
        subDate = (subDate.split(" ")).value(0);

        //**************************qDebug()<<"开始解析出来的对比日期:"<<datetime<<QString("第%1次解析出来的对比日期:").arg(i)<<subDate;
        if(datetime == subDate)
        {
            //**************************qDebug()<<"16";
        }
        //碰到另外一个文件的数据了把之前的文件数据写出
        else if(datetime != subDate)
        {
            //**************************qDebug()<<"17"<<datetime<<value["datetime"];
            nameChangWriteData = true;
            jump = true;
        }
        //到尾了都是同一个文件中的数据该写出了
        if(i == (len - 1) ){
            //**************************qDebug()<<"18";
            nameChangWriteData = true;
        }

        if(!jump){
            //从缓存中读具体各部分数据填入excel写缓存中。
            //**************************qDebug()<<"19";
            memeryXlsx.write(QString("B%1").arg(excerow + i),value["datetime"].toString());
            memeryXlsx.write(QString("D%1").arg(excerow + i),value["ad"].toDouble());
            memeryXlsx.write(QString("F%1").arg(excerow + i),value["mor"].toDouble());
            memeryXlsx.write(QString("H%1").arg(excerow + i),value["sendtemp"].toDouble());
            memeryXlsx.write(QString("J%1").arg(excerow + i),value["sendhum"].toDouble());
            memeryXlsx.write(QString("L%1").arg(excerow + i),value["recitemp"].toDouble());
            memeryXlsx.write(QString("N%1").arg(excerow + i),value["recihum"].toDouble());
            qDebug()<<QString("导出第%1条数据").arg(i)<<
                      value["datetime"].toString()<<
                      value["ad"].toDouble()<<
                      value["mor"].toDouble()<<
                      value["sendtemp"].toDouble()<<
                      value["sendhum"].toDouble()<<
                      value["recitemp"].toDouble()<<
                      value["recihum"].toDouble();
                      emit outputProgresssSignal(outputedLines++);
        }

        if(nameChangWriteData){
            //只要写数据不成功 直接退出
            if(!(memeryXlsx.saveAs(path))){
                writeFlage = true;
                //**************************qDebug()<<"32";
                return ;
            }
            else
            {                                                  //成功就删除存储成功的那部分数据;
                //**************************qDebug()<<"20";
                int num;

                if(jump){                                      //碰到另外一个文件的数据
                    num = i - 1;
                    //**************************qDebug()<<"21";
                }

                else                                           //都是一个文件中的数据
                {
                    num = len;
                    //**************************qDebug()<<"22";
                }

                for(int j = 0;j <= num;j++){                   //清除已存储的数据
                    this->tabledata.removeAt(0);
                }
                //检查数据是否写出完毕
                if(this->tabledata.length() < 1){
                    emit outputProgresssSignal(this->lineTotal);
                }
                else{
                    writeFlage = true;
                    qDebug()<<"数据条数:"<<len<<"导出条数:"<<(len - tabledata.length());
                }
                return ;
            }
        }
    }
}













