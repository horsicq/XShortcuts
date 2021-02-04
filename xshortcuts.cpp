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

void XShortcuts::addGroup(XShortcuts::ID idGroup)
{
    qint32 nEnd=getGroupEnd(idGroup);

    for(qint32 nId=idGroup+1;nId<nEnd;nId++)
    {
        g_listValueIDs.append((XShortcuts::ID)nId);
    }
}

void XShortcuts::setShortcutsIDs(QList<XShortcuts::ID> listValueIDs)
{
    this->g_listValueIDs=listValueIDs;
}

QList<XShortcuts::ID> XShortcuts::getShortcutsIDs()
{
    return g_listValueIDs;
}

void XShortcuts::load()
{
    QSettings *pSettings=nullptr;

    if(g_sFilePath!="")
    {
        pSettings=new QSettings(g_sFilePath,QSettings::IniFormat);
    }

    int nNumberOfIDs=g_listValueIDs.count();

    for(int i=0;i<nNumberOfIDs;i++)
    {
        ID id=g_listValueIDs.at(i);
        QString sName=idToSettingsString(id);
        QKeySequence ksDefault=getDefault(id);

        if(pSettings)
        {
            g_mapValues.insert(id,QKeySequence::fromString(pSettings->value(sName,ksDefault.toString()).toString()));
        }
        else
        {
            g_mapValues.insert(id,ksDefault);
        }
    }

    if(pSettings)
    {
        delete pSettings;
    }
}

void XShortcuts::save()
{
    if(g_sFilePath!="")
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
}

QKeySequence XShortcuts::getShortcut(XShortcuts::ID id)
{
    if(!g_mapValues.contains(id))
    {
        QString sErrorString=idToSettingsString(id);
        qDebug(sErrorString.toLatin1().data());
    }

    return g_mapValues.value(id);
}

void XShortcuts::setShortcut(XShortcuts::ID id, QKeySequence keyValue)
{
    g_mapValues.insert(id,keyValue);
}

bool XShortcuts::checkShortcut(XShortcuts::ID id, QKeySequence keyValue)
{
    bool bResult=true;

    if(keyValue!=QKeySequence())
    {
        ID idGroup=getGroupFromId(id);

        for(qint32 nId=idGroup+1;nId<getGroupEnd(idGroup);nId++)
        {
            if(id!=nId)
            {
                if(getShortcut((ID)nId)==keyValue)
                {
                    bResult=false;
                    break;
                }
            }
        }
    }

    return bResult;
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
        case ID_ACTION_COPY:                sResult=QString("Action/Copy");             break;
        case ID_STRINGS_COPYSTRING:         sResult=QString("Strings/CopyString");      break;
        case ID_STRINGS_COPYOFFSET:         sResult=QString("Strings/CopyOffset");      break;
        case ID_STRINGS_COPYSIZE:           sResult=QString("Strings/CopySize");        break;
        case ID_STRINGS_HEX:                sResult=QString("Strings/Hex");             break;
        case ID_HEX_DUMPTOFILE:             sResult=QString("Hex/DumpToFile");          break;
        case ID_HEX_GOTOADDRESS:            sResult=QString("Hex/GoToAddress");         break;
        case ID_HEX_GOTOOFFSET:             sResult=QString("Hex/GoToOffset");          break;
        case ID_HEX_SIGNATURE:              sResult=QString("Hex/Signature");           break;
        case ID_HEX_FIND:                   sResult=QString("Hex/Find");                break;
        case ID_HEX_FINDNEXT:               sResult=QString("Hex/FindNext");            break;
        case ID_HEX_SELECTALL:              sResult=QString("Hex/SelectAll");           break;
        case ID_HEX_COPYASHEX:              sResult=QString("Hex/CopyAsHex");           break;
        case ID_HEX_COPYCURSOROFFSET:       sResult=QString("Hex/CopyCursorOffset");    break;
        case ID_HEX_COPYCURSORADDRESS:      sResult=QString("Hex/CopyCursorAddress");   break;
        case ID_HEX_DISASM:                 sResult=QString("Hex/Disasm");              break;
        case ID_DISASM_DUMPTOFILE:          sResult=QString("Disasm/DumpToFile");       break;
        case ID_DISASM_GOTOADDRESS:         sResult=QString("Disasm/GoToAddress");      break;
        case ID_DISASM_GOTOOFFSET:          sResult=QString("Disasm/GoToOffset");       break;
        case ID_DISASM_HEXSIGNATURE:        sResult=QString("Disasm/HexSignature");     break;
        case ID_DISASM_SIGNATURE:           sResult=QString("Disasm/Signature");        break;
        case ID_DISASM_FIND:                sResult=QString("Disasm/Find");             break;
        case ID_DISASM_FINDNEXT:            sResult=QString("Disasm/FindNext");         break;
        case ID_DISASM_SELECTALL:           sResult=QString("Disasm/SelectAll");        break;
        case ID_DISASM_COPYASHEX:           sResult=QString("Disasm/CopyAsHex");        break;
        case ID_DISASM_HEX:                 sResult=QString("Disasm/Hex");              break;
        case ID_DEBUGGER_RUN:               sResult=QString("Debugger/Run");            break;
        case ID_DEBUGGER_BREAKPOINT:        sResult=QString("Debugger/Breakpoint");     break;
        case ID_DEBUGGER_STEPINTO:          sResult=QString("Debugger/StepInto");       break;
        case ID_DEBUGGER_STEPOVER:          sResult=QString("Debugger/StepOver");       break;
        case ID_ARCHIVE_COPYFILENAME:       sResult=QString("Archive/CopyFilename");    break;
        case ID_ARCHIVE_DUMPTOFILE:         sResult=QString("Archive/DumpToFile");      break;
        case ID_ARCHIVE_ENTROPY:            sResult=QString("Archive/Entropy");         break;
        case ID_ARCHIVE_HASH:               sResult=QString("Archive/Hash");            break;
        case ID_ARCHIVE_HEX:                sResult=QString("Archive/Hex");             break;
        case ID_ARCHIVE_OPEN:               sResult=QString("Archive/Open");            break;
        case ID_ARCHIVE_SCAN:               sResult=QString("Archive/Scan");            break;
        case ID_ARCHIVE_STRINGS:            sResult=QString("Archive/Strings");         break;
    }

    return sResult;
}

QString XShortcuts::idToString(XShortcuts::ID id)
{
    QString sResult=tr("Unknown");

    switch(id)
    {
        case ID_ACTION_COPY:                sResult=tr("Copy");                         break;
        case ID_STRINGS_COPYSTRING:         sResult=tr("Copy string");                  break;
        case ID_STRINGS_COPYOFFSET:         sResult=tr("Copy offset");                  break;
        case ID_STRINGS_COPYSIZE:           sResult=tr("Copy size");                    break;
        case ID_STRINGS_HEX:                sResult=tr("Hex");                          break;
        case ID_HEX_DUMPTOFILE:             sResult=tr("Dump to file");                 break;
        case ID_HEX_GOTOADDRESS:            sResult=tr("Go to address");                break;
        case ID_HEX_GOTOOFFSET:             sResult=tr("Go to offset");                 break;
        case ID_HEX_SIGNATURE:              sResult=tr("Signature");                    break;
        case ID_HEX_FIND:                   sResult=tr("Find");                         break;
        case ID_HEX_FINDNEXT:               sResult=tr("Find next");                    break;
        case ID_HEX_SELECTALL:              sResult=tr("Select all");                   break;
        case ID_HEX_COPYASHEX:              sResult=tr("Copy as hex");                  break;
        case ID_HEX_COPYCURSOROFFSET:       sResult=tr("Copy cursor offset");           break;
        case ID_HEX_COPYCURSORADDRESS:      sResult=tr("Copy cursor address");          break;
        case ID_HEX_DISASM:                 sResult=tr("Disasm");                       break;
        case ID_DISASM_DUMPTOFILE:          sResult=tr("Dump to file");                 break;
        case ID_DISASM_GOTOADDRESS:         sResult=tr("Go to address");                break;
        case ID_DISASM_GOTOOFFSET:          sResult=tr("Go to offset");                 break;
        case ID_DISASM_HEXSIGNATURE:        sResult=tr("Hex signature");                break;
        case ID_DISASM_SIGNATURE:           sResult=tr("Signature");                    break;
        case ID_DISASM_FIND:                sResult=tr("Find");                         break;
        case ID_DISASM_FINDNEXT:            sResult=tr("Find next");                    break;
        case ID_DISASM_SELECTALL:           sResult=tr("Select all");                   break;
        case ID_DISASM_COPYASHEX:           sResult=tr("Copy as hex");                  break;
        case ID_DISASM_COPYCURSORADDRESS:   sResult=tr("Copy cursor address");          break;
        case ID_DISASM_COPYCURSOROFFSET:    sResult=tr("Copy cursor offset");           break;
        case ID_DISASM_HEX:                 sResult=tr("Hex");                          break;
        case ID_DEBUGGER_RUN:               sResult=tr("Run");                          break;
        case ID_DEBUGGER_BREAKPOINT:        sResult=tr("Breakpoint");                   break;
        case ID_DEBUGGER_STEPINTO:          sResult=tr("Step into");                    break;
        case ID_DEBUGGER_STEPOVER:          sResult=tr("Step over");                    break;
        case ID_ARCHIVE_COPYFILENAME:       sResult=tr("Copy filename");                break;
        case ID_ARCHIVE_DUMPTOFILE:         sResult=tr("Dump to file");                 break;
        case ID_ARCHIVE_ENTROPY:            sResult=tr("Entropy");                      break;
        case ID_ARCHIVE_HASH:               sResult=tr("Hash");                         break;
        case ID_ARCHIVE_HEX:                sResult=tr("Hex");                          break;
        case ID_ARCHIVE_OPEN:               sResult=tr("Open");                         break;
        case ID_ARCHIVE_SCAN:               sResult=tr("Scan");                         break;
        case ID_ARCHIVE_STRINGS:            sResult=tr("Strings");                      break;
    }

    return sResult;
}

QKeySequence XShortcuts::getDefault(XShortcuts::ID id)
{
    QKeySequence ksResult=QKeySequence();

    switch(id)
    {
        case ID_ACTION_COPY:                ksResult=QKeySequence::Copy;            break;
        case ID_STRINGS_COPYSTRING:         ksResult=QKeySequence::Copy;            break;
        case ID_STRINGS_COPYOFFSET:         ksResult=QKeySequence();                break;
        case ID_STRINGS_COPYSIZE:           ksResult=QKeySequence();                break;
        case ID_STRINGS_HEX:                ksResult=QKeySequence();                break;
        case ID_HEX_DUMPTOFILE:             ksResult=Qt::CTRL+Qt::Key_D;            break;
        case ID_HEX_GOTOADDRESS:            ksResult=Qt::CTRL+Qt::Key_G;            break;
        case ID_HEX_GOTOOFFSET:             ksResult=QKeySequence();                break;
        case ID_HEX_SIGNATURE:              ksResult=Qt::Key_S;                     break;
        case ID_HEX_FIND:                   ksResult=QKeySequence::Find;            break;
        case ID_HEX_FINDNEXT:               ksResult=QKeySequence::FindNext;        break;
        case ID_HEX_SELECTALL:              ksResult=QKeySequence::SelectAll;       break;
        case ID_HEX_COPYASHEX:              ksResult=QKeySequence::Copy;            break;
        case ID_HEX_COPYCURSOROFFSET:       ksResult=QKeySequence();                break;
        case ID_HEX_COPYCURSORADDRESS:      ksResult=QKeySequence();                break;
        case ID_HEX_DISASM:                 ksResult=QKeySequence();                break;
        case ID_DISASM_DUMPTOFILE:          ksResult=Qt::CTRL+Qt::Key_D;            break;
        case ID_DISASM_GOTOADDRESS:         ksResult=Qt::CTRL+Qt::Key_G;            break;
        case ID_DISASM_GOTOOFFSET:          ksResult=QKeySequence();                break;
        case ID_DISASM_HEXSIGNATURE:        ksResult=Qt::Key_S;                     break;
        case ID_DISASM_SIGNATURE:           ksResult=Qt::SHIFT+Qt::Key_G;           break;
        case ID_DISASM_FIND:                ksResult=QKeySequence::Find;            break;
        case ID_DISASM_FINDNEXT:            ksResult=QKeySequence::FindNext;        break;
        case ID_DISASM_SELECTALL:           ksResult=QKeySequence::SelectAll;       break;
        case ID_DISASM_COPYASHEX:           ksResult=QKeySequence::Copy;            break;
        case ID_DISASM_COPYCURSORADDRESS:   ksResult=QKeySequence();                break;
        case ID_DISASM_COPYCURSOROFFSET:    ksResult=QKeySequence();                break;
        case ID_DISASM_HEX:                 ksResult=QKeySequence();                break;
        case ID_DEBUGGER_RUN:               ksResult=Qt::Key_F9;                    break;
        case ID_DEBUGGER_BREAKPOINT:        ksResult=Qt::Key_F2;                    break;
        case ID_DEBUGGER_STEPINTO:          ksResult=Qt::Key_F7;                    break;
        case ID_DEBUGGER_STEPOVER:          ksResult=Qt::Key_F8;                    break;
        case ID_ARCHIVE_COPYFILENAME:       ksResult=QKeySequence::Copy;            break;
        case ID_ARCHIVE_DUMPTOFILE:         ksResult=Qt::CTRL+Qt::Key_D;            break;
        case ID_ARCHIVE_ENTROPY:            ksResult=QKeySequence();                break;
        case ID_ARCHIVE_HASH:               ksResult=QKeySequence();                break;
        case ID_ARCHIVE_HEX:                ksResult=QKeySequence();                break;
        case ID_ARCHIVE_OPEN:               ksResult=QKeySequence();                break;
        case ID_ARCHIVE_SCAN:               ksResult=QKeySequence();                break;
        case ID_ARCHIVE_STRINGS:            ksResult=QKeySequence();                break;
    }

    return ksResult;
}

QString XShortcuts::idToGroupString(XShortcuts::ID id)
{
    QString sResult=tr("Unknown");

    if      (id&ID_ACTION)      sResult=tr("Action");
    else if (id&ID_STRINGS)     sResult=tr("Strings");
    else if (id&ID_HEX)         sResult=tr("Hex");
    else if (id&ID_DISASM)      sResult=tr("Disasm");
    else if (id&ID_DEBUGGER)    sResult=tr("Debugger");
    else if (id&ID_ARCHIVE)     sResult=tr("Archive");

    return sResult;
}

XShortcuts::ID XShortcuts::getGroupEnd(XShortcuts::ID idGroup)
{
    int nEnd=0;

    if(idGroup==ID_ACTION)      nEnd=ID_ACTION__END;
    if(idGroup==ID_STRINGS)     nEnd=ID_STRINGS__END;
    if(idGroup==ID_HEX)         nEnd=ID_HEX__END;
    if(idGroup==ID_DISASM)      nEnd=ID_DISASM__END;
    if(idGroup==ID_DEBUGGER)    nEnd=ID_DEBUGGER__END;
    if(idGroup==ID_ARCHIVE)     nEnd=ID_ARCHIVE__END;

    return (ID)nEnd;
}

XShortcuts::ID XShortcuts::getGroupFromId(XShortcuts::ID id)
{
    qint32 nResult=id;

    nResult&=0xFFFF0000;

    return (ID)nResult;
}
