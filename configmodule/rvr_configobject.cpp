#include "rvr_configobject.h"

RVR_Configobject::RVR_Configobject(QObject *parent) :
    QObject(parent)
{
     ExeRoot = ".";
     configFilePath = ".";
     initconfig();
     initINIFile(rvrConfig,"rvr.ini");
     initINIFile(databaseConfig,"database.ini");
     watcher = new QFileSystemWatcher();
     watcher->addPath(configFilePath);
     connect(watcher,SIGNAL(fileChanged(QString)),this,SLOT(getConfigData(QString)));
}

void RVR_Configobject::initconfig()
{
    ExeRoot = QApplication::applicationDirPath();
    QDir::setCurrent(ExeRoot);
    configFilePath = ExeRoot+"/seting/";
}

QMap<QString,QString> RVR_Configobject::getConfigData(QString )
{
     QMap<QString,QString> serial;
     serial["port"] = rvrConfig->value("serialport/port").toString();
     serial["baud"] = rvrConfig->value("serialport/baud").toString();
     serial["datas"] = rvrConfig->value("serialport/data").toString();
     serial["stop"] = rvrConfig->value("serialport/stop").toString();
     serial["parity"] = rvrConfig->value("serialport/parity").toString();
     return serial;
}

QMap<QString, QStringList> RVR_Configobject::tablesInfo()
{
    QString tableName;QStringList fieldStr;
    QMap<QString,QStringList> tableinfo;
    int leng = (databaseConfig->value("Tables/num")).toInt();
    for(int i = 1;i <= leng;i++){
       tableName = (databaseConfig->value(QString("Tables/table%1").arg(i))).toString();
       fieldStr = ((databaseConfig->value(QString("Tables/fieldStr%1").arg(i))).toString()).split(":");
       tableinfo[tableName] = fieldStr;
    }
//    qDebug()<<"tableinfo xxxxxx:"<<tableinfo;
    return tableinfo;
}

//get baseline length
QString RVR_Configobject::getBaseLineLength()
{
     QString baseline = rvrConfig->value("baseline/length").toString();
     return baseline;
}
//get wind rain cover length
QString RVR_Configobject::getWindRainCover()
{
    QString windRain = rvrConfig->value("windraincover/length").toString();
    return windRain;
}

void RVR_Configobject::updateCurrentCommit(QMap<QString, QString> map)
{
    qDebug()<<"current Commit:"<<map;
}

void RVR_Configobject::initINIFile(QSettings *&seting,QString pathstr)
{
    seting = new QSettings((configFilePath + pathstr), QSettings::IniFormat);
    seting->setIniCodec("UTF-8");
}








