#include "rvr_defaultconfig.h"
#include "ui_rvr_defaultconfig.h"

RVR_DefaultConfig::RVR_DefaultConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RVR_DefaultConfig)
{
    ui->setupUi(this);
}

RVR_DefaultConfig::~RVR_DefaultConfig()
{
    delete ui;
}
void RVR_DefaultConfig::setDefaultInfo(QMap<QString,QString> cur_serial)
{
    ui->label_port->setText(cur_serial["port"]);
    ui->label_baud->setText(cur_serial["baud"]);
    ui->label_datas->setText(cur_serial["datas"]);
    ui->label_stop->setText(cur_serial["stop"]);
    ui->label_parity->setText(cur_serial["parity"]);
}











