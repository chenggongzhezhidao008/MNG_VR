#ifndef RVR_VIEW_H
#define RVR_VIEW_H

#include <QDialog>

namespace Ui {
class RVR_View;
}

class RVR_View : public QDialog
{
    Q_OBJECT

public:
    explicit RVR_View(QWidget *parent = 0);
    ~RVR_View();

private:
    Ui::RVR_View *ui;
};

#endif // RVR_VIEW_H
