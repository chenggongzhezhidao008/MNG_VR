#include "rvr_lineartest.h"
#include "ui_rvr_lineartest.h"
#include "mess/RVR_Reminder_Msg.h"
#include <QMap>
#include <QRegExp>
#include <QRegExpValidator>
#include <qmath.h>

RVR_LinearTest::RVR_LinearTest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RVR_LinearTest)
{
    ui->setupUi(this);
    index = 0;
    ui->lineEdit_morValue_1->setReadOnly(true);
    ui->lineEdit_morValue_2->setReadOnly(true);
    ui->lineEdit_morValue_3->setReadOnly(true);
    ui->lineEdit_morValue_4->setReadOnly(true);
    ui->lineEdit_morValue_5->setReadOnly(true);
    ui->lineEdit_morValue_6->setReadOnly(true);
    ui->lineEdit_morValue_7->setReadOnly(true);
    ui->lineEdit_morValue_8->setReadOnly(true);
    enabledButton(0);
    QRegExp rexExp("[^\d+$]{6}");//V1.1.2
    ui->lineEdit_input_1->setValidator(new QRegExpValidator(rexExp,this));
    ui->lineEdit_input_2->setValidator(new QRegExpValidator(rexExp,this));
    ui->lineEdit_input_3->setValidator(new QRegExpValidator(rexExp,this));
    ui->lineEdit_input_4->setValidator(new QRegExpValidator(rexExp,this));
    ui->lineEdit_input_5->setValidator(new QRegExpValidator(rexExp,this));
    ui->lineEdit_input_6->setValidator(new QRegExpValidator(rexExp,this));
    ui->lineEdit_input_7->setValidator(new QRegExpValidator(rexExp,this));
    ui->lineEdit_input_8->setValidator(new QRegExpValidator(rexExp,this));
    ui->lineEdit_morOffset_1->setReadOnly(true);
    ui->lineEdit_morOffset_2->setReadOnly(true);
    ui->lineEdit_morOffset_3->setReadOnly(true);
    ui->lineEdit_morOffset_4->setReadOnly(true);
    ui->lineEdit_morOffset_5->setReadOnly(true);
    ui->lineEdit_morOffset_6->setReadOnly(true);
    ui->lineEdit_morOffset_7->setReadOnly(true);
    ui->lineEdit_morOffset_8->setReadOnly(true);
    this->inputValue = "";
}

RVR_LinearTest::~RVR_LinearTest()
{
    delete ui;
}

void RVR_LinearTest::setTValue(QByteArray , QMap<QString, QString> dataMap)
{
    QString linestr = dataMap["lineValue"];
    qreal baseLength = qreal(this->baseline.toDouble() - this->windraincover.toDouble());
    qreal input = (-baseLength * 3)/qLn(qreal(this->inputValue.toDouble())/100);
    qreal calc =  (-baseLength * 3)/qLn(qreal(linestr.toDouble()));
    qreal result = (qAbs(input - calc) / input) * qreal(100.0);//V1.1.2
    QString offsetValue = QString("%1").arg(result);
    qDebug()<<"::"<<result;

    if(index == 1){
        writeTValue(ui->lineEdit_morValue_1,linestr,
                    ui->lineEdit_morOffset_1,offsetValue);
        enabledButton(1);
    }
    else if(index == 2){
        writeTValue(ui->lineEdit_morValue_2,linestr,
                    ui->lineEdit_morOffset_2,offsetValue);
        enabledButton(2);
    }
    else if(index == 3){
        writeTValue(ui->lineEdit_morValue_3,linestr,
                    ui->lineEdit_morOffset_3,offsetValue);
        enabledButton(3);
    }
    else if(index == 4){
        writeTValue(ui->lineEdit_morValue_4,linestr,
                    ui->lineEdit_morOffset_4,offsetValue);
        enabledButton(4);
    }
    else if(index == 5){
        writeTValue(ui->lineEdit_morValue_5,linestr,
                    ui->lineEdit_morOffset_5,offsetValue);
        enabledButton(5);
    }
    else if(index == 6){
        writeTValue(ui->lineEdit_morValue_6,linestr,
                    ui->lineEdit_morOffset_6,offsetValue);
        enabledButton(6);
    }
    else if(index == 7){
        writeTValue(ui->lineEdit_morValue_7,linestr,
                    ui->lineEdit_morOffset_7,offsetValue);
        enabledButton(7);
    }
    else if(index == 8){
        writeTValue(ui->lineEdit_morValue_8,linestr,
                    ui->lineEdit_morOffset_8,offsetValue);
        enabledButton(8);
    }
}
//write Tvalue and offset value
void RVR_LinearTest::writeTValue(QLineEdit *TValueLineEdit, QString TValue,
                                 QLineEdit *offsetLineEdit, QString offSetValue)
{
    TValueLineEdit->setText(TValue);
    if(offSetValue.length()> 4){//V1.1.2
        offsetLineEdit->setText(offSetValue.mid(0,4));
    }
    else{
        offsetLineEdit->setText(offSetValue);
    }
}

//set baseline length
void RVR_LinearTest::setBaseline(QString lengthStr)
{
    this->baseline = lengthStr;
}

//set wind rain cover
void RVR_LinearTest::setWindRainCover(QString lengthStr)
{
    qDebug()<<"wind rain updated";
    this->windraincover = lengthStr;
}

void RVR_LinearTest::on_pushButton_test_one_clicked()
{
    sendValue(1,ui->lineEdit_input_1);
}

void RVR_LinearTest::on_pushButton_test_two_clicked()
{
    sendValue(2,ui->lineEdit_input_2);
}

void RVR_LinearTest::on_pushButton_test_three_clicked()
{
    sendValue(3,ui->lineEdit_input_3);
}

void RVR_LinearTest::on_pushButton_test_four_clicked()
{
    sendValue(4,ui->lineEdit_input_4);
}

void RVR_LinearTest::on_pushButton_test_five_clicked()
{
    sendValue(5,ui->lineEdit_input_5);
}

void RVR_LinearTest::on_pushButton_test_six_clicked()
{
    sendValue(6,ui->lineEdit_input_6);
}

void RVR_LinearTest::on_pushButton_test_seven_clicked()
{
    sendValue(7,ui->lineEdit_input_7);
}

void RVR_LinearTest::on_pushButton_test_eigth_clicked()
{
    sendValue(8,ui->lineEdit_input_8);
}

void RVR_LinearTest::sendValue(int i, QLineEdit *edit)
{
    QString str = edit->text().trimmed();
    if(str == ""){
        Reminder_Mseg::showMessageboxError("请输入值");
        return ;
    }
    else{
        if(str.toFloat() > 9999.0){
            Reminder_Mseg::showMessageboxError("输入值过大,请检查");
            return ;
        }
        index = i;
        edit->setReadOnly(true);
        this->inputValue = edit->text();//用于计算误差值
        QMap<QString,QString> map;
        QString dir = ".";
        int pos = str.indexOf(dir);
        qDebug()<<"length:"<<str.length();
        if(pos >= 0){
            str.remove(pos,str.length()- pos).trimmed();
            qDebug()<<". pos:"<<QString::number(pos)<<str;
        }                                                 //qDebug()<<". pos:"<<QString::number(pos)<<"remove:"<<str;
        map["line_test_input_value"] = str;
        emit lineTest("line_test",map);
    }
}

void RVR_LinearTest::enabledButton(int i)
{
    ui->pushButton_test_one->setEnabled(false);
    ui->pushButton_test_one->setStyleSheet("color:gray");
    ui->pushButton_test_two->setEnabled(false);
    ui->pushButton_test_two->setStyleSheet("color:gray");
    ui->pushButton_test_three->setEnabled(false);
    ui->pushButton_test_three->setStyleSheet("color:gray");
    ui->pushButton_test_four->setEnabled(false);
    ui->pushButton_test_four->setStyleSheet("color:gray");
    ui->pushButton_test_five->setEnabled(false);
    ui->pushButton_test_five->setStyleSheet("color:gray");
    ui->pushButton_test_six->setEnabled(false);
    ui->pushButton_test_six->setStyleSheet("color:gray");
    ui->pushButton_test_seven->setEnabled(false);
    ui->pushButton_test_seven->setStyleSheet("color:gray");
    ui->pushButton_test_eigth->setEnabled(false);
    ui->pushButton_test_eigth->setStyleSheet("color:gray");

    if(i == 0) {
        ui->pushButton_test_one->setEnabled(true);
        ui->pushButton_test_one->setStyleSheet("color:white");
    }
    else if(i == 1){
        ui->pushButton_test_two->setEnabled(true);
        ui->pushButton_test_two->setStyleSheet("color:white");
    }
    else if(i == 2){
        ui->pushButton_test_three->setEnabled(true);
        ui->pushButton_test_three->setStyleSheet("color:white");
    }
    else if(i == 3){
        ui->pushButton_test_four->setEnabled(true);
        ui->pushButton_test_four->setStyleSheet("color:white");
    }
    else if(i == 4){
        ui->pushButton_test_five->setEnabled(true);
        ui->pushButton_test_five->setStyleSheet("color:white");
    }
    else if(i == 5){
        ui->pushButton_test_six->setEnabled(true);
        ui->pushButton_test_six->setStyleSheet("color:white");
    }
    else if(i == 6){
        ui->pushButton_test_seven->setEnabled(true);
        ui->pushButton_test_seven->setStyleSheet("color:white");
    }
    else if(i == 7){
        ui->pushButton_test_eigth->setEnabled(true);
        ui->pushButton_test_eigth->setStyleSheet("color:white");
    }
    else if(i == 8){
        Reminder_Mseg::showMessageboxInfo("线性测试完成");
    }
}

void RVR_LinearTest::clearContext(QLineEdit *editIn,QLineEdit *editout,QLineEdit *editoffset,QPushButton *button)
{
    editIn->setReadOnly(false);
    editIn->clear();
    editout->clear();
    editoffset->clear();
    button->setEnabled(true);
    button->setStyleSheet("color:white");
}



void RVR_LinearTest::on_pushButton_clear_one_clicked()
{
    clearContext(ui->lineEdit_input_1,ui->lineEdit_morValue_1,ui->lineEdit_morOffset_1,ui->pushButton_test_one);
}

void RVR_LinearTest::on_pushButton_clear_two_clicked()
{
    clearContext(ui->lineEdit_input_2,ui->lineEdit_morValue_2,ui->lineEdit_morOffset_2,ui->pushButton_test_two);
}

void RVR_LinearTest::on_pushButton_clear_three_clicked()
{
    clearContext(ui->lineEdit_input_3,ui->lineEdit_morValue_3,ui->lineEdit_morOffset_3,ui->pushButton_test_three);
}

void RVR_LinearTest::on_pushButton_clear_four_clicked()
{
    clearContext(ui->lineEdit_input_4,ui->lineEdit_morValue_4,ui->lineEdit_morOffset_4,ui->pushButton_test_four);
}

void RVR_LinearTest::on_pushButton_clear_five_clicked()
{
    clearContext(ui->lineEdit_input_5,ui->lineEdit_morValue_5,ui->lineEdit_morOffset_5,ui->pushButton_test_five);
}

void RVR_LinearTest::on_pushButton_clear_six_clicked()
{
    clearContext(ui->lineEdit_input_6,ui->lineEdit_morValue_6,ui->lineEdit_morOffset_6,ui->pushButton_test_six);
}

void RVR_LinearTest::on_pushButton_clear_seven_clicked()
{
    clearContext(ui->lineEdit_input_7,ui->lineEdit_morValue_7,ui->lineEdit_morOffset_7,ui->pushButton_test_seven);
}

void RVR_LinearTest::on_pushButton_clear_eight_clicked()
{
    clearContext(ui->lineEdit_input_8,ui->lineEdit_morValue_8,ui->lineEdit_morOffset_8,ui->pushButton_test_eigth);
}
