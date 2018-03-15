#ifndef METERPLUGIN_H
#define METERPLUGIN_H

#include <QWidget>
#include <QPainter>


namespace Ui {
class MeterPlugin;
}

class MeterPlugin : public QWidget
{
    Q_OBJECT

public:
    explicit MeterPlugin(QWidget *parent = 0);
    ~MeterPlugin();

protected:
    void paintEvent(QPaintEvent *);
private:
    Ui::MeterPlugin *ui;
};

#endif // METERPLUGIN_H
