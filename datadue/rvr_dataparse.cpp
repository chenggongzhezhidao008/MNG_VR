#include "rvr_dataparse.h"
#include <qmath.h>

RVR_DataParse::RVR_DataParse(QObject *parent) :
    QObject(parent)
{
    this->i =100 ;
    this->et=0.008 ;
}


void RVR_DataParse::dataParse(QString mess_type,QByteArray data)
{
    QByteArray softinfo,datainfo;
    softinfo.push_back(data.mid(4,9));
    softinfo.push_back(data.mid(16,2));
    int datalegth = (uchar)data[21]*16*16 + (uchar)data[22];
    if(datalegth>2){
        datainfo.push_back((uchar)0x01);
        datainfo.push_back(data.mid(25,datalegth-2));
    }
    else{
        datainfo.push_back((uchar)0x02);
    }
    qDebug()<<"softinfo:"<<softinfo.toHex();
    qDebug()<<"datainfo:"<<datainfo.toHex();

    if(mess_type == "sensor_base_info") baseInfoParse(softinfo,datainfo);
    else if(mess_type == "serial_info_set") serialParse(softinfo,datainfo);
    else if(mess_type == "enable_set") enableParse(softinfo,datainfo);
    else if(mess_type == "gyro_init") gyroInitParse(softinfo,datainfo);
    else if(mess_type == "threshold_value_set")Threshold(softinfo,datainfo);
    else if(mess_type == "sender_value_set") senderMachineConfParse(softinfo,datainfo);
    else if(mess_type == "RVR_value_calc")/*emit Rvr(softinfo,datainfo)*/;
    else if(mess_type == "waring_set") waringParse(softinfo,datainfo);
    else if(mess_type == "data_info") dataInfoParse(softinfo,datainfo);
    else if(mess_type == "work_model") workModleParse(softinfo,datainfo);
    else if(mess_type == "recover_first") recoverFactoryParse(softinfo,datainfo);
    else if(mess_type == "RVR_data") RVRCalcData(softinfo,datainfo);
    else if(mess_type == "wraing_up_send")WaringUpSend(softinfo,datainfo);
    else if(mess_type == "groy_xyz_zero")groyXYZZero(softinfo,datainfo);
    else if(mess_type == "full_scale_info")fullScaleInfo(softinfo,datainfo);
    else if(mess_type == "offset_value_info")offsetValueInfo(softinfo,datainfo);
    else if(mess_type == "RVR_soft_recover")RVRSoftRecover(softinfo,datainfo);
    else if(mess_type == "line_test_value")lineTestValue(softinfo,datainfo);
    else return ;
}



//Sensor 基本信息解析
//7E 5A [00 00] 01 ff ff 00 00 02 [00 00]
//01 01 00 02 00 [00 00] 01 01
//data{00 00 00 00 00 00} 11 55
void RVR_DataParse::baseInfoParse(QByteArray softinfo, QByteArray datainfo)
{
    QMap<QString,QString> dataMap;
    QString str;
    dataMap["type"] = str.sprintf("%02X",(uchar)datainfo[1]);
    dataMap["hardversions"] = str.sprintf("%02X",(uchar)datainfo[2]);
    dataMap["softversions"] = str.sprintf("%02X",(uchar)datainfo[3]);
    emit baseInfo(softinfo,dataMap);
}

//串口信息解析 -return
//7E 5A [00 17] 01 ff ff 00 00 02 [00 0e]
//01 01 00 02 00 [00 06] 01 02 data{00 00 00 00}11 55
//
void RVR_DataParse::serialParse(QByteArray softinfo,QByteArray /*datainfo*/)
{
    QMap<QString,QString> dataMap;
    //    int baud = 0;
    //    baud = (int)((uchar)datainfo[1]);
    //    switch (baud) {
    //    case 1:dataMap["baud"] = "4800";
    //        break;
    //    case 2:dataMap["baud"] = "9600";
    //        break;
    //    case 3:dataMap["baud"] = "19200";
    //        break;
    //    case 4:dataMap["baud"] = "57600";
    //        break;
    //    case 5:dataMap["baud"] = "115200";
    //        break;
    //    default:
    //        break;
    //    }
    //    int datas = (int)((uchar)datainfo[2]);
    //    switch (datas) {
    //    case 1:dataMap["datas"] = "5";
    //        break;
    //    case 2:dataMap["datas"] = "6";
    //        break;
    //    case 3:dataMap["datas"] = "7";
    //        break;
    //    case 4:dataMap["datas"] = "8";
    //        break;
    //    default:
    //        break;
    //    }
    //    int parity = (int)((uchar)datainfo[3]);
    //    switch (parity) {
    //    case 1:dataMap["parity"] = "无校验";
    //        break;
    //    case 2:dataMap["parity"] = "偶校验";
    //        break;
    //    case 3:dataMap["parity"] = "奇校验";
    //        break;
    //    default:
    //        break;
    //    }
    //    dataMap["stop"] = "1";
    dataMap["data_info"] = "通讯设置成功";
    emit serialInfo(softinfo,dataMap);
}

//数据信息解析 -return
//7E 5A [00 33] 01 ff ff  00 00 02 [00 2a]
//01 01 00 02 00 [00 22] 01 09
//data{ 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00} 11 55
//
void RVR_DataParse::dataInfoParse(QByteArray softinfo,QByteArray datainfo)
{
    if(datainfo.length()<2){
        return ;
    }
    QMap<QString,QString> dataMap;
    int adlen = ((int)((uchar)datainfo[1]))*16*16 + ((int)((uchar)datainfo[2]));
    dataMap["AD"] = QString::number(adlen,10);
    dataMap["send_temperature"] = QString::number(((int)((uchar)datainfo[3])),10);
    dataMap["send_humidity"] = QString::number(((int)((uchar)datainfo[4])),10);
    dataMap["reciver_temperature"] = QString::number(((int)((uchar)datainfo[5])),10);
    dataMap["reciver_humidity"] = QString::number(((int)((uchar)datainfo[6])),10);

    //gyro datas
    dataMap["send_gyro_X"] = QString("%1").arg((datainfo.mid(7,4)).toFloat());
    dataMap["send_gyro_Y"] = QString("%1").arg((datainfo.mid(11,4)).toFloat());
    dataMap["send_gyro_Z"] = QString("%1").arg((datainfo.mid(15,4)).toFloat());
    dataMap["reci_gyro_X"] = QString("%1").arg((datainfo.mid(19,4)).toFloat());
    dataMap["reci_gyro_X"] = QString("%1").arg((datainfo.mid(23,4)).toFloat());
    dataMap["reci_gyro_X"] = QString("%1").arg((datainfo.mid(27,4)).toFloat());

    int mor = ((int)((uchar)datainfo[31]))*16*16 + ((int)((uchar)datainfo[32]));
    dataMap["MOR"] = QString::number(mor,10);
    qDebug()<<"reciver data:"<<dataMap;
    //维护 端口 RVR 计算
    if(this->RVR_enable){
        double rvr = RVR_value_calc(mor,this->i,this->et);
        if(((double)mor) > rvr){
            dataMap["rvr_value"] = QString::number(mor);
        }
        else{
            dataMap["rvr_value"] = QString("%1").arg(rvr);
        }
//        qDebug()<<QString("mor:%1,rvr:%2").arg(mor).arg(rvr);
    }
    emit datalist(softinfo,dataMap);
}

//陀螺仪初始化解析 - return
//7E 5A [00 15] 01 ff ff 00 00 02 [00 13]
//01 01 00 02  00 [00 0b] 01 04
//data{00 00 00 00 00 00 00 00 00} 11 55
//
void RVR_DataParse::gyroInitParse(QByteArray softinfo, QByteArray datainfo)
{
    QMap<QString,QString> dataMap;
    qDebug()<<datainfo.toHex();
    int line_len = (uchar)datainfo[1]*16*16 + (uchar)datainfo[2];
    dataMap["line_len"] = QString::number(line_len,10);
    dataMap["wind_rain_len"] = QString::number(((int)((uchar)datainfo[3])),10);
    dataMap["sender_X"] = QString::number(((int)((uchar)datainfo[4])),10);
    dataMap["sender_Y"] = QString::number(((int)((uchar)datainfo[5])),10);
    dataMap["sender_Z"] = QString::number(((int)((uchar)datainfo[6])),10);
    dataMap["reciver_X"] = QString::number(((int)((uchar)datainfo[7])),10);
    dataMap["reciver_Y"] = QString::number(((int)((uchar)datainfo[8])),10);
    dataMap["reciver_Z"] = QString::number(((int)((uchar)datainfo[9])),10);
    //    qDebug()<<"mapdata:"<<dataMap;
    emit gyroInint(softinfo,dataMap);
}

void RVR_DataParse::Threshold(QByteArray softinfo, QByteArray datainfo)
{
    QMap<QString,QString> dataMap;
    dataMap["calibrationValue"] = QString::number((int)((uchar)datainfo[10]),10);
    emit ThresholdValue(softinfo,dataMap);
}
//恢复出厂设置解析 -return
//7E 5A [00 14] 01 ff ff 00 00 01 [00 0b]
//01 01 00 01 00 [00 03] 02 01 data{01} 11 55
//
void RVR_DataParse::recoverFactoryParse(QByteArray softinfo, QByteArray /*datainfo*/)
{
    QMap<QString,QString> dataMap;
    //    if((uchar)datainfo[1] == 0x01)
    dataMap["recover"] = "ok";
    //    else
    //        dataMap["recover"] = "no";
    emit recover(softinfo,dataMap);
}
//RVR计算数据解析
//7e 5A [00 17] 10 ff ff 00 00 01 [00 0E]
//01 00 3C 00 00 [00 06]
//01 0b 00 00 00 00 11 55
void RVR_DataParse::RVRCalcData(QByteArray softinfo, QByteArray datainfo)
{
    QMap<QString,QString> dataMap;
    //    if(((uchar)datainfo[3] != (uchar)(0x00)) || ((uchar)datainfo[3] != (uchar)(0x00))){
    dataMap["rvr_value"] = QString::number(((int)((uchar)datainfo[3]))*256 +((int)((uchar)datainfo[4])),10);
    emit RVRData(softinfo,dataMap);/*}*/
    qDebug()<<"RVR value:"<<datainfo.toHex();
    //    else return;
}

//工作模式解析 -return
//7E 5A [00 15] 01 ff ff 00 00 02 [00 0B]
// 01 01 00 02 00 [00 03] 01 0a data{00} 11 55
void RVR_DataParse::workModleParse(QByteArray softinfo, QByteArray datainfo)
{
    QMap<QString,QString> dataMap;
    if((uchar)datainfo[1] == 0x00)
        dataMap["workmodle"] = "alignment";
    else if((uchar)datainfo[1] == 0x01)
        dataMap["workmodle"] = "test";
    else return ;
    emit recover(softinfo,dataMap);
}
//发射机参数配置 -return
//7E 5A [00 15] 01 ff ff 00 00 02 [00 0c]
//01 01 00 02 00 [00 05] 01 06 data{00 00 00} 11 55
void RVR_DataParse::senderMachineConfParse(QByteArray softinfo, QByteArray datainfo)
{
    QMap<QString,QString> dataMap;
    QString str;
    dataMap["electric_current"] =str.sprintf("%X02",(uchar)datainfo[1]);
    dataMap["pwd_ frequency"] =str.sprintf("%X02",(uchar)datainfo[2]);
    dataMap["mor_inpout_type"] =str.sprintf("%X02",(uchar)datainfo[3]);
    emit senderMachine(softinfo,dataMap);
}
//使能解析 - return
//7E 5A [00 18] 01 ff ff 00 00 02 [00 0f]
//01 01 00 02 00 [00 07] 01 03 data{00 00 00 00 00} 11 55
void RVR_DataParse::enableParse(QByteArray softinfo, QByteArray /*datainfo*/)
{
    QMap<QString,QString> dataMap;
    emit enable(softinfo,dataMap);
}
//告警解析 - return
//7E 5A [00 00] 01 ff ff 00 00 02 [00 00]
//01 01 00 02 00 [00 00] 01 08
// data{00 00 00 00 00 00 00 00 00 00 00 00 00 00 00} 11 55
void RVR_DataParse::waringParse(QByteArray softinfo, QByteArray datainfo)
{
    QMap<QString,QString> dataMap;
    dataMap["align_Sig"] = QString::number(((int)((uchar)datainfo[12])),10);
    emit waring(softinfo,dataMap);
}
//故障上传
void RVR_DataParse::WaringUpSend(QByteArray softinfo, QByteArray datainfo)
{
    QMap<QString,QString> dataMap;
    QString warStr = "no";
    if((uchar)datainfo[1] == 0x01)
    {
        warStr = "yes";
    }
    else
    {
        warStr = "no";
    }
    dataMap["reci_temp_down"] = warStr;
    if((uchar)datainfo[2] == 0x01)
    {
        warStr = "yes";
    }
    else
    {
        warStr = "no";
    }
    dataMap["reci_temp_hight"] = warStr;
    if((uchar)datainfo[3] == 0x01)
    {
        warStr = "yes";
    }
    else
    {
        warStr = "no";
    }
    dataMap["reci_hum_out_standard"] = warStr;
    if((uchar)datainfo[4] == 0x01)
    {
        warStr = "yes";
    }
    else
    {
        warStr = "no";
    }
    dataMap["send_temp_down"] = warStr;
    if((uchar)datainfo[5] == 0x01)
    {
        warStr = "yes";
    }
    else
    {
        warStr = "no";
    }
    dataMap["send_temp_hight"] = warStr;
    if((uchar)datainfo[6] == 0x01)
    {
        warStr = "yes";
    }
    else
    {
        warStr = "no";
    }
    dataMap["send_hum_out_standard"] = warStr;
    if((uchar)datainfo[7] == 0x01)
    {
        warStr = "yes";
    }
    else
    {
        warStr = "no";
    }
    dataMap["485_line_woring"] = warStr;
    emit waringUp(softinfo,dataMap);
}
//校准后陀螺仪角度复位
void RVR_DataParse::groyXYZZero(QByteArray softinfo, QByteArray datainfo)
{
    QMap<QString,QString> data;
    data["send_X"] = QString::number(((int)((uchar)datainfo[1])),10);
    data["send_Y"] = QString::number(((int)((uchar)datainfo[2])),10);
    data["send_Z"] = QString::number(((int)((uchar)datainfo[3])),10);
    data["reci_X"] = QString::number(((int)((uchar)datainfo[4])),10);
    data["reci_Y"] = QString::number(((int)((uchar)datainfo[5])),10);
    data["reci_Z"] = QString::number(((int)((uchar)datainfo[6])),10);
    emit groyXYZZeroValue(softinfo,data);
}
//满量程校准结果提示
void RVR_DataParse::fullScaleInfo(QByteArray softinfo, QByteArray /*datainfo*/)
{
    QMap<QString,QString> map;
    map["clibration_fullScale_value"] = "ok";
    emit fullScaaleValueSignal(softinfo,map);
}
//offset校准提示
void RVR_DataParse::offsetValueInfo(QByteArray softinfo, QByteArray datainfo)
{
    QMap<QString,QString> map;
    int num = ((int)((uchar)datainfo[1])) *16*16 +((int)((uchar)datainfo[2]));
    map["clibration_offset_value"] =QString::number(num,10);
    emit calibrationOffsetValue(softinfo,map);
}
//RVR软件复位提示
void RVR_DataParse::RVRSoftRecover(QByteArray softinfo, QByteArray /*datainfo*/)
{
    QMap<QString,QString> map;
    emit RVRSoftRecover(softinfo,map);
}
//线性测试
void RVR_DataParse::lineTestValue(QByteArray softinfo, QByteArray datainfo)
{
    QMap<QString,QString> map;
    QByteArray value = datainfo.mid(1,datainfo.length()-1);
    qDebug()<<"没裁剪"<<datainfo.toHex()<<"裁剪后"<<value.toHex()<<value.toDouble()<<value.toFloat();

    float floatValue = byteToFloat(value);
    map["lineValue"] = QString("%1").arg(floatValue);
    emit lineValue(softinfo,map);
}
//维护端口的RVR计算所需参数
void RVR_DataParse::maintainRvrCalc(QString option, QMap<QString, QString> data)
{
    if(option == "maintain_RVR_calc"){
        this->i = data["run_up_light"].trimmed().toDouble();
        this->et = data["backgroundlight"].trimmed().toDouble();
    }
    else return;
}
//使能维护端口的RVR值计算
void RVR_DataParse::enableRemainRVR(bool ok)
{
    this->RVR_enable = ok;
}
//维护端口的RVR值计算
double RVR_DataParse::RVR_value_calc(int morvalue, double ivalue, double etvalue)
{


    double mor,I,Et,y1,y2,mor350,mor600,a,rvrvalue = 0.0;
    int retflag = 0;
    mor = /*300*/ morvalue; I = /*1000*/ ivalue; Et = /*1.0/10000.0*//*0.0001*/ etvalue;
    qDebug()<<"mor:"<<QString::number(mor)<<"I:"<<QString::number(I)<<"Et:"<<QString::number(Et);

    if( (  log(600)-((log(I/Et))/2 - (3*600)/(2*mor)) )<0 )
    {
        qDebug()<<"In the 600-15000";
        for(int i = 600;i < 15000;i++)
        {
            y1 = log(i);
            y2 = (log(I/Et))/2 - (3*i)/(2*mor);
            if( (y1-y2) >0)
            {
                //printf("\n --> RVR:%d  \n",i);
                //printf("\n --> y1:%.10f --> y2:%.10f y1-y2:%f \n",y1,y2,y1-y2);
                //printf(" \n");
                rvrvalue = i;
                retflag =1;
                break;
            }
        }
    }
    else
    {
        qDebug()<<"in the 1-350 \n";

        for(int i = 1;i < 350;i++)
        {
            y1 = log(i);
            y2 = (log(I/Et))/2 - (3*i)/(2*mor);
            if( (y1-y2) >0)
            {
                //printf("\n --> RVR:%d  \n",i);
                //printf("\n --> y1:%.10f --> y2:%.10f y1-y2:%f \n",y1,y2,y1-y2);
                //printf(" \n");
                rvrvalue = i;
                retflag =2;
                break;
            }
        }
        if( retflag != 2 )
        {
            qDebug()<<"\n Not in the 1-350 \n";
            mor350 = ( 3 * 350) / (log(I) - log(Et) - 2 * ( log( 350)));
            mor600 = ( 3 * 600) / (log(I) - log(Et) - 2 * ( log( 600)));
            a = (mor -mor350) / (mor600 - mor350);
            rvrvalue = a * 600 + (1 - a) * 350;
            //            rvrvalue = ((mor-350)/5)*12+((mor-100)/5)*7;
        }
    }
    return rvrvalue;
}

float RVR_DataParse::byteToFloat(QByteArray bytes)
{
    float *returnValue;
    unsigned char dataV[4] ;
    for(int j = 0;j < 4;j++){
        dataV[j] = (unsigned char)bytes[j];
    }
    returnValue = (float *)dataV;
    float returnNmu = *returnValue;
    return returnNmu;
}














