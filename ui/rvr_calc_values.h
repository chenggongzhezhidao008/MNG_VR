#ifndef RVR_CALC_VALUES_H
#define RVR_CALC_VALUES_H

#include <QWidget>
#include <QMap>

namespace Ui {
class RVR_Calc_values;
}

class RVR_Calc_values : public QWidget
{
    Q_OBJECT

public:
    explicit RVR_Calc_values(QWidget *parent = 0);
    ~RVR_Calc_values();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_back_clicked();

signals:
    void calc_Value(QString options,QMap<QString,QString> data);
private:
    Ui::RVR_Calc_values *ui;
    void initUI();
    QString back_light,run_light;
};

#endif // RVR_CALC_VALUES_H
