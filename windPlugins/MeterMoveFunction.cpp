#include "windmeter.h"

void WindMeter::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton){//判断鼠标事件的按钮名称
        point = e->globalPos() - this->pos();//计算全局做表与局部坐标差向量
        mousePressed = true;
    }
    e->accept();//接收事件
}

void WindMeter::mouseMoveEvent(QMouseEvent *e)
{
    QPoint p;
    if(e->buttons() == Qt::LeftButton && this->mousePressed){//判断鼠标事件的所有按钮被按下状态的按钮
        p = e->globalPos() - this->point;
//        this->move(p);//以界面左上角坐标为基点移动Awos界面
    }
//    qDebug()<<"ssdddd"<<p;
    e->accept();
}

void WindMeter::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton){//判断鼠标事件的按钮名称
        this->mousePressed = false;
    }
    e->accept();
}
