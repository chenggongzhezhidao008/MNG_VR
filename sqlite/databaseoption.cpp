#include "databaseoption.h"

DataBaseOption::DataBaseOption(QObject *parent) :
    QObject(parent)
{
    RVR_database_sqllite::instance()->initDatabase();
}

bool DataBaseOption::dataBaseExist()
{
    QFile dbFile;
    if(dbFile.exists("vrmngdatabase.db")){
        return true;
    }
    else {
        return false;
    }
}

void DataBaseOption::initDatabase()
{
     RVR_database_sqllite::instance()->initDatabase();
}

void DataBaseOption::createTable(QString tableName, QString createSqlStr)
{
    if(tableName.trimmed() == ""){return ;}
//    qDebug()<<"tableName 2019:"<<tableName<<"columns names:"<<createSqlStr;
    if((RVR_database_sqllite::instance()->sqlite).open()){
        QSqlQuery query(RVR_database_sqllite::instance()->sqlite);
        bool flag = query.exec(QString("create table %1(%2)").arg(tableName).arg(createSqlStr));
        if(flag){
            qDebug()<<"create table succee.";
        }
        else{
            qDebug()<<"create table faild.";
        }
        RVR_database_sqllite::instance()->sqlite.close();
    }
    return ;
}

void DataBaseOption::insertData(QString tableName, QString dataStr)
{
    if(RVR_database_sqllite::instance()->sqlite.open()){
        QSqlQuery query(RVR_database_sqllite::instance()->sqlite);
        bool flag = query.exec(QString("insert into %1 values(%2)").arg(tableName).arg(dataStr));
        if(flag) qDebug()<<"data insert into succeed!";
        else {
            qDebug()<<"insert into faild!";
        }
        RVR_database_sqllite::instance()->sqlite.close();
    }
    return ;
}

QList<lineData> DataBaseOption::selectData(QString tableName,QStringList columns)
{
    QList<lineData> list;
    lineData mapRecord;
    if(RVR_database_sqllite::instance()->sqlite.open()){
        int columnsLength = columns.length();
        QSqlQuery query(RVR_database_sqllite::instance()->sqlite);
        QString sqlstr = "select ";
        for(int i = 0; i < columnsLength; i++){
            if(i == 0){
                sqlstr = sqlstr + QString(" %1 ").arg(columns.value(i));
            }
            else{
                sqlstr = sqlstr + QString(",%1 ").arg(columns.value(i));
            }
        }
        sqlstr = sqlstr + QString(" from %1").arg(tableName);
        qDebug() << "sql str:" << sqlstr;
        bool flag = query.exec( sqlstr);
        if(flag) {
            while(query.next()){
                for(int j = 0; j < columnsLength;j++){
                    mapRecord[columns.value(j)] = query.value(columns.value(j));
                }
                list.push_back(mapRecord);
            }
        }
        RVR_database_sqllite::instance()->sqlite.close();
    }
    return list;
}

