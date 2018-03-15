INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

QT += core gui gui-private
!build_xlsx_lib:DEFINES += XLSX_NO_LIB

HEADERS += $$PWD/xlsx/xlsxdocpropscore_p.h \
    $$PWD/xlsx/xlsxdocpropsapp_p.h \
    $$PWD/xlsx/xlsxrelationships_p.h \
    $$PWD/xlsx/xlsxutility_p.h \
    $$PWD/xlsx/xlsxsharedstrings_p.h \
    $$PWD/xlsx/xlsxcontenttypes_p.h \
    $$PWD/xlsx/xlsxtheme_p.h \
    $$PWD/xlsx/xlsxformat.h \
    $$PWD/xlsx/xlsxworkbook.h \
    $$PWD/xlsx/xlsxstyles_p.h \
    $$PWD/xlsx/xlsxabstractsheet.h \
    $$PWD/xlsx/xlsxabstractsheet_p.h \
    $$PWD/xlsx/xlsxworksheet.h \
    $$PWD/xlsx/xlsxworksheet_p.h \
    $$PWD/xlsx/xlsxchartsheet.h \
    $$PWD/xlsx/xlsxchartsheet_p.h \
    $$PWD/xlsx/xlsxzipwriter_p.h \
    $$PWD/xlsx/xlsxworkbook_p.h \
    $$PWD/xlsx/xlsxformat_p.h \
    $$PWD/xlsx/xlsxglobal.h \
    $$PWD/xlsx/xlsxdrawing_p.h \
    $$PWD/xlsx/xlsxzipreader_p.h \
    $$PWD/xlsx/xlsxdocument.h \
    $$PWD/xlsx/xlsxdocument_p.h \
    $$PWD/xlsx/xlsxcell.h \
    $$PWD/xlsx/xlsxcell_p.h \
    $$PWD/xlsx/xlsxdatavalidation.h \
    $$PWD/xlsx/xlsxdatavalidation_p.h \
    $$PWD/xlsx/xlsxcellreference.h \
    $$PWD/xlsx/xlsxcellrange.h \
    $$PWD/xlsx/xlsxrichstring_p.h \
    $$PWD/xlsx/xlsxrichstring.h \
    $$PWD/xlsx/xlsxconditionalformatting.h \
    $$PWD/xlsx/xlsxconditionalformatting_p.h \
    $$PWD/xlsx/xlsxcolor_p.h \
    $$PWD/xlsx/xlsxnumformatparser_p.h \
    $$PWD/xlsx/xlsxdrawinganchor_p.h \
    $$PWD/xlsx/xlsxmediafile_p.h \
    $$PWD/xlsx/xlsxabstractooxmlfile.h \
    $$PWD/xlsx/xlsxabstractooxmlfile_p.h \
    $$PWD/xlsx/xlsxchart.h \
    $$PWD/xlsx/xlsxchart_p.h \
    $$PWD/xlsx/xlsxsimpleooxmlfile_p.h \
    $$PWD/xlsx/xlsxcellformula.h \
    $$PWD/xlsx/xlsxcellformula_p.h

SOURCES += $$PWD/xlsx/xlsxdocpropscore.cpp \
    $$PWD/xlsx/xlsxdocpropsapp.cpp \
    $$PWD/xlsx/xlsxrelationships.cpp \
    $$PWD/xlsx/xlsxutility.cpp \
    $$PWD/xlsx/xlsxsharedstrings.cpp \
    $$PWD/xlsx/xlsxcontenttypes.cpp \
    $$PWD/xlsx/xlsxtheme.cpp \
    $$PWD/xlsx/xlsxformat.cpp \
    $$PWD/xlsx/xlsxstyles.cpp \
    $$PWD/xlsx/xlsxworkbook.cpp \
    $$PWD/xlsx/xlsxabstractsheet.cpp \
    $$PWD/xlsx/xlsxworksheet.cpp \
    $$PWD/xlsx/xlsxchartsheet.cpp \
    $$PWD/xlsx/xlsxzipwriter.cpp \
    $$PWD/xlsx/xlsxdrawing.cpp \
    $$PWD/xlsx/xlsxzipreader.cpp \
    $$PWD/xlsx/xlsxdocument.cpp \
    $$PWD/xlsx/xlsxcell.cpp \
    $$PWD/xlsx/xlsxdatavalidation.cpp \
    $$PWD/xlsx/xlsxcellreference.cpp \
    $$PWD/xlsx/xlsxcellrange.cpp \
    $$PWD/xlsx/xlsxrichstring.cpp \
    $$PWD/xlsx/xlsxconditionalformatting.cpp \
    $$PWD/xlsx/xlsxcolor.cpp \
    $$PWD/xlsx/xlsxnumformatparser.cpp \
    $$PWD/xlsx/xlsxdrawinganchor.cpp \
    $$PWD/xlsx/xlsxmediafile.cpp \
    $$PWD/xlsx/xlsxabstractooxmlfile.cpp \
    $$PWD/xlsx/xlsxchart.cpp \
    $$PWD/xlsx/xlsxsimpleooxmlfile.cpp \
    $$PWD/xlsx/xlsxcellformula.cpp

