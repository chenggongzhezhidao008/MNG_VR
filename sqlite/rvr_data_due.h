#ifndef RVR_DATA_DUE_H
#define RVR_DATA_DUE_H

#include <QObject>
#include "sqlite/databaseoption.h"
#include <QMap>
#include <QVariant>
#include <QList>

typedef QMap<QString,QVariant> lineData;

class RVR_Data_Due : public QObject
{
    Q_OBJECT

public:
    explicit RVR_Data_Due(QObject *parent = 0);
    bool configDatabaseTable(QString tableName,QStringList columnNames);
    void addData(QString tableName = QString(),QVariantList datalist = QVariantList());
    QList<lineData> getData(QString tableName);

signals:

public slots:

private:
    void initDataDue();
    DataBaseOption *option;
};

#endif // RVR_DATA_DUE_H
