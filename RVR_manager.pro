#-------------------------------------------------
#
# Project created by QtCreator 2016-10-28T09:20:20
#
#-------------------------------------------------

QT       += core gui quick qml serialport sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RVR_manager
TEMPLATE = app

include(qtxlsx.pri)

SOURCES += \
    main.cpp\
    comm.cpp \
    serialmodule/rvr_serialparse.cpp \
    serialmodule/rvr_serialwrite.cpp \
    configmodule/rvr_configobject.cpp \
    serialmodule/serialport.cpp \
    rvr_manager.cpp \
    ui/rvr_currentstatus.cpp \
    ui/rvr_alignment.cpp \
    ui/rvr_calibration.cpp \
    ui/rvr_lineartest.cpp \
    ui/rvr_defaultset.cpp \
    ui/rvr_currentconfig.cpp \
    ui/rvr_defaultconfig.cpp \
    datadue/rvr_datawrite.cpp \
    datadue/rvr_dataparse.cpp \
    serialmodule/serialinfo.cpp \
    rvr_startui.cpp \
    ui/serial_message.cpp \
    datadue/rvr_logoutstore.cpp \
    zmq/rvr_zmq_worker.cpp \
    ui/rvr_calc_values.cpp \
    mess/messgae.cpp \
    mess/messagehelper.cpp \
    sqlite/rvr_database_sqllite.cpp \
    distanceTransfer/cdmatransport.cpp \
    distanceTransfer/setupthread.cpp \
#    windPlugins/windmeter.cpp \
#    windPlugins/MeterDrawingFunctions.cpp \
    rvr_managerFunctions.cpp \
    managerHead.cpp \
    sqlite/databaseoption.cpp \
    sqlite/rvr_data_due.cpp \
    ui/rvr_database_output.cpp \
    MessageParse/messageparse.cpp \
    managerinitObject.cpp \
    windPlugins/MeterMoveFunction.cpp \
    windPlugins/MeterDrawingFunctions.cpp \
    windPlugins/windmeter.cpp




HEADERS  += \
    serialmodule/rvr_serialparse.h \
    serialmodule/rvr_serialwrite.h \
    configmodule/rvr_configobject.h \
    serialmodule/serialport.h \
    comm.h \
    rvr_manager.h \
    ui/rvr_currentstatus.h \
    ui/rvr_alignment.h \
    ui/rvr_calibration.h \
    ui/rvr_lineartest.h \
    ui/rvr_defaultset.h \
    ui/rvr_currentconfig.h \
    ui/rvr_defaultconfig.h \
    datadue/rvr_datawrite.h \
    datadue/rvr_dataparse.h \
    serialmodule/serialinfo.h \
    rvr_startui.h \
    ui/serial_message.h \
    datadue/rvr_logoutstore.h \
    zmq/rvr_zmq_worker.h \
    ui/rvr_calc_values.h \
    mess/messgae.h \
    mess/messagehelper.h \
    mess/RVR_Reminder_Msg.h \
    sqlite/rvr_database_sqllite.h \
    distanceTransfer/cdmatransport.h \
    distanceTransfer/setupthread.h \
#    windPlugins/windmeter.h \
    managerHead.h \
    sqlite/databaseoption.h \
    sqlite/rvr_data_due.h \
    MessageParse/messageparse.h \
    windPlugins/windmeter.h



FORMS    += \
    rvr_manager.ui \
    ui/rvr_currentstatus.ui \
    ui/rvr_alignment.ui \
    ui/rvr_calibration.ui \
    ui/rvr_lineartest.ui \
    ui/rvr_defaultset.ui \
    ui/rvr_currentconfig.ui \
    ui/rvr_defaultconfig.ui \
    rvr_startui.ui \
    ui/serial_message.ui \
    ui/rvr_calc_values.ui \
    mess/messgae.ui

# Zero_MQ
INCLUDEPATH +=E:\ZeroMQx86\include

LIBS +=E:\ZeroMQx86\lib\libzmq-v90-mt-4_0_4.lib

RC_FILE += res.rc

RESOURCES += \
    rc.qrc









