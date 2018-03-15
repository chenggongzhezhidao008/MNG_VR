#ifndef RVR_CONFIGOBJECT_H
#define RVR_CONFIGOBJECT_H

#include <QObject>
#include <QApplication>
#include <QDir>
#include <QMap>
#include <QDebug>
#include <QSettings>
#include <QFileSystemWatcher>
#include <QStringList>

class RVR_Configobject : public QObject
{
    Q_OBJECT
public:
    explicit RVR_Configobject(QObject *parent = 0);
    void initconfig();

public slots:
    QMap<QString,QString> getConfigData(QString file = "");
    QMap<QString,QStringList> tablesInfo();
    QString getBaseLineLength();
    QString getWindRainCover();

signals:

public slots:
    void updateCurrentCommit(QMap<QString,QString> map);

private:
    QFileSystemWatcher *watcher;
    QSettings *rvrConfig,*databaseConfig;
    QString ExeRoot;
    QString configFilePath;
    void initINIFile(QSettings *&seting,QString pathstr);

};

#endif // RVR_CONFIGOBJECT_H
