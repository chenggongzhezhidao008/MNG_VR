#include "rvr_logoutstore.h"
#include <QDate>
#include <QTime>

RVR_LogOutStore::RVR_LogOutStore(QObject *parent) :
    QObject(parent)
{
    path = "";
    file = NULL;
    textHead = false;
    excelHead = false;
    excelSelect = false;
    excerow = 3;
    lastFileName = "rvrName";
    memeryLastFileName = "memeryRvrName";
    writeFlage = true;
    headStr = "        时间          AD值     mor值    发射机温度    发射机湿度   接收机温度  接收机湿度 \r\n";
    connect(this,SIGNAL(lostdata(QMap<QString,QString>)),this,SLOT(saveLostData(QMap<QString,QString>)));
    backnumber = 0;
}

void RVR_LogOutStore::setfilePath(QString globalPath)
{
    this->path = globalPath+"/logdata/";
                                                       //**************************qDebug()<<"store file path:"<<this->path;
    return ;
}

void RVR_LogOutStore::TxtStoreFile(QMap<QString, QString> dataMap)
{
                                                   //**************************qDebug()<<"storeTXTmap:"<<dataMap;
    QString str = dataMap["time"]+"   "+ dataMap["AD"] + "       " +
            dataMap["MOR"] + "          " +
            dataMap["send_temperature"]  + "           " +
            dataMap["send_humidity"]+ "            " +
            dataMap["reciver_temperature"]  + "          " +
            dataMap["reciver_humidity"] +"\r\n";
    if(!file){
        if(file->exists(this->path+QDate::currentDate().toString("yyyy年MM月dd日")+"log.txt"))
            textHead = true;
        else
            textHead = false;
        file = new QFile(this->path+QDate::currentDate().toString("yyyy年MM月dd日")+"log.txt");
    }
    if( file->open(QIODevice::Append)){
        QTextStream stream(file);
        if(!textHead){
            stream <<headStr;
            textHead = true;
        }
        stream<<str;
        stream.flush();
        file->close();
    }
    else return ;
}

void RVR_LogOutStore::ExcelStoreFile(QMap<QString, QString> dataMap)
{
    //不同文件使用不同的行数标记号
    pathStr = this->path+QDate::currentDate().toString("yyyy年MM月dd日")+"log.xlsx";
    if(file->exists(pathStr)){
        excelHead = true;
        if(lastFileName != pathStr){
            lastFileName = pathStr;
            excerow = 3;
            excelSelect = false;
        }
    }
    else{
        lastFileName = pathStr;
        excelHead = false;
        excerow = 3;
        excelSelect = false;
        file = new QFile("pathStr");
        file->open(QIODevice::ReadWrite);
        file->close();
    }

    QXlsx::Document xlsxFomat(pathStr);

    if(!excelHead){
        excelHead = true;
        xlsxFomat.write("B3","时间");
        xlsxFomat.write("D3","AD值");
        xlsxFomat.write("F3","mor值");
        xlsxFomat.write("H3","发射机温度");
        xlsxFomat.write("J3","发射机湿度");
        xlsxFomat.write("L3","接收机温度");
        xlsxFomat.write("N3","接收机湿度");
        xlsxFomat.saveAs(pathStr);
    }

    while (!excelSelect) {
        if(((xlsxFomat.read(QString("D%1").arg(excerow))).toString()) == ""){
            excelSelect = true;
            break;
                                                           //**************************qDebug()<<QString("检查到文件%1存在%2条数据。").arg(pathStr).arg(excerow-1);
        }
        excerow++;
    }

    if(!(xlsxFomat.write(QString("B%1").arg(excerow),(dataMap["time"].trimmed())))){
        writeFlage = false;
        dataMap["row"] = QString::number(excerow,10);
        emit lostdata(dataMap);
    }
    else{
        xlsxFomat.write(QString("D%1").arg(excerow),(dataMap["AD"].trimmed()).toDouble());
        xlsxFomat.write(QString("F%1").arg(excerow),(dataMap["MOR"].trimmed()).toDouble());
        xlsxFomat.write(QString("H%1").arg(excerow),(dataMap["send_temperature"].trimmed()).toDouble());
        xlsxFomat.write(QString("J%1").arg(excerow),(dataMap["send_humidity"].trimmed()).toDouble());
        xlsxFomat.write(QString("L%1").arg(excerow),(dataMap["reciver_temperature"].trimmed()).toDouble());
        xlsxFomat.write(QString("N%1").arg(excerow),(dataMap["reciver_humidity"].trimmed()).toDouble());
    }

    if(!xlsxFomat.saveAs(pathStr)){
        writeFlage = false;
        dataMap["row"] = QString::number(excerow,10);
        dataMap["savePath"] = pathStr;
        emit lostdata(dataMap);
    }
    excerow++;
    return ;
}

//if memerylist length gt 200 will write out other file
void RVR_LogOutStore::memeryWrite() //实时数据存储,完整性算法函数
{
    if(writeFlage){
        return;
    }
    int len = memerylist.length();
    if(len < 1) {
        return ;
    }
                                                   //**************************qDebug()<<"1";
    bool nameChangWriteData = false;
    bool jump = false;

    QMap<QString,QString> map = memerylist.at(0);
    QString pathsub = map["savePath"];
    QXlsx::Document memeryXlsx(pathsub);
    memeryLastFileName = map["savePath"];
                                                   //**************************qDebug()<<"save path:"<<memeryLastFileName;
    for(int i = 0;i < len ;i++){
        QMap<QString,QString> value = memerylist.at(i);

        //补写数据判断文件情况
        if(memeryLastFileName == value["savePath"])
        {
                                                           //**************************qDebug()<<"2";;
        }
        else if(memeryLastFileName != value["savePath"])   //碰到另外一个文件的数据了把之前的文件数据写出
        {
                                                           //**************************qDebug()<<"3";
            nameChangWriteData = true;
            jump = true;
        }

        if(i == (len - 1) ){           //到尾了都是同一个文件中的数据该写出了
                                                           //**************************qDebug()<<"5";
            nameChangWriteData = true;
        }

        if(!jump){
                                                           //**************************qDebug()<<"8";
            //从缓存中读具体各部分数据填入excel写缓存中。
            memeryXlsx.write(QString("B%1").arg(value["row"]),(value["time"].trimmed()));
            memeryXlsx.write(QString("D%1").arg(value["row"]),(value["AD"].trimmed()).toDouble());
            memeryXlsx.write(QString("F%1").arg(value["row"]),(value["MOR"].trimmed()).toDouble());
            memeryXlsx.write(QString("H%1").arg(value["row"]),(value["send_temperature"].trimmed()).toDouble());
            memeryXlsx.write(QString("J%1").arg(value["row"]),(value["send_humidity"].trimmed()).toDouble());
            memeryXlsx.write(QString("L%1").arg(value["row"]),(value["reciver_temperature"].trimmed()).toDouble());
            memeryXlsx.write(QString("N%1").arg(value["row"]),(value["reciver_humidity"].trimmed()).toDouble());
        }

        //名称改变必须写数据了
        if(nameChangWriteData){
            if(!(memeryXlsx.saveAs(pathsub))){  //只要写数据不成功 直接退出
                                                               //**************************qDebug()<<"110";
                return ;
            }
            else
            {                                         //成功就删除存储成功的那部分数据;
                                                               //**************************qDebug()<<"6";
                int num;
                if(jump){                          //碰到另外一个文件的数据
                    num = i - 1;
                                                                   //**************************qDebug()<<"10";
                }
                else                              //都是一个文件中的数据
                {
                    num = len;
                                                                   //**************************qDebug()<<"9";
                }

                for(int j = 0;j <= num;j++){                 //清除已存储的数据
                                                                   //**************************qDebug()<<"clear:"<<memerylist.value(0);
                    memerylist.removeAt(0);
                }

                if(memerylist.length() < 1){      //检查数据是否写出完毕
                                                                   //**************************qDebug()<<"7";
                    writeFlage = true;
                }
                return ;
            }
        }
    }
}

void RVR_LogOutStore::saveLostData(QMap<QString, QString> dataMap)
{
                                                   //**************************qDebug()<<"faild:"<<dataMap;
    memerylist.push_back(dataMap);
}


