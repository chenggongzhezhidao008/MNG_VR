#include "rvr_currentconfig.h"
#include "ui_rvr_currentconfig.h"
#include <QDebug>

RVR_Currentconfig::RVR_Currentconfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RVR_Currentconfig)
{
    ui->setupUi(this);
    currentPort = "";
}

RVR_Currentconfig::~RVR_Currentconfig()
{
    delete ui;
}

void RVR_Currentconfig::setSeialPort(QString port)
{
     this->currentPort = port;
}

void RVR_Currentconfig::getcurrentInfo(QMap<QString,QString> cur_serial)
{
     qDebug()<<"current map:"<<cur_serial;
     cur_serial["port"] = this->currentPort;
     ui->label_port->setText(cur_serial["port"]);
     ui->label_deviceId->setText(cur_serial["id"]);
     ui->label_baud->setText(cur_serial["baud"]);
     ui->label_datas->setText(cur_serial["datas"]);
     ui->label_stop->setText(cur_serial["stop"]);
     ui->label_parity->setText(cur_serial["parity"]);
}

