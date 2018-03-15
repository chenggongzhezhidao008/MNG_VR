#ifndef RVR_CURRENTCONFIG_H
#define RVR_CURRENTCONFIG_H

#include <QDialog>
#include <QMap>
namespace Ui {
class RVR_Currentconfig;
}

class RVR_Currentconfig : public QDialog
{
    Q_OBJECT

public:
    explicit RVR_Currentconfig(QWidget *parent = 0);
    ~RVR_Currentconfig();
    void setSeialPort(QString port);
public slots:
    void getcurrentInfo(QMap<QString,QString> cur_serial);
private:
    QString currentPort;
    Ui::RVR_Currentconfig *ui;
};

#endif // RVR_CURRENTCONFIG_H
