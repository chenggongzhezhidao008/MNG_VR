#ifndef WINDMETER_H
#define WINDMETER_H

#include <Qt>
#include <QPainter>
#include <QWidget>
#include <qmath.h>
#include <QDebug>

#define PI 3.1415926535


class WindMeter : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int windCurrentAngle READ windCurrentAngle WRITE setWindCurrentAngle NOTIFY currentWindAngleChanged)
    Q_PROPERTY(int windCurrentSpeed READ windCurrentSpeed WRITE setWindCurrentSpeed NOTIFY windCurrentSpeedChanged)
    Q_PROPERTY(int tenWindMaxAngle READ tenWindMaxAngle WRITE setTenWindMaxAngle NOTIFY tenMaxValueChanged)
    Q_PROPERTY(int tenWindMinAngle READ tenWindMinAngle WRITE setTenWindMinAngle NOTIFY tenMinValueChanged)
    Q_PROPERTY(int runUpAngle READ runUpAngle WRITE setRunUpAngle NOTIFY runUpAngleChanged)

public:
    explicit WindMeter(QWidget *parent = 0);
    int windCurrentAngle() const { return m_windCurrentAngle;}
    int windCurrentSpeed() const {return m_windCurrentSpeed;}
    int tenWindMaxAngle() const { return m_tenWindMaxAngle;}
    int tenWindMinAngle() const { return m_tenWindMinAngle;}
    int runUpAngle() const { return m_runUpAngle;}

signals:
    void currentWindAngleChanged();
    void windCurrentSpeedChanged();
    void tenMaxValueChanged();
    void tenMinValueChanged();
    void runUpAngleChanged();
public slots:
    void setWindCurrentAngle(int angle);
    void setWindCurrentSpeed(int speed);
    void setTenWindMaxAngle(int angle);
    void setTenWindMinAngle(int angle);
    void setRunUpAngle(int angle);
private slots:
    void updatePlugin();
private:
    int y;
protected:
    int m_windCurrentAngle;
    int m_windCurrentSpeed;
    int m_tenWindMaxAngle;
    int m_tenWindMinAngle;
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
};

#endif // WINDMETER_H
