#include "rvr_calc_values.h"
#include "ui_rvr_calc_values.h"
#include <QTextCharFormat>
#include <QTextCursor>
#include <QLineEdit>

#include "mess/RVR_Reminder_Msg.h"

RVR_Calc_values::RVR_Calc_values(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RVR_Calc_values)
{
    ui->setupUi(this);
    initUI();
}

RVR_Calc_values::~RVR_Calc_values()
{
    delete ui;
}

void RVR_Calc_values::initUI()
{
    QStringList list;
    list<<"BrightDay"<<"NormalDay"<<"Intermediate"<<"Night";
    ui->comboBox_background_light->addItems(list);
    list.clear();
    list<<"1%"<<"3%"<<"10%"<<"30%"<<"100%";
    ui->comboBox_run_up_light->addItems(list);
    list.clear();
    back_light = "BrightDay";
    run_light = "1%";
    this->setWindowTitle("RVR计算参数");
}

void RVR_Calc_values::on_pushButton_clicked()
{
    QMap<QString,QString> data;
    back_light = ui->comboBox_background_light->currentText().trimmed();
    data["backgroundlight"] = back_light;
    run_light = ui->comboBox_run_up_light->currentText().trimmed();
    data["run_up_light"] = run_light;
    emit calc_Value("calc_values",data);
    data.clear();

    if(back_light == "BrightDay")data["backgroundlight"] = "0.008";
    else if(back_light == "NormalDay")data["backgroundlight"] = "0.0008";
    else if(back_light == "Intermediate")data["backgroundlight"] = "0.00008";
    else if(back_light == "Night")data["backgroundlight"] = "0.0000008";

    if(run_light == "1%")data["run_up_light"] = "100.0"; //2016.12.28改
    else if(run_light == "3%")data["run_up_light"] = "300.0";
    else if(run_light == "10%")data["run_up_light"] = "1000.0";
    else if(run_light == "30%")data["run_up_light"] = "3000.0";
    else if(run_light == "100%")data["run_up_light"] = "10000.0";
    emit calc_Value("maintain_RVR_calc",data);
}

void RVR_Calc_values::on_pushButton_back_clicked()
{
    if((back_light != ui->comboBox_background_light->currentText().trimmed())||
            (run_light != ui->comboBox_run_up_light->currentText().trimmed())){
        Reminder_Mseg::showMessageboxInfo("参数设置未提交");
        ui->comboBox_background_light->setCurrentText( back_light);
        ui->comboBox_run_up_light->setCurrentText(run_light);
    }
    hide();
}
