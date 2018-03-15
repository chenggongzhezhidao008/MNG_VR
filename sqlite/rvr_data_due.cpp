#include "rvr_data_due.h"

RVR_Data_Due::RVR_Data_Due(QObject *parent) :
    QObject(parent)
{
    initDataDue();
}

//配置数据库表格
bool RVR_Data_Due::configDatabaseTable(QString tableName,QStringList columnNames)
{
   if(!(option->dataBaseExist())){
       option->initDatabase();
       return false;
   }
   QString fieldStr = columnNames.value(0);
   for(int i = 1; i < columnNames.length();i++){
       fieldStr = fieldStr + ","+columnNames.value(i);
   }
   option->createTable(tableName,fieldStr);
   return true;//2017.3.1
}

//添加数据
void RVR_Data_Due::addData(QString tableName, QVariantList datalist)
{
    if(!(option->dataBaseExist())){
        option->initDatabase();
    }

//    if(!tableIsExist(tableName)){//插入数据时表不存在
//       在数据库中配置所有表。 return;
//    }

    QString dataStr,sub;
    for(int i = 0; i < datalist.length();i++){
        if(QMetaType::QString == ((datalist.value(i)).type())){
            sub = datalist.at(i).toString();
            sub = "'" + sub + "'";
//            qDebug()<<"str"<<sub;
        }
        else{
            sub = datalist.value(i).toString();
//            qDebug()<<"str"<<sub;
        }
        if(i == 0) dataStr = sub;
        else{
            dataStr = dataStr + " , "+ sub;
        }
    }
//    qDebug()<<"ooooo table name:"<<tableName<<"table field str"<<dataStr;
    option->insertData(tableName,dataStr);
}

//查询数据库表格数据
QList<lineData> RVR_Data_Due::getData(QString tableName)
{
    qDebug()<<"3";
    QList<lineData> list;
    if(!(option->dataBaseExist())){
       return list;
    }
    //    if(!tableIsExist(tableName)){//读取数据时表不存在
    //      return QList<lineData>;
    //    }
    QStringList columnNameStr /* = getColumnsNmae(tableName)*/;
    columnNameStr<<"datetime"<<"ad"<<"mor"<<"sendtemp"<<"sendhum"<<"recitemp"<<"recihum";//
    QList<lineData> tableList = option->selectData(tableName,columnNameStr);

//    for(int i = 0; i < tableList.length();i++){
//        qDebug()<<"data ID:"<<QString::number(i,10)<<"table data:"<< tableList.value(i);
//    }

    return tableList;
}

void RVR_Data_Due::initDataDue()
{
     option = new DataBaseOption();
}


