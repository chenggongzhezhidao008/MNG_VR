#include "rvr_calibration.h"
#include "ui_rvr_calibration.h"
#include "mess/RVR_Reminder_Msg.h"
#include <QRegExp>
#include <QRegExpValidator>


RVR_Calibration::RVR_Calibration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RVR_Calibration)
{
    ui->setupUi(this);
    initUi();
}

void RVR_Calibration::initUi()
{
    ui->lineEdit_CAL_Fact->setReadOnly(true);
    QStringList list;
    list<<"人工观测"<<"自动校准";
    ui->comboBox_calibration_style->addItems(list);
    list.clear();
    ui->lineEdit_CAL_Fact->setAlignment(Qt::AlignCenter);
    ui->lineEdit_offset_Value->setReadOnly(true);
    ui->lineEdit_offset_Value->setAlignment(Qt::AlignCenter);
    ui->lineEdit_full_scale_value->setAlignment(Qt::AlignCenter);
    QRegExp regExp("[0-9]{5}");
    ui->lineEdit_full_scale_value->setValidator(new QRegExpValidator(regExp, this));
}

RVR_Calibration::~RVR_Calibration()
{
    delete ui;
}

void RVR_Calibration::cal_fact(QByteArray , QMap<QString, QString> dataMap)
{
    ui->lineEdit_CAL_Fact->setText(dataMap["calibrationValue"]);
}

void RVR_Calibration::fullScaaleValueSlot(QByteArray , QMap<QString, QString> dataMap)
{
    if(dataMap["clibration_fullScale_value"] == "ok"){
        Reminder_Mseg::showMessageboxInfo("fullScale输入成功");
    }
}

//offset value show
void RVR_Calibration::calibrationOffsetValue(QByteArray , QMap<QString, QString> dataMap)
{
    ui->lineEdit_offset_Value->setText(dataMap["clibration_offset_value"]);
}

void RVR_Calibration::on_pushButton_Full_calibraion_clicked()
{
    QMap<QString,QString> data;
    QString str = ui->lineEdit_full_scale_value->text().trimmed();
    data["full_scale_value"] = str;
    emit calibrationOption("full_calibration",data);
}

void RVR_Calibration::on_pushButton_offset_clicked()
{
    QMap<QString,QString> data;
    data["offset_value"] = "ok";
    emit calibrationOption("offset_calibration",data);
}

void RVR_Calibration::on_pushButton_7_clicked()
{
    ui->lineEdit_offset_Value->clear();
}
