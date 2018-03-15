#ifndef RVR_ALIGNMENT_H
#define RVR_ALIGNMENT_H

#include <QDialog>
#include <QMap>
#include <QDebug>

namespace Ui {
class RVR_Alignment;
}

class RVR_Alignment : public QDialog
{
    Q_OBJECT

public:
    explicit RVR_Alignment(QWidget *parent = 0);
    ~RVR_Alignment();
private:
    bool send_initFlage;
    bool reci_initFlage;
    void ini_UI();
    void messageShow(const QString mess);

public slots:
    void update_data(QByteArray softinfo,QMap<QString,QString> dataMap);
    void waring_signal(QByteArray softinfo,QMap<QString,QString> dataMap);
    void show_groyXYZZeroValue(QByteArray softinfo,QMap<QString,QString> dataMap);

private slots:
    void on_pushButton_init_sen_clicked();
    void on_pushButton_init_rec_clicked();

    void on_pushButton_groy_setZero_clicked();

signals:
    void groyOption(QString option,QMap<QString,QString> data);

//protected:
//    bool eventFilter(QObject *obj, QEvent *event);
private:
    Ui::RVR_Alignment *ui;
    QString sender_X,sender_Y,sender_Z;
    QString reciver_X,reciver_Y,reciver_Z;
};

#endif // RVR_ALIGNMENT_H
