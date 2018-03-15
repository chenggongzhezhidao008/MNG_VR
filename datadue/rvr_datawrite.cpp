#include "rvr_datawrite.h"

RVR_DataWrite::RVR_DataWrite(QObject *parent) :
    QObject(parent)
{
    initRVRDataMap();
    seq = 0;
}

void RVR_DataWrite::initRVRDataMap()
{
    for(int i = 0;i < 32;i++){
        if(i < 3){
            senderparameter[i] = (uchar)0x00;}
        if(i < 4){
            RVRcalcValues[i] = (uchar)0x00;}
        if(i < 5){
            enableData[i]    = (uchar)0x00;}
        if(i < 9){
            groyinitData[i]  = (uchar)0x00;}
        if(i < 10){
            RVRparameter[i]  = (uchar)0x00;}
        if(i < 21){
            Threshold[i]     = (uchar)0x00;}
    }
}

void RVR_DataWrite::writeData(QString option,QMap<QString,QString> data)
{
    if(option == "serial_set")SerialPortSet(data);
    else if(option == "device_set")deviceSet(data);
    else if(option == "serial_ask") serialPortAsk();
    else if(option == "data_info_ask")dataInfoAsk();
    else if(option == "recover_set")recoverFactorySet();
    else if(option == "waring_ask") waringask();
    else if(option == "gyro_xyz")getgyro();
    else if(option == "init_gyro_send")sendinitgyro(data);
    else if(option == "init_gyro_reci")reciinitgyro(data);
    else if(option == "set_wind_rain")setWindRain(data);
    else if(option == "enable_RVR")enable_RVR(data);
    else if(option == "enable_hinder_light")enable_hinder_light(data);
    else if(option == "enable_send_blower")enable_send_blower(data);
    else if(option == "enable_reci_blower")enable_reci_blower(data);
    else if(option == "message_model")message_model(data);
    else if(option == "Threshold_set")Threshold_set(data);
    else if(option == "RVR_Calc_value")RVR_Calc_parameter(data);
    else if(option == "senderarguments")sender_arguments_set(data);
    else if(option == "calc_values")RVR_calc_input_value(data);
    else if(option == "offset_calibration") offsetCalibration(data);
    else if(option == "full_calibration")fullScaleCalibration(data);
    else if(option == "reset_RVR_soft")RVRReset(data);
    else if(option == "groy_setZero")groySetZero(data);
    else if(option == "line_test") lineTest(data);
    else if(option == "hearbeat") hearbeat(data);
    else return ;
}

//取串口数据 -read
void RVR_DataWrite::serialPortAsk()
{
    char buff[] = { 0x7E, 0x5A, 0x00, 0x17, 0x01, 0x00, 0x01, 0xff, 0xff, 0x01, 0x00, 0x0E,
                    0x01, 0x01,0x00,0x00,0x00,0x00,0x02,0x01,0x02,0x11,0x55};//ok
    atHeadAddSeq(QByteArray(buff, 23));
}

//设串口数据 -write
void RVR_DataWrite::SerialPortSet(QMap<QString,QString> data)
{
    qDebug()<<"serial set:"<<data;

    char buff[] = { 0x7E, 0x5A, 0x00, 0x17, 0x01, 0x00, 0x01, 0xff, 0xff, 0x01, 0x00, 0x0E,
                    0x01, 0x01,0x00,0x01,0x00,0x00,0x06,0x01,0x02,0x00,0x00,0x00,
                    0x01, 0x11,0x55};//ok
    bool ok ;
    buff[6] = data["id"].toInt(&ok,16);
    switch (data["baud"].toInt()) {
    case 9600:buff[21] = 0x01;
        break;
    case 19200:buff[21] = 0x02;
        break;
    case 38400:buff[21] = 0x03;
        break;
    case 57600:buff[21] = 0x04;
        break;
    default:
        break;
    }
    switch (data["datas"].toInt()) {
    case 5:buff[22] = 0x01;
        break;
    case 6:buff[22] = 0x02;
        break;
    case 7:buff[22] = 0x03;
        break;
    case 8:buff[22] = 0x04;
        break;
    default:
        break;
    }
    if(data["parity"] == "无校验")buff[23] = 0x01;
    if(data["parity"] == "偶校验")buff[23] = 0x02;
    if(data["parity"] == "奇校验")buff[23] = 0x03;

    atHeadAddSeq(QByteArray(buff, 27));
}

//取数据信息 -read
void RVR_DataWrite::dataInfoAsk()
{
    char buff[] = { 0x7E, 0x5A, 0x00, 0x13, 0x01, 0x00, 0x01, 0xff, 0xff, 0x01, 0x00, 0x0A,
                    0x01, 0x01,0x00,0x00,0x00,0x00,0x02,0x01,0x09,0x11,0x55};//ok
    atHeadAddSeq(QByteArray(buff, 23));
}

//恢复出厂设置 - write
void RVR_DataWrite::recoverFactorySet()
{
    char buff[] = { 0x7E, 0x5A, 0x00, 0x13, 0x01, 0x00, 0x01, 0xff, 0xff, 0x01, 0x00, 0x0a,
                    0x01, 0x01,0x00,0x01,0x00,0x00,0x02,0x02,0x01,0x11,0x55};//ok
    qDebug()<<"command:"<<QByteArray(buff,23);
    atHeadAddSeq(QByteArray(buff, 23));
}


//设备设置 -write 暂无此命令
void RVR_DataWrite::deviceSet(QMap<QString,QString> data)
{
    char buff[] = { 0x7E, 0x5A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x55 };
    atHeadAddSeq(QByteArray(buff, 9));
    qDebug()<<"data"<<data;
}

//告警配置请求
void RVR_DataWrite::waringask()
{
    char buff[] = { 0x7E, 0x5A, 0x00, 0x13, 0x01, 0x00,0x01 ,0xff,0xff ,0x01,0x00,0x0a,
                    0x01,0x01,0x00,0x00,0x00,0x00,0x02,0x01,0x08,0x11, 0x55 };
    atHeadAddSeq(QByteArray(buff, 25));//ok
}

//读陀螺仪数据
void RVR_DataWrite::getgyro()
{
    char buff[] = { 0x7E, 0x5A, 0x00, 0x13, 0x01, 0x00, 0x01, 0xff,0xff ,0x01,0x00,0x0a ,
                    0x01,0x01,0x00,0x01,0x00,0x00,0x02,0x01,0x04,0x11,0x55 };
    atHeadAddSeq(QByteArray(buff, 23));
}

//发射机初始化螺仪
void RVR_DataWrite::sendinitgyro(QMap<QString, QString> data)
{
    char buff[] = { 0x7E, 0x5A, 0x00, 0x1c, 0x01, 0x00, 0x01, 0xff,0xff ,0x01,0x00,0x13,
                    0x01,0x01,0x00,0x01,0x00,0x00,0x0b,0x01,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                    0x00,0x00,0x11,0x55 };
    bool ok;
    groyinitData[3] = (uchar)(data["sender_X"].trimmed().toInt(&ok,16));
    groyinitData[4] = (uchar)(data["sender_Y"].trimmed().toInt(&ok,16));
    groyinitData[5] = (uchar)(data["sender_Z"].trimmed().toInt(&ok,16));
    for(int i = 0;i < 9;i++){
        buff[21+i] = groyinitData[i];
    }
    atHeadAddSeq(QByteArray(buff, 32));
}

//接收机初始化螺仪
void RVR_DataWrite::reciinitgyro(QMap<QString, QString> data)
{

    char buff[] = { 0x7E, 0x5A, 0x00, 0x1c, 0x01, 0x00, 0x01, 0xff,0xff ,0x01,0x00,0x13,
                    0x01,0x01,0x00,0x01,0x00,0x00,0x0b,0x01,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                    0x00,0x00,0x11,0x55 };
    bool ok;
    groyinitData[6] = (uchar)(data["reciver_X"].trimmed().toInt(&ok,16));
    groyinitData[7] = (uchar)(data["reciver_Y"].trimmed().toInt(&ok,16));
    groyinitData[8] = (uchar)(data["reciver_Z"].trimmed().toInt(&ok,16));
    for(int i = 0;i < 9;i++){
        buff[21+i] = groyinitData[i];
    }
    atHeadAddSeq(QByteArray(buff, 32));
}

//设置风雨罩
void RVR_DataWrite::setWindRain(QMap<QString, QString> data)
{
    char buff[] = { 0x7E, 0x5A, 0x00, 0x1c, 0x01, 0x00, 0x01, 0xff,0xff ,0x01,0x00,0x13,
                    0x01,0x01,0x00,0x01,0x00,0x00,0x0b,0x01,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                    0x00,0x00,0x11,0x55 };
    int baseline = (data["baseline"].trimmed().toInt())/256;
    groyinitData[0] = (uchar)baseline;
    baseline = (data["baseline"].trimmed().toInt())%256;
    groyinitData[1] = (uchar)baseline;
    groyinitData[2] = (uchar)(data["wind_rain"].trimmed().toInt());
    for(int i = 0;i < 9;i++){
        buff[21+i] = groyinitData[i];
    }
    atHeadAddSeq(QByteArray(buff, 32));
}
//RVR使能
void RVR_DataWrite::enable_RVR(QMap<QString, QString> data)
{
    char buff[] = { 0x7e, 0x5A,0x00,0x18,0x01, 0x00, 0x01, 0xff, 0xff, 0x01, 0x00, 0x0f,
                    0x01, 0x01,0x00, 0x01, 0x00, 0x00,0x07,0x01, 0x03,
                    0x01, 0x00, 0x00, 0x00, 0x02, 0x11,0x55};
    enableData[0] = (uchar)(data["RVR"].trimmed().toInt());
    for(int i = 0;i < 5;i++){
        buff[21+i] = enableData[i];
    }
    atHeadAddSeq(QByteArray(buff, 28));
}
//障碍灯使能
void RVR_DataWrite::enable_hinder_light(QMap<QString, QString> data)
{
    char buff[] = { 0x7e, 0x5A,0x00,0x18,0x01, 0x00, 0x01, 0xff, 0xff, 0x01, 0x00, 0x0f,
                    0x01, 0x01,0x00, 0x01, 0x00, 0x00,0x07,0x01, 0x03,
                    0x01, 0x00, 0x00, 0x00, 0x02, 0x11,0x55};
    enableData[1] = (uchar)(data["hinder_light"].trimmed().toInt());
    for(int i = 0;i < 5;i++){
        buff[21+i] = enableData[i];
    }
    atHeadAddSeq(QByteArray(buff, 28));
}
//发射机风机使能
void RVR_DataWrite::enable_send_blower(QMap<QString, QString> data)
{
    char buff[] = { 0x7e, 0x5A,0x00,0x18,0x01, 0x00, 0x01, 0xff, 0xff, 0x01, 0x00, 0x0f,
                    0x01, 0x01,0x00, 0x01, 0x00, 0x00,0x07,0x01, 0x03,
                    0x01, 0x00, 0x00, 0x00, 0x02, 0x11,0x55};
    enableData[2] = (uchar)(data["send_blower"].trimmed().toInt());
    for(int i = 0;i < 5;i++){
        buff[21+i] = enableData[i];
    }
    atHeadAddSeq(QByteArray(buff, 28));
}
//接收机风机使能
void RVR_DataWrite::enable_reci_blower(QMap<QString, QString> data)
{
    char buff[] = { 0x7e, 0x5A,0x00,0x18,0x01, 0x00, 0x01, 0xff, 0xff, 0x01, 0x00, 0x0f,
                    0x01, 0x01,0x00, 0x01, 0x00, 0x00,0x07,0x01, 0x03,
                    0x01, 0x00, 0x00, 0x00, 0x02, 0x11,0x55};
    enableData[3] = (uchar)(data["reci_blower"].trimmed().toInt());
    for(int i = 0;i < 5;i++){
        buff[21+i] = enableData[i];
    }
    atHeadAddSeq(QByteArray(buff, 28));
}
//消息模式
void RVR_DataWrite::message_model(QMap<QString, QString> data)
{
    char buff[] = { 0x7e, 0x5A,0x00,0x18,0x01, 0x00, 0x01, 0xff, 0xff, 0x01, 0x00, 0x0f,
                    0x01, 0x01,0x00, 0x01, 0x00, 0x00,0x07,0x01, 0x03,
                    0x01, 0x00, 0x00, 0x00, 0x02, 0x11,0x55};
    enableData[4] = (uchar)(data["mess_model"].trimmed().toInt());
    for(int i = 0;i < 5;i++){
        buff[21+i] = enableData[i];
    }
    atHeadAddSeq(QByteArray(buff, 28));
}
//阈值设定
void RVR_DataWrite::Threshold_set(QMap<QString, QString> data)
{
    char buff[] = {0x7e, 0x5A, 0x00, 0x2a, 0x01,0x00,0x01,0xff,0xff,0x01,0x00,0x21,
                   0x01,0x01,0x00,0x01,0x00,0x00,0x19,0x01,0x05,
                   0x00, 0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x11,0x55};
    Threshold[0]  = (uchar)(data["hinderlight"].trimmed().toInt() / 256);
    Threshold[1]  = (uchar)(data["hinderlight"].trimmed().toInt() % 256);
    Threshold[2]  = (uchar)(data["gyr_send_Vup"].trimmed().toInt());
    Threshold[3]  = (uchar)(data["gyr_reciv_Vup"].trimmed().toInt());
    Threshold[4]  = (uchar)(data["gyr_send_Hup"].trimmed().toInt());
    Threshold[5]  = (uchar)(data["gyr_reciv_Hup"].trimmed().toInt());
    Threshold[6]  = (uchar)(data["gyr_send_font_back_up"].trimmed().toInt());
    Threshold[7]  = (uchar)(data["gyr_reciv_font_back_up"].trimmed().toInt());
    Threshold[8]  = (uchar)(data["runupmin"].trimmed().toInt() / 256);
    Threshold[9]  = (uchar)(data["runupmin"].trimmed().toInt() % 256);
    Threshold[10] = (uchar)(data["alignmentsignal"].trimmed().toInt());
    Threshold[11] = (uchar)(data["calfact"].trimmed().toInt());
    Threshold[12] = (uchar)(data["stuptemperature"].trimmed().toInt());
    Threshold[13] = (uchar)(data["stoptemperature"].trimmed().toInt());
    Threshold[14] = (uchar)(data["inside_max_humidity"].trimmed().toInt());
    Threshold[15] = (uchar)(data["4-50"].trimmed().toInt() / 256);
    Threshold[16] = (uchar)(data["4-50"].trimmed().toInt() % 256);
    Threshold[17] = (uchar)(data["51-999"].trimmed().toInt() / 256);
    Threshold[18] = (uchar)(data["51-999"].trimmed().toInt() % 256);
    Threshold[19] = (uchar)(data["1000-12000"].trimmed().toInt() / 256);
    Threshold[20] = (uchar)(data["1000-12000"].trimmed().toInt() % 256);
    Threshold[21] = (uchar)(data["gt12000"].trimmed().toInt() / 256);
    Threshold[22] = (uchar)(data["gt12000"].trimmed().toInt() % 256);
    for(int i = 0; i < 23;i++){
        buff[21+i] = Threshold[i];
    }
    atHeadAddSeq(QByteArray(buff, 46));
}
//RVR 计算参数
void RVR_DataWrite::RVR_Calc_parameter(QMap<QString, QString> data)
{
    char buff[] = {0x7e,0x5A, 0x00,0x1d,0x01,0x00,0x01,0xff,0xff,0x01,0x00,0x14,
                   0x01, 0x01, 0x00,0x01,0x00,0x00,0x0c,0x01,0x07,
                   0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x11,0x55};
    RVRparameter[0]  = (uchar)(data["RVR_Calc_enanle"].trimmed().toInt());
    RVRparameter[1]  = (uchar)(data["message_port"].trimmed().toInt());
    RVRparameter[2]  = (uchar)(data["down_value"].trimmed().toInt() / 256);
    RVRparameter[3]  = (uchar)(data["down_value"].trimmed().toInt() % 256);
    RVRparameter[4]  = (uchar)(data["up_value"].trimmed().toInt() / 256);
    RVRparameter[5]  = (uchar)(data["up_value"].trimmed().toInt() % 256);
    RVRparameter[6]  = (uchar)(data["RVR_samp_interval"].trimmed().toInt());
    RVRparameter[7]  = (uchar)(data["Mor_accuracy"].trimmed().toInt());
    RVRparameter[8]  = (uchar)(data["RVR_accuracy"].trimmed().toInt());
    RVRparameter[9]  = (uchar)(data["RVR_pollution_Cover"].trimmed().toInt());
    for(int i = 0; i < 10; ++i) {
        buff[21+i] = senderparameter[i];
    }
    atHeadAddSeq(QByteArray(buff, 33));
}

//发射机参数
void RVR_DataWrite::sender_arguments_set(QMap<QString, QString> data)
{
    char buff[] = {0x7e,0x5A,0x00,0x17,0x01,0x00,0x01,0xff,0xff,0x01,0x00,0x0E,
                   0x01,0x01,0x00,0x01,0x00,0x00,0x05,0x01,0x06,
                   0x00,0x00,0x00,0x11,0x55};
    senderparameter[0] = (uchar)(data["electric_strength"].trimmed().toInt());
    senderparameter[1] = (uchar)(data["pwm_frequency"].trimmed().toInt());
    senderparameter[2] = (uchar)(data["input_mor_stlye"].trimmed().toInt());
    for (int i = 0; i < 3; ++i) {
        buff[21+i] = senderparameter[i];
    }
    atHeadAddSeq(QByteArray(buff, 26));
}

//RVR计算时需输入的参数
void RVR_DataWrite::RVR_calc_input_value(QMap<QString, QString> data)
{
    char buff[] = {0x7e, 0x5A, 0x00, 0x17, 0x10,0xff, 0xff, 0x00, 0x00,0x01,0x00,0x0E,
                   0x01, 0x00, 0x3C, 0x01, 0x00, 0x00, 0x06,
                   0x01, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x11, 0x55};

    QString str = data["backgroundlight"].trimmed();
    int sub = 0;
    if(str == "8/1000") sub = 0;
    else if(str == "8/10000")sub = 1;
    else if(str == "8/100000") sub = 2;
    else if(str == "8/10000000") sub = 3;
    RVRcalcValues[0] = (uchar)sub;

    str = data["run_up_light"].trimmed();
    if(str == "1%") sub = 0;
    else if(str == "3%") sub = 1;
    else if(str == "10%") sub = 2;
    else if(str == "30%") sub = 3;
    else if(str == "100%") sub = 4;
    RVRcalcValues[1] = (uchar)sub;;

    for(int i = 0; i < 4; i++){
        buff[21+i] = RVRcalcValues[i];
    }

    atHeadAddSeq(QByteArray(buff, 27));
}
//
void RVR_DataWrite::offsetCalibration(QMap<QString, QString> data)
{
    if(data["offset_value"] == "ok");
    char buff[] = { 0x7E, 0x5A, 0x00, 0x13, 0x01, 0x00, 0x01, 0xff, 0xff, 0x01, 0x00, 0x0a,
                    0x01,0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x0d,
                    0x11, 0x55 };
    atHeadAddSeq(QByteArray(buff, 23));
}

void RVR_DataWrite::fullScaleCalibration(QMap<QString, QString> data)
{
    int num = data["full_scale_value"].trimmed().toInt();
    char buff[] = { 0x7E, 0x5A, 0x00, 0x15, 0x01, 0x00, 0x01, 0xff, 0xff, 0x01, 0x00, 0x0c,
                    0x01,0x01,0x00, 0x01, 0x00, 0x00, 0x04, 0x01, 0x0c,0x00, 0x00,
                    0x11, 0x55 };

    buff[21] = (uchar)(num / (16*16));
    buff[22] = (uchar)(num % (16*16));
    atHeadAddSeq(QByteArray(buff, 25));
}

//reset RVR soft
void RVR_DataWrite::RVRReset(QMap<QString, QString> /*data*/)
{
    char buff[] = {0x7E, 0x5A, 0x00, 0x13, 0x01, 0x00, 0x01, 0xff, 0xff, 0x01, 0x00, 0x0a,
                   0x01,0x01,0x00, 0x01, 0x00, 0x00, 0x02, 0x01, 0x10, 0x11, 0x55};
    //    if(data["reset_value"] == "reset"){
    atHeadAddSeq(QByteArray(buff,23));
    //    }
    return ;
}
//groy setZero
void RVR_DataWrite::groySetZero(QMap<QString, QString> /*data*/)
{
    char buff[] = {0x7E, 0x5A, 0x00, 0x13, 0x01, 0x00, 0x01, 0xff, 0xff, 0x01, 0x00, 0x0a,
                   0x01,0x01,0x00, 0x01, 0x00, 0x00, 0x02, 0x01, 0x0f, 0x11, 0x55};
    atHeadAddSeq(QByteArray(buff,23));
    return ;
}
//line Tset
void RVR_DataWrite::lineTest(QMap<QString, QString> data)
{
    float inputValue = (data["line_test_input_value"].trimmed().toFloat()) / 100;
    qDebug()<<"value:"<<QString("%1").arg(inputValue);
    QByteArray floatValue;
    QByteArray flota = floatValue.setNum(inputValue);
    char subBuff[] = { 0x00};
    QByteArray sub = QByteArray(subBuff,1);
        int i = flota.length();
        for(i ; i < 4;i++){
            flota.insert(i,sub);
        }
    qDebug()<<"线性测试输入值:"<<flota.toHex()<<flota.toFloat();
    char buff[] = {0x7E, 0x5A, 0x00, 0x13, 0x01, 0x00, 0x01, 0xff, 0xff, 0x01, 0x00, 0x0a,
                   0x01,0x01,0x00, 0x01, 0x00, 0x00, 0x02, 0x01, 0x11, 0x11, 0x55};
    QByteArray sendByt = QByteArray(buff,23);
//    sendByt.insert(21,flota);
    atHeadAddSeq(sendByt);
    return ;
}

//上位机心跳
void RVR_DataWrite::hearbeat(QMap<QString, QString> )
{
    char buff[] = {0x7E, 0x5A, 0x00, 0x00, 0x11, 0x55};
    QByteArray sendByt = QByteArray(buff,6);
    atHeadAddSeq(sendByt);
}

void RVR_DataWrite::commmand(QByteArray /*fram*/, QByteArray /*commd*/, QByteArray /*data*/)
{
    char buff[] = { 0x7E, 0x5A, 0x00, 0x13, 0x01, 0x00, 0x01, 0xff, 0xff, 0x01, 0x00, 0x0a,
                    0x01,0x01,0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x04, 0x11, 0x55 };
    atHeadAddSeq(QByteArray(buff, 23));
}

//监视数据写出
void RVR_DataWrite::writeMonitor(QString, QByteArray data)
{
    qDebug()<<"手动输出字符串->>:"+data.toHex();
    emit writeComm(data);
}

void RVR_DataWrite::atHeadAddSeq(QByteArray data)
// 将RVR数据格式协议 V05_A版 转为 V05_A(1)版
{
    if((this->seq) == 4294901760)
    {
        this->seq = 0;
    }
    this->seq++;
    //    qDebug()<<"legtne"<<data.mid(2,2).toHex();
    int length = ((int)((uchar)data[2])) * 16 * 16 +((int)((uchar)data[3])) + 4;
    data[2] = (uchar)(length / (16*16));
    data[3] = (uchar)(length % (16*16));
    //    qDebug()<<"i"<<QString::number(length,10)<<data.mid(2,2).toHex();
    QByteArray orderSeq = data;
    char sequence[] = {0x00 ,0x00 ,0x00 ,0x01};
    sequence[0] = (uchar)(this->seq / (16*16*16*16*16*16));
    sequence[1] = (uchar)((this->seq % (16*16*16*16*16*16)) / (16*16*16*16));
    sequence[2] = (uchar)((this->seq % (16*16*16*16)) / (16*16));
    sequence[3] = (uchar)(this->seq  % (16*16));
    QByteArray seque = QByteArray(sequence,4);
    orderSeq.insert(4,seque);
    //    qDebug()<<"seque byte:"<<seque.toHex();
    qDebug()<<"写出命令->>:" + orderSeq.toHex();
    emit writeComm(orderSeq);
}


























