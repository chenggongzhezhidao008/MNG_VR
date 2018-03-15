#include "rvr_alignment.h"
#include "ui_rvr_alignment.h"

#include "mess/RVR_Reminder_Msg.h"

RVR_Alignment::RVR_Alignment(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RVR_Alignment)
{
    ui->setupUi(this);
    ini_UI();
    send_initFlage = false;
    reci_initFlage  = false;
    sender_X = "\0";
    sender_Y = "\0";
    sender_Z = "\0";
    reciver_X = "\0";
    reciver_Y = "\0";
    reciver_Z = "\0";
    ui->groupBox_send_current->setTitle("未初始化值");
    ui->groupBox_reciver_current->setTitle("未初始化值");

    //    installEventFilter(this);
}

RVR_Alignment::~RVR_Alignment()
{
    delete ui;
}

//bool RVR_Alignment::eventFilter(QObject *obj, QEvent *event)
//{
//    qDebug()<<"执行事件了"<<obj->dynamicPropertyNames()<<"事件"<<event;
//    if (event->type() == QKeyEvent::ShortcutOverride||
//            event->type() ==QKeyEvent::KeyPress||
//            event->type() ==QKeyEvent::KeyRelease) {
//        qDebug()<<"返回了";

//    }
//    return true;
////    return QObject::eventFilter(obj, event);
//}


void RVR_Alignment::ini_UI()
{
    ui->groupBox_reciver_init->hide();
    ui->groupBox_send_init->hide();
    {
        ui->pushButton_cansle_rec->hide();
        ui->pushButton_cansle_sen->hide();
    }
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(100);
    ui->lineEdit_sgnal->setText("0.0%");
    ui->progressBar->setValue(0);
//    ui->lineEdit_CurrentX_rec->setReadOnly(true);
//    ui->lineEdit_CurrentY_rec->setReadOnly(true);
//    ui->lineEdit_CurrentZ_rec->setReadOnly(true);
//    ui->lineEdit_CurrentY_sen->setReadOnly(true);
//    ui->lineEdit_CurrentX_sen->setReadOnly(true);
//    ui->lineEdit_CurrentZ_sen->setReadOnly(true);
//    ui->lineEdit_initX_sen->setReadOnly(true);
//    ui->lineEdit_initY_sen->setReadOnly(true);
//    ui->lineEdit_initZ_sen->setReadOnly(true);
//    ui->lineEdit_initX_rec->setReadOnly(true);
//    ui->lineEdit_initY_rec->setReadOnly(true);
//    ui->lineEdit_initZ_rec->setReadOnly(true);

//    ui->lineEdit_CurrentX_rec->setAlignment(Qt::AlignCenter);
//    ui->lineEdit_CurrentY_rec->setAlignment(Qt::AlignCenter);
//    ui->lineEdit_CurrentZ_rec->setAlignment(Qt::AlignCenter);
//    ui->lineEdit_CurrentY_sen->setAlignment(Qt::AlignCenter);
//    ui->lineEdit_CurrentX_sen->setAlignment(Qt::AlignCenter);
//    ui->lineEdit_CurrentZ_sen->setAlignment(Qt::AlignCenter);
//    ui->lineEdit_initX_sen->setAlignment(Qt::AlignCenter);
//    ui->lineEdit_initY_sen->setAlignment(Qt::AlignCenter);
//    ui->lineEdit_initZ_sen->setAlignment(Qt::AlignCenter);
//    ui->lineEdit_initX_rec->setAlignment(Qt::AlignCenter);
//    ui->lineEdit_initY_rec->setAlignment(Qt::AlignCenter);
//    ui->lineEdit_initZ_rec->setAlignment(Qt::AlignCenter);

    ui->lineEdit_sgnal->setReadOnly(true);
    ui->lineEdit_sgnal->setAlignment(Qt::AlignCenter);
    ui->lineEdit_send_Xdegree->setReadOnly(true);
    ui->lineEdit_send_Ydegree->setReadOnly(true);
    ui->lineEdit_send_Zdegree->setReadOnly(true);
    ui->lineEdit_reciv_Xdegree->setReadOnly(true);
    ui->lineEdit_reciv_Ydegree->setReadOnly(true);
    ui->lineEdit_reciv_Zdegree->setReadOnly(true);
    ui->lineEdit_send_Xdegree->setAlignment(Qt::AlignCenter);
    ui->lineEdit_send_Ydegree->setAlignment(Qt::AlignCenter);
    ui->lineEdit_send_Zdegree->setAlignment(Qt::AlignCenter);
    ui->lineEdit_reciv_Xdegree->setAlignment(Qt::AlignCenter);
    ui->lineEdit_reciv_Ydegree->setAlignment(Qt::AlignCenter);
    ui->lineEdit_reciv_Zdegree->setAlignment(Qt::AlignCenter);

}

void RVR_Alignment::update_data(QByteArray,QMap<QString,QString> dataMap)
{
    if(!send_initFlage)
    {
        ui->lineEdit_CurrentY_sen->setText(dataMap["sender_Y"]);
        ui->lineEdit_CurrentX_sen->setText(dataMap["sender_X"]);
        ui->lineEdit_CurrentZ_sen->setText(dataMap["sender_Z"]);
    }
    else
    {
        ui->lineEdit_initX_sen->setText(QString::number(
        (dataMap["sender_X"].trimmed().toInt() - this->sender_X.toInt()),10));
        ui->lineEdit_initY_sen->setText(QString::number(
        (dataMap["sender_Y"].trimmed().toInt() - this->sender_Y.toInt()),10));
        ui->lineEdit_initZ_sen->setText(QString::number(
        (dataMap["sender_Z"].trimmed().toInt() - this->sender_Z.toInt()),10));
    }

    if(!reci_initFlage)
    {
        ui->lineEdit_CurrentX_rec->setText(dataMap["reciver_X"]);
        ui->lineEdit_CurrentY_rec->setText(dataMap["reciver_Y"]);
        ui->lineEdit_CurrentZ_rec->setText(dataMap["reciver_Z"]);
    }
    else
    {
        ui->lineEdit_initX_rec->setText(QString::number(
        (dataMap["reciver_X"].trimmed().toInt() - this->reciver_X.toInt()),10));
        ui->lineEdit_initY_rec->setText(QString::number(
        (dataMap["reciver_Y"].trimmed().toInt() - this->reciver_Y.toInt()),10));
        ui->lineEdit_initZ_rec->setText(QString::number(
        (dataMap["reciver_Z"].trimmed().toInt() - this->reciver_Z.toInt()),10));
    }
}

void RVR_Alignment::messageShow(const QString mess)
{
    Reminder_Mseg::showMessageboxInfo(mess);
}

void RVR_Alignment::waring_signal(QByteArray , QMap<QString, QString> dataMap)
{
    int percent = (dataMap["align_Sig"]).toInt();
    if(percent > 64){
        ui->progressBar->setValue(100);
        ui->lineEdit_sgnal->setText("100%");
    }
    else {
        ui->progressBar->setValue(percent);
        ui->lineEdit_sgnal->setText(dataMap["align_Sig"]+"%");
    }
    if(percent > 50){
        if(percent > 80){
            ui->label_signal_status->setText("ok");
        }
        else{
            ui->label_signal_status->setText("当前对准状况欠佳，需校正");
        }
    }else{
        ui->label_signal_status->setText("没有对准，请校正");
    }
}

void RVR_Alignment::show_groyXYZZeroValue(QByteArray , QMap<QString, QString> dataMap)
{
    ui->lineEdit_send_Xdegree->setText(dataMap["send_X"]);
    ui->lineEdit_send_Ydegree->setText(dataMap["send_Y"]);
    ui->lineEdit_send_Zdegree->setText(dataMap["send_Z"]);
    ui->lineEdit_reciv_Xdegree->setText(dataMap["reci_X"]);
    ui->lineEdit_reciv_Ydegree->setText(dataMap["reci_Y"]);
    ui->lineEdit_reciv_Zdegree->setText(dataMap["reci_Z"]);
}

void RVR_Alignment::on_pushButton_init_sen_clicked()
{
    //    QMap<QString,QString> map;//要下发发射机的初始化陀螺仪的数据时用
    //      emit groyOption("gyro_xyz",map);//读取陀螺仪值
    if(!send_initFlage && ui->lineEdit_CurrentX_sen->text().trimmed()=="")
    {
        Reminder_Mseg::showMessageboxError("发射机陀螺仪初始化失败!\n请检查陀螺仪是否正常。");
        return ;
    }
    if(!send_initFlage){

        //        要下发发射机的初始化陀螺仪的数据时用
        //        QString data = ui->lineEdit_CurrentX_sen->text();
        //        map["sender_X"] = data;
        //        ui->lineEdit_initX_sen->setText(data);

        //        data = ui->lineEdit_CurrentY_sen->text();
        //        map["sender_Y"] = data;
        //        ui->lineEdit_initY_sen->setText(data);

        //        data = ui->lineEdit_CurrentZ_sen->text();
        //        map["sender_Z"] = data;
        //        ui->lineEdit_initZ_sen->setText(data);

        //        ui->groupBox_send_current->setTitle("当前值");
        //        ui->groupBox_send_init->show();
        //        ui->pushButton_init_sen->setText("取消初始化");
        //        send_initFlage = true;
        //        emit groyOption("init_gyro_send",map);

        QString data = ui->lineEdit_CurrentX_sen->text().trimmed();
        sender_X = data;

        data = ui->lineEdit_CurrentY_sen->text().trimmed();
        sender_Y = data;

        data = ui->lineEdit_CurrentZ_sen->text().trimmed();
        sender_Z = data;

        ui->groupBox_send_current->setTitle("初始化值");
        ui->groupBox_send_current->setEnabled(false);
        ui->groupBox_send_init->show();
        ui->groupBox_send_init->setTitle("当前偏移值");
        ui->pushButton_init_sen->setText("取消初始化");
        send_initFlage = true;

    }
    else{
        ui->groupBox_send_current->setTitle("未初始化值");
        ui->groupBox_send_current->setEnabled(true);
        ui->groupBox_send_init->hide();
        //        ui->pushButton_init_sen->setText("初始化");
        send_initFlage = false;
    }
}

void RVR_Alignment::on_pushButton_init_rec_clicked()
{
    //      QMap<QString,QString> map;//要下发接收机的初始化陀螺仪的数据时用
    //      emit groyOption("gyro_xyz",map);//往下读取陀螺仪值
    if(!reci_initFlage && ui->lineEdit_CurrentX_rec->text().trimmed()=="")
    {
        Reminder_Mseg::showMessageboxError("接收机陀螺仪初始化失败!\n请检查陀螺仪是否正常。");
        return ;
    }
    if(!reci_initFlage){

        //        要下发接机的初始化陀螺仪的数据时用
        //        QString data = ui->lineEdit_CurrentX_rec->text();
        //        map["reciver_X"] = data;
        //        ui->lineEdit_initX_rec->setText(data);

        //        data = ui->lineEdit_CurrentY_rec->text();
        //        map["reciver_Y"] = data;
        //        ui->lineEdit_initY_rec->setText(data);

        //        data =ui->lineEdit_CurrentZ_rec->text();
        //        map["reciver_Z"] = data;
        //        ui->lineEdit_initZ_rec->setText(data);

        //        ui->groupBox_reciver_current->setTitle("当前值");
        //        ui->groupBox_reciver_init->show();
        //        ui->pushButton_init_rec->setText("取消初始化");
        //        reci_initFlage = true;
        //        emit groyOption("init_gyro_reci",map);

        //    }
        //    else{
        //        ui->groupBox_reciver_init->hide();
        //        ui->pushButton_init_rec->setText("初始化");
        //        reci_initFlage = false;
        //    }


        QString data = ui->lineEdit_CurrentX_rec->text().trimmed();
        reciver_X = data;

        data = ui->lineEdit_CurrentY_rec->text().trimmed();
        reciver_Y = data;

        data =ui->lineEdit_CurrentZ_rec->text().trimmed();
        reciver_Z = data;

        ui->groupBox_reciver_current->setTitle("初始化值");
        ui->groupBox_reciver_current->setEnabled(false);
        ui->groupBox_reciver_init->show();
        ui->groupBox_reciver_init->setTitle("当前偏移值");
        ui->pushButton_init_rec->setText("取消初始化");
        reci_initFlage = true;

    }
    else{
        ui->groupBox_reciver_current->setTitle("未初始化值");
        ui->groupBox_reciver_current->setEnabled(true);
        ui->groupBox_reciver_init->hide();
        //        ui->pushButton_init_sen->setText("初始化");
        reci_initFlage = false;
    }
}

void RVR_Alignment::on_pushButton_groy_setZero_clicked()
{
    QMap<QString,QString> data;
    emit groyOption("groy_setZero",data);
}
