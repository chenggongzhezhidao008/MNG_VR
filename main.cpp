#include "rvr_manager.h"
#include <QApplication>
#include "rvr_startui.h"
#include <QDebug>
#include <QObject>
#include <QByteArray>
#include <QStyleFactory>
#include <QDebug>
#include "managerHead.h"

//cpluscpulsplug

static void SetStyle(QApplication *app,const QString &styleName)//加载样式文件
{
    QFile file(QString(":/image/%1.css").arg(styleName));
    file.open(QFile::ReadOnly);
    QString qss = QLatin1String(file.readAll());
    app->setStyleSheet(qss);
    app->setPalette(QPalette(QColor("#F0F0F0")));
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationVersion("1.0.0");
    QApplication::setApplicationName("RVR maintain");
    SetStyle(&a,"black");
    QStringList keys = QStyleFactory::keys();
    for(int i = 0;i < keys.length();i++){
        if(keys.at(i) == "Fusion"){
            QApplication::setStyle(QStyleFactory::create("Fusion"));
        }
    }
    manager = new RVR_Manager();
    manager->show();
    return a.exec();
}
