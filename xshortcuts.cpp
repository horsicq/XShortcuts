// copyright (c) 2021 hors<horsicq@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
#include "xshortcuts.h"

XShortcuts::XShortcuts(QObject *pParent) : QObject(pParent)
{

}

void XShortcuts::setName(QString sName)
{
    this->g_sName=sName;
    this->g_sFilePath=getApplicationDataPath()+QDir::separator()+QString("%1").arg(sName);
}

void XShortcuts::setValueIDs(QList<XShortcuts::ID> listValueIDs)
{
    this->g_listValueIDs=listValueIDs;
}

void XShortcuts::load()
{
    QSettings settings(g_sFilePath,QSettings::IniFormat);

    int nNumberOfIDs=g_listValueIDs.count();

    for(int i=0;i<nNumberOfIDs;i++)
    {
        ID id=g_listValueIDs.at(i);
        QString sName=idToSettingsString(id);
        QKeySequence ksDefault=getDefault(id);

        g_mapValues.insert(id,QKeySequence::fromString(settings.value(sName,ksDefault.toString()).toString()));
    }
}

void XShortcuts::save()
{
    QSettings settings(g_sFilePath,QSettings::IniFormat);

    int nNumberOfIDs=g_listValueIDs.count();

    for(int i=0;i<nNumberOfIDs;i++)
    {
        ID id=g_listValueIDs.at(i);
        QString sName=idToSettingsString(id);
        settings.setValue(sName,g_mapValues.value(id).toString());
    }
}

QString XShortcuts::getApplicationDataPath()
{
    QString sResult;
#ifdef Q_OS_MAC
    sResult=qApp->applicationDirPath()+"/../Resources";
#else
    sResult=qApp->applicationDirPath();
#endif
    return sResult;
}

QString XShortcuts::idToSettingsString(XShortcuts::ID id)
{
    QString sResult="Unknown";

    switch(id)
    {
        case ID_ACTION_COPY:        sResult=QString("Action_Copy");         break;
    }

    return sResult;
}

QKeySequence XShortcuts::getDefault(XShortcuts::ID id)
{
    QKeySequence ksResult;

    switch(id)
    {
        case ID_ACTION_COPY:                ksResult=QKeySequence::Copy;           break;
    }

    return ksResult;
}
