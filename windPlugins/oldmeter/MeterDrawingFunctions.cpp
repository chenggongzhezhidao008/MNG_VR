#include "windPlugins/windmeter.h"

//绘制刻度条
void WindMeter::drawAngleScale(QPainter *&painter)
{
    painter->save();
    QPen thinPen(palette().background(),0.1);
    painter->setPen(thinPen);
    QPainterPath path;
    QRectF rect(-150,-150,300,300);
    path.arcTo(rect,1,8);
    painter->rotate(-5);

    for (int i = 0;i < 37;i++)
    {
        painter->rotate(10);
        if(i == 0){
            continue;
        }
        if(i >= (m_tenWindMinAngle / 10) && i<=(m_tenWindMaxAngle / 10)){
            painter->setBrush(Qt::blue);
        }
        else{
            painter->setBrush(Qt::gray);
        }
        painter->drawPath(path);
    }
    painter->restore();
}
//绘制当前风向刻度
void WindMeter::drawCurrentWindAngle(QPainter *&painter)
{
    painter->save();
    //画笔
    QPen thinPen(palette().background(),0.1);
    painter->setPen(thinPen);
    //路径编辑
    QPainterPath path;
    QRectF rect(-150,-150,300,300);
    path.arcTo(rect,1,8);
    //旋转绘画
    painter->rotate(-5);
    if((m_windCurrentAngle /10) == 36){
        painter->rotate(10);
        painter->setBrush(Qt::black);
        painter->drawPath(path);
        painter->restore();
        return ;
    }
    for (int i = 0;i < 37;i++)
    {
        if(i == (m_windCurrentAngle / 10) + 1 ){
            painter->setBrush(Qt::black);
            painter->drawPath(path);
        }
        else{
            ;
        }
        painter->rotate(10);
    }
    painter->restore();
}

//绘制刻度数据
void WindMeter::drawAngleScaleText(QPainter *&painter)
{
    painter->rotate(-90);
    painter->setPen(/*Qt::black*/"#545454");
    QFont font;
    font.setBold(true);
    font.setPointSize(12);
    painter->setFont(font);
    double deltaRad = 10*(PI/180);
    double sina,cosa;
    for ( int i= 0; i<= 36; i++ )
    {
        painter->save();
        if(i % 3 != 0 || i == 0) continue;
        sina=sin((double)(PI/2+i*deltaRad));
        cosa=cos((double)(PI/2+i*deltaRad));
        QString str = QString::number(i,10);
        if(i < 11) str = "0"+str;
        QFontMetricsF fm( this->font());
        double w = fm.size(Qt::TextSingleLine,str).width();
        double h = fm.size(Qt::TextSingleLine,str).height();
        int x = (int)(160*cosa);
        int y = (int)(160*sina);
        painter->translate(x,y);
        painter->rotate(180);
        painter->drawText(-(h/2)-3,(w/3),str);
        painter->restore();
    }
}

void WindMeter::drawInsideEllipse(QPainter *&painter)
{
    painter->save();
    painter->setPen((palette().background()).color());
    QPoint center(0,0);
    painter->setBrush(Qt::white);
    painter->drawEllipse(center,140,140);
    painter->restore();
}

//跑道角度方向
void WindMeter::drawRunUpRect(QPainter *&painter)
{
    painter->save();
    painter->rotate(m_runUpAngle);
    painter->setPen(Qt::gray);
    painter->setBrush(Qt::gray);
    QRect runUplabel(-110,-12,220,24);
    painter->drawRect(runUplabel);
    painter->setPen(Qt::gray);
    painter->setBrush(Qt::white);
    for(int i = 0;i < 5;i++){
        QRect touchSpotRect1(72,(-12 + i*5),35,3);
        painter->drawRect(touchSpotRect1);
    }
    painter->restore();
}

void WindMeter::drawUnitLabelArea(QPainter *&painter)
{
    painter->save();
    painter->rotate(90);
    QPen pen;
    pen.setColor((palette().background()).color());
    pen.setWidth(1);
    pen.setColor(Qt::gray);
    painter->setPen(pen);
    painter->setBrush(Qt::white);
    QRect rectlabel(-40,-30,80,60);
    painter->drawRect(rectlabel);
    painter->restore();
}

//当前风向，风速中心标签
void WindMeter::drawWindAngle(QPainter *&painter)
{
    painter->save();
    painter->rotate(90);
    painter->setPen(Qt::black);
    QFont fontangle = painter->font();
    fontangle.setBold(true);
    painter->setFont(fontangle);
    QRectF angleUnit = QRectF(20,-26,10,30);
    QString angleUnitstr = "o";
    painter->drawText(angleUnit,Qt::AlignVCenter|Qt::AlignLeft, angleUnitstr);

    int pixangle = fontangle.pointSize();
    pixangle += 7;
    fontangle.setPointSize(pixangle);
    painter->setFont(fontangle);

    QRectF angleRect= QRectF(-30,-26,60,30);
    QString anglestr = QString::number(m_windCurrentAngle,10);
    painter->drawText(angleRect,Qt::AlignCenter, anglestr);
    painter->restore();
}

void WindMeter::drawWindSpeed(QPainter *&painter)
{
    painter->save();
    painter->rotate(90);
    painter->setPen(Qt::black);
    QFont fontSpeed = painter->font();
    fontSpeed.setBold(true);
    painter->setFont(fontSpeed);
    QRectF SpeedUnit = QRectF(20,-4,10,30);
    QString SpeedUnitstr = "kt";
    painter->drawText(SpeedUnit,Qt::AlignCenter, SpeedUnitstr);

    int pixSpeed = fontSpeed.pointSize();
    pixSpeed += 7;
    fontSpeed.setPointSize(pixSpeed);
    painter->setFont(fontSpeed);
    QRectF SpeedRect= QRectF(-26,-4,60,28);
    QString Speedstr = QString::number(m_windCurrentSpeed,10)+" ";
    painter->drawText(SpeedRect,Qt::AlignCenter, Speedstr);
    painter->restore();
}

//当前风向标
void WindMeter::drawWindPointer(QPainter *&painter)
{
    painter->save();
    static const int triangle[3][2] = {
        {110,0},{ 130,-10}, {130,10}
    };
    qDebug()<<"current angle:"<<m_windCurrentAngle;
    painter->rotate(m_windCurrentAngle);
    painter->setBrush(Qt::black);
    painter->drawPolygon(QPolygon(3, &triangle[0][0]));
    painter->restore();
}
