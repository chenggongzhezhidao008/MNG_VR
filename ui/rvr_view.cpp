#include "rvr_view.h"
#include "ui_rvr_view.h"

RVR_View::RVR_View(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RVR_View)
{
    ui->setupUi(this);
}

RVR_View::~RVR_View()
{
    delete ui;
}
