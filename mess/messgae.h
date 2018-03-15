#ifndef MESSGAE_H
#define MESSGAE_H

#include <QDialog>
#include <QPoint>
#include <QMouseEvent>
#include "comm.h"

namespace Ui {
class Messgae;
}

class Messgae : public QDialog
{
    Q_OBJECT

public:
    explicit Messgae(QWidget *parent = 0);
    ~Messgae();
    void setMessage(QString &message,int type);
    void setSendFlage(bool ok);
signals:

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private slots:
    void on_pushButton_ok_clicked();

    void on_pushButton_Cancle_clicked();

private:
    Ui::Messgae *ui;
    bool mousePressed;
    QPoint mousepoint;
    QString messStr;
    bool sendFlage;
};

#endif // MESSGAE_H
