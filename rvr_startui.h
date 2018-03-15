#ifndef RVR_STARTUI_H
#define RVR_STARTUI_H

#include <QWidget>
#include <QStringList>

#include <QMainWindow>
#include <QPoint>
#include <QEvent>
#include <QPainter>
#include <QMouseEvent>


namespace Ui {
class RVR_startUI;
}

class RVR_startUI : public QWidget
{
    Q_OBJECT

public:
    explicit RVR_startUI(QStringList comnames,QWidget *parent = 0);
    ~RVR_startUI();

signals:
    void COM(QString comName);
    void moveSignal(QPoint point);
private slots:
    void on_pushButtonok_clicked();

public slots:
    void updatecoms(QStringList newComs);
    void okOrNo(bool flage);

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *event);
private:
    QTimer *loop;
    QString str;
    QStringList coms;
    Ui::RVR_startUI *ui;
    QPoint point;
    bool mousePressed;
};

#endif // RVR_STARTUI_H
