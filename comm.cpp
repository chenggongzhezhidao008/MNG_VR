#include "comm.h"

//RVRManager serial config info
SerialPort *Serial = NULL;
SerialInfo *ser_info = NULL;
QStringList nameList;

RVR_serialparse *ser_Parse;
RVR_serialwrite *ser_Write;

QThread *ser_thread;


//dtaparse and write
RVR_DataParse *dataParse = NULL;
RVR_DataWrite *dataWrite = NULL;

//RVRManager ui config info
RVR_Alignment *alignmentUi = NULL;
RVR_Calibration *calibrationUi = NULL;
RVR_CurrentStatus *currentStatusUi = NULL;
RVR_LinearTest *lineartestUi = NULL;
RVR_DefaultConfig *defaultConUi = NULL;
RVR_Currentconfig *currentConUi = NULL;
RVR_DefaultSet *defaultSetUi = NULL;

//config file
RVR_Configobject *config = NULL;

//start ui
RVR_startUI *startui = NULL;

//log

Serial_Message *seri_mess = NULL;
RVR_LogOutStore *logInfo = NULL;

//zmq commit
RVR_Zmq_Worker *zmqworker = NULL;


//sqlite database
//RVR_database_sqllite *sqlite = NULL;

// transfer class
SetupThread *remoteTran = NULL;

//init sql database
RVR_Data_Due *databseDue = NULL;

//init rvr calc
RVR_Calc_values *RVRCalc = NULL;


//消息解释
MessageParse *messParse  = NULL;








