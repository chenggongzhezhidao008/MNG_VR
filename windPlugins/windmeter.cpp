#include "windmeter.h"
WindMeter::WindMeter(QWidget *parent) :
    QWidget(parent)
{
    m_windCurrentAngle = 100;
    m_windCurrentSpeed = "///";

    m_tenWindMaxAngle = 360;
    m_tenWindMinAngle = 280;

    m_twoAvAngle = 360;
    m_runUpAngle = 60;
    y = 4;
    m_shield = false;

    point = QPoint();
    mousePressed = false;

    connect(this,SIGNAL(currentWindAngleChanged()),this,SLOT(updatePlugin()));
    connect(this,SIGNAL(tenMaxValueChanged()),this,SLOT(updatePlugin()));
    connect(this,SIGNAL(tenMinValueChanged()),this,SLOT(updatePlugin()));
    connect(this,SIGNAL(runUpAngleChanged()),this,SLOT(updatePlugin()));
    connect(this,SIGNAL(windCurrentSpeedChanged()),this,SLOT(updatePlugin()));
    connect(this,SIGNAL(twoWindAvAngleChanged()),this,SLOT(updatePlugin()));
}

void WindMeter::setWindCurrentAngle(int angle)
{
    int temp = this->m_windCurrentAngle;
    this->m_windCurrentAngle = angle;
    if( temp != angle){
        emit currentWindAngleChanged();
    }
}

void WindMeter::setWindCurrentSpeed(QString speed)
{
    QString temp = this->m_windCurrentSpeed;
    this->m_windCurrentSpeed = speed;
    if( temp != speed){
        emit windCurrentSpeedChanged();
    }
}

void WindMeter::setTenWindMaxAngle(int angle)
{
    int temp = this->m_tenWindMaxAngle;
    this->m_tenWindMaxAngle = angle;
    if( temp != angle){
        emit tenMaxValueChanged();
    }
}

void WindMeter::setTenWindMinAngle(int angle)
{
    int temp = this->m_tenWindMinAngle;
    this->m_tenWindMinAngle = angle;
    if( temp != angle){
        emit tenMinValueChanged();
    }
}

void WindMeter::setRunUpAngle(int angle)
{
    int temp = this->m_runUpAngle;
    this->m_runUpAngle = angle;
    if( temp != angle){
        emit runUpAngleChanged();
    }
}

void WindMeter::setTwoWindAvAngle(int angle)
{
    int temp = this->m_twoAvAngle;
    this->m_twoAvAngle = angle;
    if( temp != angle){
        emit twoWindAvAngleChanged();
    }
}

void WindMeter::setShieled(bool shiele)
{
    this->m_shield = shiele;
}

void WindMeter::updatePlugin()
{
    update();
}

void WindMeter::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter *painter = new QPainter(this);
    painter->setRenderHint(QPainter::Antialiasing,true);

    //设置画布的长宽，坐标变换，缩放度，反锯齿
    int side = qMin(width(),height());
    painter->translate(width()/2,height()/2);
    painter->scale(side / 350.0,side / 350.0);
    painter->rotate(-90);

    //画刻度 ok
    drawAngleScale(painter);

    //绘制当前风向刻度
    drawCurrentWindAngle(painter);

    //表盘内园盘 ok
    drawInsideEllipse(painter);

    //跑到图标
    drawRunUpRect(painter);

    //画中心标签区域ok
    drawUnitLabelArea(painter);

    //当前风向ok
    drawWindAngle(painter);

    //当前风速ok
    drawWindSpeed(painter);

    //当前风向指针图标 ok
    drawWindPointer(painter);

    //绘制刻度数据标签
    drawAngleScaleText(painter);

    drawShield(painter);
}
