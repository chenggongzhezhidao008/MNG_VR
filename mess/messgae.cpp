#include "messgae.h"
#include "ui_messgae.h"
#include "mess/messagehelper.h"
#include "managerHead.h"

Messgae::Messgae(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Messgae)
{
    ui->setupUi(this);
    mousePressed = false;
    sendFlage = false;
    messStr = "\0";
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_DeleteOnClose);
    MessageHelper::instance()->setLable(ui->label_ico,QChar(0xf015),10);
    MessageHelper::instance()->setButton(ui->pushButton_menu_closed,QChar(0xf00d),16);
    connect(ui->pushButton_menu_closed,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->pushButton_Cancle,SIGNAL(clicked()),this,SLOT(close()));
}

Messgae::~Messgae()
{
    delete ui;
}

void Messgae::setMessage(QString &message, int type)
{
    if(type == 1){
        ui->label_ico_main->setStyleSheet("border-image: url(:/image/info.png)");
        ui->pushButton_Cancle->setVisible(false);
        ui->label_title->setText("提示");
    }else if(type == 2){
        ui->label_ico_main->setStyleSheet("border-image: url(:/image/question.png)");
        ui->label_title->setText("询问");
    }else if(type == 3){
        ui->label_ico_main->setStyleSheet("border-image: url(://image/error.png)");
        ui->pushButton_Cancle->setVisible(false);
        ui->label_title->setText("错误");
    }
    messStr = message;
    ui->label_content->setText(message);

}

void Messgae::setSendFlage(bool ok)
{
    this->sendFlage = ok;
}

void Messgae::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton){
        mousePressed = true;
        mousepoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void Messgae::mouseMoveEvent(QMouseEvent *e)
{
    if(mousePressed &&(e->buttons() && Qt::LeftButton)){
        this->move(e->globalPos() - this->mousepoint);
        e->accept();
    }
}

void Messgae::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}

void Messgae::on_pushButton_ok_clicked()
{
    if(sendFlage){
        QMap<QString,QString> data;
        if(messStr == "RVR软件复位"){
            data["reset_value"] = "reset";
            dataWrite->writeData("reset_RVR_soft",data);
        }
        else if(messStr == "确定要退出VRMNG吗？"){
            manager->quit_app(true);
        }
        else{
            ;
        }
    }
    messStr = "\0";
    done(1);
    this->close();
    return ;
}

void Messgae::on_pushButton_Cancle_clicked()
{
    if(sendFlage){
       if(messStr == "确定要退出VRMNG吗？"){
            manager->quit_app(false);
        }
        else{
            ;
        }
    }
    messStr = "\0";
}













