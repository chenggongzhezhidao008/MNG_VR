#ifndef RVR_DEFAULTSET_H
#define RVR_DEFAULTSET_H

#include <QDialog>
#include <QStringList>
#include <QMap>

namespace Ui {
class RVR_DefaultSet;
}

class RVR_DefaultSet : public QDialog
{
    Q_OBJECT

public:
    explicit RVR_DefaultSet(QWidget *parent = 0);
    ~RVR_DefaultSet();
    void init_UI_data(QStringList portList);
    void setCurrentData();
    void select_from(int fId);

public slots:
    void setDefaultdata(QMap<QString,QString> defalut);
    void showOptionMessage(QByteArray softVersion,QMap<QString,QString> map);
    void setBaseLine(QString lengthStr);
    void setWindRainCover(QString lengthStr);

private:
    void init_ui();
    int  fromId;

signals:
    void default_set_option(QString option,QMap<QString,QString>map);
    void current_commit_info(QMap<QString,QString> map);
    void baseSignal(QString baseline);
    void rainWindSignal(QString windRain);

private slots:

    void on_pushButton_commit_set_clicked();

    void on_pushButton_recover_clicked();

    void on_pushButton_sever_set_clicked();

    void on_pushButton_base_WinRai_clicked();

    void on_pushButton_defalut_set_clicked();

    void on_pushButton_enable_clicked();

    void on_pushButton_waring_clicked();

    void on_pushButton_Threshold_clicked();

    void on_pushButton_send_set_clicked();

    void on_pushButton_2_clicked();

    void on_checkBox_RVR_clicked();

    void on_checkBox_hinderLight_clicked();

    void on_checkBox_reciLower_clicked();

    void on_checkBox_sendLower_clicked();

    void on_radioButton_auto_clicked();

    void on_radioButton_loop_clicked();

    void on_pushButton_Threshold_set_clicked();

    void on_pushButton_RVR_Calc_confirm_set_clicked();

    void on_pushButton_sender_confirm_clicked();

    void on_pushButton_back_clicked();

private:
    QStringList comboxList;
    QMap<QString,QString> defalutMap;

private:
    Ui::RVR_DefaultSet *ui;

};

#endif // RVR_DEFAULTSET_H
