#ifndef RVR_DATABASE_SQLLITE_H
#define RVR_DATABASE_SQLLITE_H

#include <QObject>
#include <QMutex>
#include <QMutexLocker>
#include <QDebug>

#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QApplication>
#include <QStringList>

class RVR_database_sqllite : public QObject
{
    Q_OBJECT
public:
    explicit RVR_database_sqllite(QObject *parent = 0);
    static RVR_database_sqllite *instance(){
        static QMutex mutex;
        if(!RVR_sql){
            QMutexLocker lock(&mutex);
            if(!RVR_sql){
                RVR_sql = new RVR_database_sqllite();
            }
        }
        return RVR_sql;
    }
    QSqlDatabase getConnection();
    void initDatabase();
signals:

private:
    static RVR_database_sqllite *RVR_sql;
    bool initFlag;
public:
    QSqlDatabase sqlite;
};

#endif // RVR_DATABASE_SQLLITE_H
