#include "rvr_startui.h"
#include "ui_rvr_startui.h"
#include <QDebug>

#include "mess/RVR_Reminder_Msg.h"

RVR_startUI::RVR_startUI(QStringList comnames,QWidget *parent) :
    QWidget(parent),coms(comnames),
    ui(new Ui::RVR_startUI)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_QuitOnClose,false);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    this->setWindowTitle("RVR通信选择");
    ui->comboBox_coms->addItems(comnames);
    this->setGeometry(10,37,900,600);

}

RVR_startUI::~RVR_startUI()
{
    delete ui;
}

void RVR_startUI::on_pushButtonok_clicked()
{
    str = ui->comboBox_coms->currentText();
    if(str.isEmpty()){
        Reminder_Mseg::showMessageboxInfo("没有通信端口,请接入。");
        return ;
    }
    emit  COM(str);
}

void RVR_startUI::updatecoms(QStringList newComs)
{
    newComs<<"3616"<<"remote";
    if(coms!= newComs){
        coms.clear();
        ui->comboBox_coms->clear();
        ui->comboBox_coms->addItems(newComs);
        coms << newComs;
    }
    qDebug()<<"com"<<coms;
}


void RVR_startUI::okOrNo(bool flage)
{
    if(flage == true)
    {
        this->hide();
    }
    else{
        str = ui->comboBox_coms->currentText();
        Reminder_Mseg::showMessageboxError(QString("%1端口可能被占用\n请检查。").arg(str));
    }
}

void RVR_startUI::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton){
        point = e->globalPos() - this->pos();
        mousePressed = true;
    }
    e->accept();
}

void RVR_startUI::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() == Qt::LeftButton && this->mousePressed){
        this->move(e->globalPos() - this->point);
        emit moveSignal(e->globalPos() - this->point);
    }
    e->accept();
}

void RVR_startUI::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton){
        this->mousePressed = false;
    }
    e->accept();
}

void RVR_startUI::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
}

