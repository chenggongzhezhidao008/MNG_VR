#ifndef RVR_LINEARTEST_H
#define RVR_LINEARTEST_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class RVR_LinearTest;
}

class RVR_LinearTest : public QDialog
{
    Q_OBJECT

public:
    explicit RVR_LinearTest(QWidget *parent = 0);
    ~RVR_LinearTest();
signals:
    void lineTest(QString option, QMap<QString,QString> data);

public slots:
    void setTValue(QByteArray softInfo,QMap<QString,QString>dataMap);
    void writeTValue(QLineEdit *TValueLineEdit,QString TValue,
                     QLineEdit *offsetLineEdit,QString offSetValue);
    void setBaseline(QString lengthStr);
    void setWindRainCover(QString lengthStr);

private slots:
    void on_pushButton_test_one_clicked();

    void on_pushButton_test_two_clicked();

    void on_pushButton_test_three_clicked();

    void on_pushButton_test_four_clicked();

    void on_pushButton_test_five_clicked();

    void on_pushButton_test_six_clicked();

    void on_pushButton_test_seven_clicked();

    void on_pushButton_test_eigth_clicked();

    void on_pushButton_clear_one_clicked();

    void on_pushButton_clear_two_clicked();

    void on_pushButton_clear_three_clicked();

    void on_pushButton_clear_four_clicked();

    void on_pushButton_clear_five_clicked();

    void on_pushButton_clear_six_clicked();

    void on_pushButton_clear_seven_clicked();

    void on_pushButton_clear_eight_clicked();


private:
    Ui::RVR_LinearTest *ui;
    QString baseline;
    QString windraincover;
    QString inputValue;
    int index;
    void sendValue(int i,QLineEdit *edit);
    void enabledButton(int i = 0);
    void clearContext(QLineEdit *editIn,QLineEdit *editout,QLineEdit *editoffset,QPushButton *button);
};

#endif // RVR_LINEARTEST_H
