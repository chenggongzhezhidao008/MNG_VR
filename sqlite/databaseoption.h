#ifndef DATABASEOPTION_H
#define DATABASEOPTION_H

#include <QObject>
#include "sqlite/rvr_database_sqllite.h"
#include <QFile>
#include <QSqlQuery>

#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QMap>
#include <QList>
#include <QVariant>

typedef QMap<QString,QVariant> lineData;
class DataBaseOption : public QObject
{
    Q_OBJECT
public:
    explicit DataBaseOption(QObject *parent = 0);
    bool dataBaseExist();
    void initDatabase();
    void createTable(QString tableName,QString createSqlStr);
    void insertData(QString tableName,QString dataStr);
    QList<lineData> selectData(QString tableName,QStringList columns = QStringList());

signals:

public slots:

};

#endif // DATABASEOPTION_H
