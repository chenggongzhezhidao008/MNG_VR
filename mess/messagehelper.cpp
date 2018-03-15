#include "messagehelper.h"
#include <QDebug>

MessageHelper * MessageHelper::_MessHelper = 0;

MessageHelper::MessageHelper(QObject *) :
    QObject(qApp)
{
    int fontId = QFontDatabase::addApplicationFont("://image/fontawesome-webfont.ttf");
    QStringList list = QFontDatabase::applicationFontFamilies(fontId);
//    qDebug()<<"app supply language:"<<list;
    QString fontstr = list.at(0);
    font = QFont(fontstr);
}

void MessageHelper::setLable(QLabel *lab, QChar c, int size)
{
    font.setPointSize(size);
    lab->setFont(font);
    lab->setText(c);
    return ;
}

void MessageHelper::setButton(QPushButton *button, QChar c, int size)
{
    font.setPointSize(size);
    button->setFont(font);
    button->setText(c);
    return ;
}
