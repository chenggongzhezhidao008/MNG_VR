#ifndef RVR_CALIBRATION_H
#define RVR_CALIBRATION_H

#include <QDialog>
#include <QMap>

namespace Ui {
class RVR_Calibration;
}

class RVR_Calibration : public QDialog
{
    Q_OBJECT

public:
    explicit RVR_Calibration(QWidget *parent = 0);
    ~RVR_Calibration();
public slots:
    void cal_fact(QByteArray soft, QMap<QString, QString> dataMap);
    void fullScaaleValueSlot(QByteArray soft, QMap<QString, QString> dataMap);
    void calibrationOffsetValue(QByteArray soft, QMap<QString, QString> dataMap);
private slots:
    void on_pushButton_Full_calibraion_clicked();

    void on_pushButton_offset_clicked();
    void on_pushButton_7_clicked();

signals:
    void calibrationOption(QString optionstr,QMap<QString, QString> data);
private:
    Ui::RVR_Calibration *ui;
    void initUi();
};

#endif // RVR_CALIBRATION_H
