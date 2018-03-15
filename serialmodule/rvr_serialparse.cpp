#include "rvr_serialparse.h"
#include <QDebug>

RVR_serialparse::RVR_serialparse(QObject *parent) :
    QObject(parent)
{
}
//==============
//  查找串行序列
//  pos = 报文开始位置
//  返回命令长度
//===============
int RVR_serialparse::find_head_rear(char *serData,int len,int &startPos)
{
    int i = 0;
    bool have_head = false;
    while(i < len){                                                                   //qDebug()<<i;  //qDebug()<<"byte:"<<(uchar)serData[i];
        if((uchar)serData[i] == 0x7E &&(uchar)serData[i+1] == 0x5A){
            qDebug()<<"find head.";
            have_head = true;
            for(int j = i+2;j < len;j++){
                if((uchar)serData[j] == 0x11&&(uchar)serData[j+1] == 0x55){
                    startPos = i;
                    qDebug()<<"find rear";
                    qDebug()<<"command length:"<<(j-i)+2;
                    return (j-i)+2;
                    break;
                }
            }
            qDebug()<<"not find rear!";
            startPos = i;
            return 0;
            break;
        }
        i++;
    }
    qDebug()<<"not find a message";
    startPos = i-2;
    return 0;
}
//========
//解析串口字节数据序列
//========
void RVR_serialparse::parse_serial(QByteArray newdata){
    serialbuff += newdata;
    qDebug()<<"data length:"<<serialbuff.length();
    int  comm_length = 0;
    int start_pos = 0;
    while(serialbuff.length()> 0){
        comm_length = find_head_rear(serialbuff.data(),serialbuff.length(),start_pos);
        if(comm_length >0){
            QByteArray message = serialbuff.mid(start_pos,comm_length);
            int messageLength = message.length();
            if(messageLength > 25){//先不处理长度计算
                message_parse(message);
                qDebug()<<"Parse message"<<message.toHex()<<"length:"<<messageLength;
            }
        }
        else{
            serialbuff.remove(0,start_pos);
            break;
        }
        serialbuff.remove(0,start_pos+comm_length);
    }
    qDebug()<<"due after data length:"<<serialbuff.length();
}

//============
// 数据内容解析
//============
void RVR_serialparse::message_parse(QByteArray message){
    if((message[9] == ((char)0xff)) && (message[10] == ((char)0xff)))
    {
        if(message[13] == (char)0x01){
            return ;
        }
        qDebug()<<"data content："<<message.toHex();
        if(message[23] == (char)0x01){
            switch (message[24]) {
            case 0x01:
                qDebug()<<"sensor基本信息";
                emit mess_Data("sensor_base_info",message);
                break;
            case 0x02:
                qDebug()<<"串口信息配置";
                emit mess_Data("serial_info_set",message);
                break;
            case 0x03:
                qDebug()<<"使能配置";
                emit mess_Data("enable_set",message);
                break;
            case 0x04:
                qDebug()<<"陀螺仪初始化";
                emit mess_Data("gyro_init",message);
                break;
            case 0x05:
                qDebug()<<"阈值设置";
                emit mess_Data("threshold_value_set",message);
                break;
            case 0x06:
                qDebug()<<"发射机参数配置";
                emit mess_Data("sender_value_set",message);
                break;
            case 0x07:
                qDebug()<<"RVR计算参数";
                emit mess_Data("RVR_value_calc",message);
                break;
            case 0x08:
                qDebug()<<"告警配置";
                emit mess_Data("waring_set",message);
                break;
            case 0x09:
                qDebug()<<"数据信息";
                emit mess_Data("data_info",message);
                break;
            case 0x0A:
                qDebug()<<"工作模式";
                emit mess_Data("work_model",message);
                break;
            case 0x0B:
                qDebug()<<"RVR计算数据";
                emit mess_Data("RVR_data",message);
                break;
            case 0x0C:
                qDebug()<<"full scale 消息";
                emit mess_Data("full_scale_info",message);
                break;
            case 0x0D:
                qDebug()<<"offset value 消息";
                emit mess_Data("offset_value_info",message);
                break;
            case 0x0E:
                qDebug()<<"故障主动上传";
                emit mess_Data("wraing_up_send",message);
                break;
            case 0x0f:
                qDebug()<<"校准后陀螺仪角度复位";
                emit mess_Data("groy_xyz_zero",message);
                break;
            case 0x10:
                qDebug()<<"RVR软件复位";
                emit mess_Data("RVR_soft_recover",message);
                break;
            case 0x11:
                qDebug()<<"线性测试";
                emit mess_Data("line_test_value",message);
                break;
            default:
                qDebug()<<"gao jing";
                break;
            }
        }
        else if(message[23] == (char)0x02){
            switch (message[24]) {
            case 0x01:
                qDebug()<<"回复出厂默认设置";
                emit mess_Data("recover_first",message);
                break;
            default:
                break;
            }
        }
    }
    else{
        return ;
    }
}

