#include "meterplugin.h"
#include "ui_meterplugin.h"

MeterPlugin::MeterPlugin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MeterPlugin)
{
    ui->setupUi(this);
    this->resize(200,200);
}

MeterPlugin::~MeterPlugin()
{
    delete ui;
}

void MeterPlugin::paintEvent(QPaintEvent *)
{
     QPainter *painter = new QPainter(this);
     static const int triangle[3][2] = {
         {70,0},{ 89,-10}, {89,10},
     };
     int side = qMin(width(),height());
     painter->translate(width()/2,height()/2);
     painter->scale(side / 400.0,side / 400.0);
     painter->setRenderHint(QPainter::Antialiasing);
     painter->save();
     QPen thinPen(palette().background(),0.1);
     painter->setPen(thinPen);
     QPainterPath path,path2;
     QRectF rect(-100,-100,200,200);
     path.arcTo(rect,0,10);
     QRectF rect2(-90,-90,180,180);
     path2.arcTo(rect2,0,10);

     for (int i= 0;i < 18;i++){
         painter->rotate(20);
         if(i>4 && i<9){
             if(i*20 > 100 && i*20 <140){
                 painter->setBrush(Qt::black);
             }
             else{
             painter->setBrush(Qt::blue);
             }
         }
         else
         {
             painter->setBrush(Qt::green);
         }
         painter->drawPath(path);
         painter->setBrush(palette().background());
         painter->drawPath(path2);
     }

     QPoint center(0,0);
     painter->setBrush(palette().background());
     painter->drawEllipse(center,90,90);
     painter->restore();
     painter->rotate(135);
     painter->setBrush(Qt::black);
     painter->drawPolygon(QPolygon(3, &triangle[0][0]));
}
