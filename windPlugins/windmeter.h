#ifndef WINDMETER_H
#define WINDMETER_H

#include <Qt>
#include <QPainter>
#include <QWidget>
#include <qmath.h>
#include <QDebug>
#include <QLinearGradient>
#include <QMouseEvent>

#define PI 3.1415926535

class WindMeter : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int windCurrentAngle READ windCurrentAngle WRITE setWindCurrentAngle NOTIFY currentWindAngleChanged)
    Q_PROPERTY(QString windCurrentSpeed READ windCurrentSpeed WRITE setWindCurrentSpeed NOTIFY windCurrentSpeedChanged)
    Q_PROPERTY(int tenWindMaxAngle READ tenWindMaxAngle WRITE setTenWindMaxAngle NOTIFY tenMaxValueChanged)
    Q_PROPERTY(int tenWindMinAngle READ tenWindMinAngle WRITE setTenWindMinAngle NOTIFY tenMinValueChanged)
    Q_PROPERTY(int runUpAngle READ runUpAngle WRITE setRunUpAngle NOTIFY runUpAngleChanged)
    Q_PROPERTY(int twoWindAvAngle READ twoWindAvAngle WRITE setTwoWindAvAngle NOTIFY twoWindAvAngleChanged)
    Q_PROPERTY(bool shieled READ shieled WRITE setShieled)

public:
    explicit WindMeter(QWidget *parent = 0);
    int windCurrentAngle() const { return m_windCurrentAngle;}
    QString windCurrentSpeed() const {return m_windCurrentSpeed;}
    int tenWindMaxAngle() const { return m_tenWindMaxAngle;}
    int tenWindMinAngle() const { return m_tenWindMinAngle;}
    int runUpAngle() const { return m_runUpAngle;}
    int twoWindAvAngle() const {return m_twoAvAngle;}
    bool shieled() const {return m_shield;}

signals:
    void currentWindAngleChanged();
    void windCurrentSpeedChanged();
    void tenMaxValueChanged();
    void tenMinValueChanged();
    void runUpAngleChanged();
    void twoWindAvAngleChanged();

public slots:
    void setWindCurrentAngle(int angle);
    void setWindCurrentSpeed(QString speed);
    void setTenWindMaxAngle(int angle);
    void setTenWindMinAngle(int angle);
    void setRunUpAngle(int angle);
    void setTwoWindAvAngle(int angle);
    void setShieled(bool shiele);

private slots:
    void updatePlugin();

private:
    int y;
    bool m_shield;

    QPoint point;//保存鼠标按下的点全局位置坐标与局部坐标的差向量
    bool mousePressed;//保存鼠标按下状态

protected:
    int m_windCurrentAngle;
    QString m_windCurrentSpeed;
    int m_tenWindMaxAngle;
    int m_tenWindMinAngle;
    int m_twoAvAngle;
    int m_runUpAngle;
    void paintEvent(QPaintEvent *event);
    void drawAngleScale(QPainter *&painter);
    void drawCurrentWindAngle(QPainter *&painter);
    void drawAngleScaleText(QPainter *&painter);
    void drawInsideEllipse(QPainter *&painter);
    void drawRunUpRect(QPainter *&painter);
    void drawUnitLabelArea(QPainter *&painter);
    void drawWindAngle(QPainter *&painter);
    void drawWindSpeed(QPainter *&painter);
    void drawWindPointer(QPainter *&painter);
    void drawShield(QPainter *&painter);

    //以下三个事件使风表盘界面可移动
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
};

#endif // WINDMETER_H
