#ifndef RVR_DEFAULTCONFIG_H
#define RVR_DEFAULTCONFIG_H

#include <QDialog>
#include <QMap>

namespace Ui {
class RVR_DefaultConfig;
}

class RVR_DefaultConfig : public QDialog
{
    Q_OBJECT

public:
    explicit RVR_DefaultConfig(QWidget *parent = 0);
    ~RVR_DefaultConfig();

public slots:
    void setDefaultInfo(QMap<QString,QString> cur_serial);

private:
    Ui::RVR_DefaultConfig *ui;
};

#endif // RVR_DEFAULTCONFIG_H
