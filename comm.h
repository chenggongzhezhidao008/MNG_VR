#ifndef COMM_H
#define COMM_H

#include <QDebug>
#include <QThread>
#include <QStringList>
#include <QApplication>

//serial objects
#include "serialmodule/serialport.h"
#include "serialmodule/rvr_serialparse.h"
#include "serialmodule/rvr_serialwrite.h"
#include "serialmodule/serialinfo.h"


extern SerialPort *Serial;
extern SerialInfo *ser_info;
extern QStringList nameList;

extern RVR_serialparse *ser_Parse;
extern RVR_serialwrite *ser_Write;

extern QThread *ser_thread;

//ui objects and head file

#include "ui/rvr_alignment.h"
#include "ui/rvr_calibration.h"
#include "ui/rvr_currentstatus.h"
#include "ui/rvr_defaultconfig.h"
#include "ui/rvr_currentconfig.h"
#include "ui/rvr_defaultset.h"
#include "ui/rvr_lineartest.h"
#include "ui/rvr_view.h"
#include <QTimer>



extern RVR_Alignment *alignmentUi;
extern RVR_Calibration *calibrationUi;
extern RVR_CurrentStatus *currentStatusUi;
extern RVR_LinearTest *lineartestUi;
extern RVR_DefaultConfig *defaultConUi;
extern RVR_Currentconfig *currentConUi;
extern RVR_DefaultSet *defaultSetUi;

// config ini file
#include <QMap>
#include "configmodule/rvr_configobject.h"
extern RVR_Configobject *config;


//data parse object and write object
#include "datadue/rvr_dataparse.h"
#include "datadue/rvr_datawrite.h"

extern RVR_DataParse *dataParse;
extern RVR_DataWrite *dataWrite;

// start ui
#include "rvr_startui.h"
extern RVR_startUI *startui;

// log
#include "ui/serial_message.h"
extern Serial_Message *seri_mess;
#include "datadue/rvr_logoutstore.h"
extern RVR_LogOutStore *logInfo;


//zmq commit
#include "zmq/rvr_zmq_worker.h"
extern RVR_Zmq_Worker *zmqworker;

//sqlite database

//#include "sqlite/rvr_database_sqllite.h"

//extern RVR_database_sqllite *sqlite;

// transfer class
#include "distanceTransfer/setupthread.h"
extern SetupThread *remoteTran;

//init sql database
#include "sqlite/rvr_data_due.h"
extern RVR_Data_Due *databseDue;


//RVR 计算参数设置
#include "ui/rvr_calc_values.h"
extern RVR_Calc_values *RVRCalc;
#endif // COMM_H


//消息解释
#include "MessageParse/messageparse.h"
extern MessageParse *messParse;




























