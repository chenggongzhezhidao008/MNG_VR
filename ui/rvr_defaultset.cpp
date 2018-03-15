#include "rvr_defaultset.h"
#include "ui_rvr_defaultset.h"
#include <QCheckBox>
#include <QRadioButton>
//#include <QGraphicsBlurEffect>

#include "mess/RVR_Reminder_Msg.h"
RVR_DefaultSet::RVR_DefaultSet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RVR_DefaultSet)
{
    ui->setupUi(this);
    init_ui();
    fromId = 7;
//    ui->groupBox_main_select->setGeometry(40,10,811,471);
    ui->groupBox_defaultSet->setGeometry(40,20,811,540);//只要基本配置其他全隐藏

    ui->groupBox_selectButton->hide();
}

RVR_DefaultSet::~RVR_DefaultSet()
{
    delete ui;
}

void RVR_DefaultSet::init_UI_data(QStringList /*portList*/)
{
    //    if(comboxList.length() != portList.length()){
    //        int length = comboxList.length();
    //        for(int j = 0;j < length; j++){
    //            comboxList.removeAt(j);
    //            ui->comboBox_port->removeItem(0);
    //        }
    //        comboxList = portList;
    ui->comboBox_Id->clear();
    ui->comboBox_Id->addItem("01");
    //    }
}

void RVR_DefaultSet::setDefaultdata(QMap<QString,QString> defalut)
{
    defalutMap = defalut;
    ui->comboBox_Id->setCurrentText(defalut["01"]);
    ui->comboBox_baud->setCurrentText(defalut["baud"]);
    ui->comboBox_datas->setCurrentText(defalut["datas"]);
    ui->comboBox_stop->setCurrentText(defalut["stop"]);
    ui->comboBox_parity->setCurrentText(defalut["parity"]);
}
//set courrent config
void RVR_DefaultSet::setCurrentData()
{
    QByteArray str;
    QMap<QString,QString> data;
    data["data_info"] == "当前配置";
    showOptionMessage(str,data);
}

void RVR_DefaultSet::showOptionMessage(QByteArray , QMap<QString, QString> map)
{
    QMap<QString,QString>commitMap;
    commitMap["id"] = "01"/*ui->comboBox_Id->currentText().trimmed()*/;
    commitMap["baud"] = ui->comboBox_baud->currentText().trimmed();
    commitMap["datas"] = ui->comboBox_datas->currentText().trimmed();
    commitMap["stop"] = ui->comboBox_stop->currentText().trimmed();
    commitMap["parity"] = ui->comboBox_parity->currentText().trimmed();

    if(map["data_info"] == "通讯设置成功")
    {
        Reminder_Mseg::showMessageboxInfo(map["data_info"]);
    }
    qDebug()<<"current:config"<<commitMap;
    emit current_commit_info(commitMap);
    emit default_set_option("update_commit",commitMap);
}

//set base line length
void RVR_DefaultSet::setBaseLine(QString lengthStr)
{
   ui->lineEdit_baseline->setText(lengthStr);
}

//set wind Rain cover length
void RVR_DefaultSet::setWindRainCover(QString lengthStr)
{
   ui->lineEdit_windrain->setText(lengthStr);
}

//4800 = 4800 57600 = 57600 baud.9600	= 9600 baud,19200=19200 baud,38400 = 38400 baud.
//dataNum:
//1	= Five bits,2 = Six bits,3 = Seven bits,4 = Eight bits.
//stopByte:
//1 = 1 stop bit,3 = 1.5 stop bits,2 = 2 stop bits.
//parity:
//1 = No parity,2 = Even parity,3 = Odd parity.

void RVR_DefaultSet::init_ui()
{
    //serial set
    {
        QStringList bauds;
        bauds<<"9600"<<"19200"<<"38400"<<"57600";/*<<"4800"*/
        QStringList datas;
        datas/*<<"5"<<"6"*/<<"7"<<"8";//数据传输过程中会出现数据混乱暂时不用。
        QStringList stops;
        stops<<"1"<<"1.5"<<"2";
        QStringList paritys;
        paritys<<"无校验"<<"偶校验"<<"奇校验";
        ui->comboBox_baud->addItems(bauds);
        ui->comboBox_datas->addItems(datas);
        ui->comboBox_stop->addItems(stops);
        ui->comboBox_parity->addItems(paritys);
    }

    //decive set
    {
        QStringList device ;device<<"主设备"<<"备用设备";
        QStringList select ;select<<"是"<<"否";
        QStringList openclose; openclose<<"开"<<"关";
        QStringList electrity; electrity<<"1.5 A"<<"2.5 A"<<"15 A"<<"20 A";
        QStringList factorys;factorys<<"视程科技"<<"维萨拉";
        ui->comboBox_pullte->addItems(openclose);
        ui->comboBox_buzzer->addItems(openclose);
        ui->comboBox_factory->addItems(factorys);
        ui->comboBox_electrity->addItems(electrity);
        ui->comboBoxMojr_secend->addItems(device);
        ui->comboBox_reciver_fever->addItems(openclose);
        ui->comboBox_send_fever->addItems(openclose);
    }
    //init waring config
    QStringList list;
    list<<"不饱和"<<"饱和";
    ui->comboBox_reciv_signal->addItems(list);
    list.clear();
    list<<"leavel1"<<"leavel2"<<"leavel3";
    ui->comboBox_pollute_leve->addItems(list);
    list.clear();
    list<<"低不可用"<<"低可用"<<"正常";
    ui->comboBox_RVR_SPL->addItems(list);
    list.clear();
    list<<"10%立即更换"<<"6%更换"<<"4%不更换";
    ui->comboBox_led_old->addItems(list);
    list.clear();
    list<<"正常"<<"告警";
    ui->comboBox_reciv_electric_state->addItems(list);
    ui->comboBox_send_electric_state->addItems(list);
    list.clear();
    list<<"关闭"<<"打开";
    ui->comboBox_hinderLight->addItems(list);
    list.clear();
    list<<">80%不需对准"<<"<80%需对准";
    ui->comboBox_alignment->addItems(list);
    list.clear();
    list<<"正常"<<"超出下限"<<"超出上限"<<"基于PWD测量"<<"无效";
    ui->comboBox_mor_state->addItems(list);
    list.clear();

    //init sender config
    list<<"3600"<<"维护端口";
    ui->comboBox_MessagePort->addItems(list);
    list.clear();
    list<<"开启"<<"关闭";
    ui->comboBox_RVR_Clac_open->addItems(list);
    list.clear();
    //sender set
    list<<"PWD"<<"observer";
    ui->comboBox_calibration_input_mor_stlye->addItems(list);
    list.clear();
}



void RVR_DefaultSet::on_pushButton_recover_clicked()
{
    //    if(defalutMap.count() < 4){
    //    Reminder_Mseg::showMessageboxError("出厂配置信息丢失，恢复失败");
    //    }
    emit default_set_option("recover_set",defalutMap);
}

void RVR_DefaultSet::select_from(int fId)
{
    if(fromId == fId) return;
    if(fromId == 1){
        ui->groupBox_defaultSet->setGeometry(900,10,811,471);
    }
    else if(fromId == 2){
        ui->groupBox_Threshold->setGeometry(900,10,811,471);
    }
    else if(fromId == 3){
        ui->groupBox_send_set->setGeometry(900,10,811,471);
    }
    else if(fromId == 4){
        ui->groupBox_Enable->setGeometry(900,10,811,471);
    }
    else if(fromId == 5){
        ui->groupBox_waring->setGeometry(900,10,811,471);
    }
    else if(fromId == 6){
        ui->groupBox_RVRClac->setGeometry(900,10,811,471);
    }
    else if(fromId == 7){
        ui->groupBox_main_select->setGeometry(900,10,811,471);
    }

    if(fId == 1){
        fromId = 1;
        ui->groupBox_defaultSet->setGeometry(40,10,811,471);
    }
    else if(fId == 2){
        fromId = 2;
        ui->groupBox_Threshold->setGeometry(40,10,811,471);
    }
    else if(fId == 3){
        fromId = 3;
        ui->groupBox_send_set->setGeometry(40,10,811,471);
    }
    else if(fId == 4){
        fromId = 4;
        ui->groupBox_Enable->setGeometry(40,10,811,471);
    }
    else if(fId == 5){
        fromId = 5;
        ui->groupBox_waring->setGeometry(40,10,811,471);
    }
    else if(fId == 6){
        fromId = 6;
        ui->groupBox_RVRClac->setGeometry(40,10,811,471);
    }
    else if(fId == 7){
        fromId = 7;
        ui->groupBox_main_select->setGeometry(40,10,811,471);
    }
}


void RVR_DefaultSet::on_pushButton_defalut_set_clicked(){
    select_from(1);
    ui->groupBox_selectButton->show();
}

void RVR_DefaultSet::on_pushButton_enable_clicked(){
    select_from(4);
    ui->groupBox_selectButton->show();
}

void RVR_DefaultSet::on_pushButton_waring_clicked(){
    select_from(5);
    ui->groupBox_selectButton->show();
}

void RVR_DefaultSet::on_pushButton_Threshold_clicked(){
    select_from(2);
    ui->groupBox_selectButton->show();
}

void RVR_DefaultSet::on_pushButton_send_set_clicked(){
    select_from(3);
    ui->groupBox_selectButton->show();
}

void RVR_DefaultSet::on_pushButton_2_clicked(){
    select_from(6);
    ui->groupBox_selectButton->show();
}
void RVR_DefaultSet::on_pushButton_back_clicked()
{
    select_from(7);
    ui->groupBox_selectButton->hide();
}


//eable
void RVR_DefaultSet::on_checkBox_RVR_clicked()
{
    QMap<QString,QString>map;
    if(ui->checkBox_RVR->isChecked()){
        map["RVR"] = "1";
    }else{
        map["RVR"] = "0";
    }
    emit default_set_option("enable_RVR",map);
}

void RVR_DefaultSet::on_checkBox_hinderLight_clicked()
{
    QMap<QString,QString>map;
    if(ui->checkBox_hinderLight->isChecked()){
        map["hinderlight"] = "1";
    }else{
        map["hinderlight"] = "0";
    }
    emit default_set_option("enable_hinder_light",map);

}

void RVR_DefaultSet::on_checkBox_reciLower_clicked()
{
    QMap<QString,QString>map;
    if(ui->checkBox_reciLower->isChecked()){
        map["recilower"] = "1";
    }else{
        map["recilower"] = "0";
    }
    emit default_set_option("enable_reci_blower",map);
}

void RVR_DefaultSet::on_checkBox_sendLower_clicked()
{
    QMap<QString,QString>map;
    if(ui->checkBox_sendLower->isChecked()){
        map["sendlower"] = "1";
    }else{
        map["sendlower"] = "0";
    }
    emit default_set_option("enable_send_blower",map);

}

void RVR_DefaultSet::on_radioButton_auto_clicked()
{
    QMap<QString,QString>map;
    if(ui->radioButton_auto->isChecked())
    {
        map["messmodel"] = "1";
    }else{
        map["messmodel"] = "2";
    }
    emit default_set_option("message_model",map);
}

void RVR_DefaultSet::on_radioButton_loop_clicked()
{
    QMap<QString,QString>map;
    if(ui->radioButton_auto->isChecked())
    {
        map["messmodel"] = "1";
    }else{
        map["messmodel"] = "2";
    }
    emit default_set_option("message_model",map);
}

void RVR_DefaultSet::on_pushButton_base_WinRai_clicked()
{
    QMap<QString,QString> map;
    QString baseline = ui->lineEdit_baseline->text().trimmed();
    QString wr = ui->lineEdit_windrain->text().trimmed();
    map["baseline"] = baseline;
    map["wind_rain"] = wr;
    if((baseline.toInt() < 65536)&&(wr.toInt() < 256)){
        emit baseSignal(baseline);
        emit rainWindSignal(wr);
        emit default_set_option("set_wind_rain",map);
    }
    else{
        Reminder_Mseg::showMessageboxInfo("输入的数据有误\n基线应小于65535风雨罩应小于256");
    }
}

//commit config
void RVR_DefaultSet::on_pushButton_commit_set_clicked()
{
    QMap<QString,QString>map;
    map["id"] = ui->comboBox_Id->currentText().trimmed();
    map["baud"] = ui->comboBox_baud->currentText().trimmed();
    map["datas"] = ui->comboBox_datas->currentText().trimmed();
    map["stop"] = ui->comboBox_stop->currentText().trimmed();
    map["parity"] = ui->comboBox_parity->currentText().trimmed();
    emit default_set_option("serial_set",map);
}

void RVR_DefaultSet::on_pushButton_sever_set_clicked()
{
    QMap<QString,QString>map;
    map["id"] = ui->lineEdit_id->text();
    map["locaton"] = ui->lineEdit_location->text();
    map["pullte"] = ui->comboBox_pullte->currentText().trimmed();
    map["factory"] = ui->comboBox_factory->currentText().trimmed();
    map["electrity"] = ui->comboBox_electrity->currentText().trimmed();
    map["mojr_second"] = ui->comboBoxMojr_secend->currentText().trimmed();
    map["reci_fever"] = ui->comboBox_reciver_fever->currentText().trimmed();
    map["send_fever"] = ui->comboBox_send_fever->currentText().trimmed();
    map["buzzer"] = ui->comboBox_buzzer->currentText().trimmed();
    emit default_set_option("device_set",map);
}

void RVR_DefaultSet::on_pushButton_Threshold_set_clicked()
{
    QMap<QString,QString>map;
    map["hinderlight"] = ui->lineEdit_hinderlight->text().trimmed();
    map["runupmin"] = ui->lineEdit_runuplight->text().trimmed();
    map["alignmentsignal"] = ui->lineEdit_alignmentsignal->text().trimmed();
    map["calfact"] = ui->lineEdit_calfact->text().trimmed();
    map["stuptemperature"] = ui->lineEdit_stupe_temperatrue->text().trimmed();
    map["stoptemperature"] = ui->lineEdit_stop_temperatrue->text().trimmed();
    map["inside_max_humidity"] = ui->lineEdit_inside_max_humidity->text().trimmed();
    map["4-50"] = ui->lineEdit_4_50->text().trimmed();
    map["51-999"] = ui->lineEdit_51_999->text().trimmed();
    map["1000-12000"] = ui->lineEdit_1000_12000->text().trimmed();
    map["gt12000"] = ui->lineEdit_gt_12000->text().trimmed();
    map["gyr_reciv_Vup"] = ui->lineEdit_reciv_Vup->text().trimmed();
    map["gyr_reciv_Hup"] = ui->lineEdit_reciv_Hup->text().trimmed();
    map["gyr_reciv_font_back_up"] = ui->lineEdit_recived_font_back_up->text().trimmed();
    map["gyr_send_Vup"] = ui->lineEdit_send_Vup->text().trimmed();
    map["gyr_send_Hup"] = ui->lineEdit__send_Hup->text().trimmed();
    map["gyr_send_font_back_up"] = ui->lineEdit_send_font_back_up->text().trimmed();
    emit default_set_option("Threshold_set",map);
}

void RVR_DefaultSet::on_pushButton_RVR_Calc_confirm_set_clicked()
{
    QMap<QString,QString>map;
    map["RVR_Calc_enanle"] = (ui->comboBox_RVR_Clac_open->currentText().trimmed()) == "开启" ? "1":"0";
    map["message_port"] = (ui->comboBox_MessagePort->currentText().trimmed()) == "维护端口" ? "1":"0";
    map["down_value"] = ui->lineEdit_RVR_Calc_down_value->text().trimmed();
    map["up_value"] = ui->lineEdit_RVR_Calc_up_value->text().trimmed();
    map["RVR_samp_interval"] = ui->lineEdit_RVR_samp_interval->text().trimmed();
    map["Mor_accuracy"] = ui->lineEdit_Mor_accuracy->text().trimmed();
    map["RVR_accuracy"] = ui->lineEdit_RVR_accuracy->text().trimmed();
    map["RVR_pollution_Cover"] = ui->lineEdit_RVR_pollution_Cover->text().trimmed();
    emit default_set_option("RVR_Calc_value",map);
}

//sender config
void RVR_DefaultSet::on_pushButton_sender_confirm_clicked()
{
    QMap<QString,QString>map;
    map["electric_strength"] = ui->lineEdit_electric_strength->text().trimmed();
    map["pwm_frequency"] = ui->lineEdit_pwm_frequency->text().trimmed();
    map["input_mor_stlye"] = (ui->comboBox_calibration_input_mor_stlye->currentText().trimmed()) == "PWD" ? "1":"2";
    emit default_set_option("senderarguments",map);
}


