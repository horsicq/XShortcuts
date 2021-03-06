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
    g_bIsNative=false;
}

void XShortcuts::setName(QString sValue)
{
    this->g_sName=sValue;
}

void XShortcuts::setNative(bool bValue)
{
    g_bIsNative=bValue;
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

    if(g_bIsNative)
    {
        pSettings=new QSettings;
    }
    else if(g_sName!="")
    {
        pSettings=new QSettings(qApp->applicationDirPath()+QDir::separator()+QString("%1").arg(g_sName),QSettings::IniFormat); // TODO more options
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
    QSettings *pSettings=nullptr;

    if(g_bIsNative)
    {
        pSettings=new QSettings;
    }
    else if(g_sName!="")
    {
        pSettings=new QSettings(qApp->applicationDirPath()+QDir::separator()+QString("%1").arg(g_sName),QSettings::IniFormat); // TODO more options
    }

    if(pSettings)
    {
        int nNumberOfIDs=g_listValueIDs.count();

        for(int i=0;i<nNumberOfIDs;i++)
        {
            ID id=g_listValueIDs.at(i);
            QString sName=idToSettingsString(id);
            pSettings->setValue(sName,g_mapValues.value(id).toString());
        }
    }

    if(pSettings)
    {
        delete pSettings;
    }
}

QKeySequence XShortcuts::getShortcut(XShortcuts::ID id)
{
#ifdef QT_DEBUG
    if(!g_mapValues.contains(id))
    {
        QString sErrorString=idToSettingsString(id);
        qDebug(sErrorString.toLatin1().data());
    }
#endif
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

QString XShortcuts::idToSettingsString(XShortcuts::ID id)
{
    QString sResult="Unknown";

    switch(id)
    {
        case ID_ACTION_COPY:                sResult=QString("Shortcuts/Action/Copy");                   break;
        case ID_STRINGS_COPYSTRING:         sResult=QString("Shortcuts/Strings/CopyString");            break;
        case ID_STRINGS_COPYOFFSET:         sResult=QString("Shortcuts/Strings/CopyOffset");            break;
        case ID_STRINGS_COPYSIZE:           sResult=QString("Shortcuts/Strings/CopySize");              break;
        case ID_STRINGS_HEX:                sResult=QString("Shortcuts/Strings/Hex");                   break;
        case ID_STRINGS_DEMANGLE:           sResult=QString("Shortcuts/Strings/Demangle");              break;
        case ID_SIGNATURES_COPYNAME:        sResult=QString("Shortcuts/Signatures/CopyName");           break;
        case ID_SIGNATURES_COPYSIGNATURE:   sResult=QString("Shortcuts/Signatures/CopySignature");      break;
        case ID_SIGNATURES_COPYADDRESS:     sResult=QString("Shortcuts/Signatures/CopyAddress");        break;
        case ID_SIGNATURES_COPYOFFSET:      sResult=QString("Shortcuts/Signatures/CopyOffset");         break;
        case ID_SIGNATURES_COPYSIZE:        sResult=QString("Shortcuts/Signatures/CopySize");           break;
        case ID_SIGNATURES_HEX:             sResult=QString("Shortcuts/Signatures/Hex");                break;
        case ID_HEX_DUMPTOFILE:             sResult=QString("Shortcuts/Hex/DumpToFile");                break;
        case ID_HEX_GOTOADDRESS:            sResult=QString("Shortcuts/Hex/GoToAddress");               break;
        case ID_HEX_GOTOOFFSET:             sResult=QString("Shortcuts/Hex/GoToOffset");                break;
        case ID_HEX_SIGNATURE:              sResult=QString("Shortcuts/Hex/Signature");                 break;
        case ID_HEX_FIND:                   sResult=QString("Shortcuts/Hex/Find");                      break;
        case ID_HEX_FINDNEXT:               sResult=QString("Shortcuts/Hex/FindNext");                  break;
        case ID_HEX_SELECTALL:              sResult=QString("Shortcuts/Hex/SelectAll");                 break;
        case ID_HEX_COPYASHEX:              sResult=QString("Shortcuts/Hex/CopyAsHex");                 break;
        case ID_HEX_COPYCURSOROFFSET:       sResult=QString("Shortcuts/Hex/CopyCursorOffset");          break;
        case ID_HEX_COPYCURSORADDRESS:      sResult=QString("Shortcuts/Hex/CopyCursorAddress");         break;
        case ID_HEX_DISASM:                 sResult=QString("Shortcuts/Hex/Disasm");                    break;
        case ID_HEX_MEMORYMAP:              sResult=QString("Shortcuts/Hex/MemoryMap");                 break;
        case ID_DISASM_DUMPTOFILE:          sResult=QString("Shortcuts/Disasm/DumpToFile");             break;
        case ID_DISASM_GOTOADDRESS:         sResult=QString("Shortcuts/Disasm/GoToAddress");            break;
        case ID_DISASM_GOTOOFFSET:          sResult=QString("Shortcuts/Disasm/GoToOffset");             break;
        case ID_DISASM_GOTOENTRYPOINT:      sResult=QString("Shortcuts/Disasm/GoToEntryPoint");         break;
        case ID_DISASM_HEXSIGNATURE:        sResult=QString("Shortcuts/Disasm/HexSignature");           break;
        case ID_DISASM_SIGNATURE:           sResult=QString("Shortcuts/Disasm/Signature");              break;
        case ID_DISASM_FIND:                sResult=QString("Shortcuts/Disasm/Find");                   break;
        case ID_DISASM_FINDNEXT:            sResult=QString("Shortcuts/Disasm/FindNext");               break;
        case ID_DISASM_SELECTALL:           sResult=QString("Shortcuts/Disasm/SelectAll");              break;
        case ID_DISASM_COPYASHEX:           sResult=QString("Shortcuts/Disasm/CopyAsHex");              break;
        case ID_DISASM_COPYCURSOROFFSET:    sResult=QString("Shortcuts/Disasm/CopyCursorOffset");       break;
        case ID_DISASM_COPYCURSORADDRESS:   sResult=QString("Shortcuts/Disasm/CopyCursorAddress");      break;
        case ID_DISASM_HEX:                 sResult=QString("Shortcuts/Disasm/Hex");                    break;
        case ID_DEBUGGER_RUN:               sResult=QString("Shortcuts/Debugger/Run");                  break;
        case ID_DEBUGGER_SETBREAKPOINT:     sResult=QString("Shortcuts/Debugger/SetBreakpoint");        break;
        case ID_DEBUGGER_STEPINTO:          sResult=QString("Shortcuts/Debugger/StepInto");             break;
        case ID_DEBUGGER_STEPOVER:          sResult=QString("Shortcuts/Debugger/StepOver");             break;
        case ID_DEBUGGER_STOP:              sResult=QString("Shortcuts/Debugger/Stop");                 break;
        case ID_ARCHIVE_COPYFILENAME:       sResult=QString("Shortcuts/Archive/CopyFilename");          break;
        case ID_ARCHIVE_DUMPTOFILE:         sResult=QString("Shortcuts/Archive/DumpToFile");            break;
        case ID_ARCHIVE_ENTROPY:            sResult=QString("Shortcuts/Archive/Entropy");               break;
        case ID_ARCHIVE_HASH:               sResult=QString("Shortcuts/Archive/Hash");                  break;
        case ID_ARCHIVE_HEX:                sResult=QString("Shortcuts/Archive/Hex");                   break;
        case ID_ARCHIVE_OPEN:               sResult=QString("Shortcuts/Archive/Open");                  break;
        case ID_ARCHIVE_SCAN:               sResult=QString("Shortcuts/Archive/Scan");                  break;
        case ID_ARCHIVE_STRINGS:            sResult=QString("Shortcuts/Archive/Strings");               break;
        case ID_TABLE_HEX:                  sResult=QString("Shortcuts/Table/Hex");                     break;
        case ID_TABLE_DISASM:               sResult=QString("Shortcuts/Table/Disasm");                  break;
        default:
        {
        #ifdef QT_DEBUG
            qDebug("UNKNOWN!!!");
        #endif
        }
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
        case ID_STRINGS_DEMANGLE:           sResult=tr("Demangle");                     break;
        case ID_SIGNATURES_COPYNAME:        sResult=tr("Copy name");                    break;
        case ID_SIGNATURES_COPYSIGNATURE:   sResult=tr("Copy signature");               break;
        case ID_SIGNATURES_COPYADDRESS:     sResult=tr("Copy address");                 break;
        case ID_SIGNATURES_COPYOFFSET:      sResult=tr("Copy offset");                  break;
        case ID_SIGNATURES_COPYSIZE:        sResult=tr("Copy size");                    break;
        case ID_SIGNATURES_HEX:             sResult=tr("Hex");                          break;
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
        case ID_HEX_MEMORYMAP:              sResult=tr("Memory map");                   break;
        case ID_DISASM_DUMPTOFILE:          sResult=tr("Dump to file");                 break;
        case ID_DISASM_GOTOADDRESS:         sResult=tr("Go to address");                break;
        case ID_DISASM_GOTOOFFSET:          sResult=tr("Go to offset");                 break;
        case ID_DISASM_GOTOENTRYPOINT:      sResult=tr("Go to entry point");            break;
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
        case ID_DEBUGGER_SETBREAKPOINT:     sResult=tr("Set breakpoint");               break;
        case ID_DEBUGGER_STEPINTO:          sResult=tr("Step into");                    break;
        case ID_DEBUGGER_STEPOVER:          sResult=tr("Step over");                    break;
        case ID_DEBUGGER_STOP:              sResult=tr("Stop");                         break;
        case ID_ARCHIVE_COPYFILENAME:       sResult=tr("Copy filename");                break;
        case ID_ARCHIVE_DUMPTOFILE:         sResult=tr("Dump to file");                 break;
        case ID_ARCHIVE_ENTROPY:            sResult=tr("Entropy");                      break;
        case ID_ARCHIVE_HASH:               sResult=tr("Hash");                         break;
        case ID_ARCHIVE_HEX:                sResult=tr("Hex");                          break;
        case ID_ARCHIVE_OPEN:               sResult=tr("Open");                         break;
        case ID_ARCHIVE_SCAN:               sResult=tr("Scan");                         break;
        case ID_ARCHIVE_STRINGS:            sResult=tr("Strings");                      break;
        case ID_TABLE_HEX:                  sResult=tr("Hex");                          break;
        case ID_TABLE_DISASM:               sResult=tr("Disasm");                       break;
        default:                            sResult=tr("Unknown");
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
        case ID_STRINGS_DEMANGLE:           ksResult=QKeySequence();                break;
        case ID_SIGNATURES_COPYNAME:        ksResult=QKeySequence::Copy;            break;
        case ID_SIGNATURES_COPYSIGNATURE:   ksResult=QKeySequence();                break;
        case ID_SIGNATURES_COPYADDRESS:     ksResult=QKeySequence();                break;
        case ID_SIGNATURES_COPYOFFSET:      ksResult=QKeySequence();                break;
        case ID_SIGNATURES_COPYSIZE:        ksResult=QKeySequence();                break;
        case ID_SIGNATURES_HEX:             ksResult=QKeySequence();                break;
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
        case ID_HEX_MEMORYMAP:              ksResult=QKeySequence();                break;
        case ID_DISASM_DUMPTOFILE:          ksResult=Qt::CTRL+Qt::Key_D;            break;
        case ID_DISASM_GOTOADDRESS:         ksResult=Qt::CTRL+Qt::Key_G;            break;
        case ID_DISASM_GOTOOFFSET:          ksResult=QKeySequence();                break;
        case ID_DISASM_GOTOENTRYPOINT:      ksResult=QKeySequence();                break;
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
        case ID_DEBUGGER_SETBREAKPOINT:     ksResult=Qt::Key_F2;                    break;
        case ID_DEBUGGER_STEPINTO:          ksResult=Qt::Key_F7;                    break;
        case ID_DEBUGGER_STEPOVER:          ksResult=Qt::Key_F8;                    break;
        case ID_DEBUGGER_STOP:              ksResult=QKeySequence();                break;
        case ID_ARCHIVE_COPYFILENAME:       ksResult=QKeySequence::Copy;            break;
        case ID_ARCHIVE_DUMPTOFILE:         ksResult=Qt::CTRL+Qt::Key_D;            break;
        case ID_ARCHIVE_ENTROPY:            ksResult=QKeySequence();                break;
        case ID_ARCHIVE_HASH:               ksResult=QKeySequence();                break;
        case ID_ARCHIVE_HEX:                ksResult=QKeySequence();                break;
        case ID_ARCHIVE_OPEN:               ksResult=QKeySequence();                break;
        case ID_ARCHIVE_SCAN:               ksResult=QKeySequence();                break;
        case ID_ARCHIVE_STRINGS:            ksResult=QKeySequence();                break;
        case ID_TABLE_HEX:                  ksResult=QKeySequence();                break;
        case ID_TABLE_DISASM:               ksResult=QKeySequence();                break;
        default:                            ksResult=QKeySequence();
    }

    return ksResult;
}

QString XShortcuts::idToGroupString(XShortcuts::ID id)
{
    QString sResult=tr("Unknown");

    if      (id&ID_ACTION)      sResult=tr("Action");
    else if (id&ID_STRINGS)     sResult=tr("Strings");
    else if (id&ID_SIGNATURES)  sResult=tr("Signatures");
    else if (id&ID_HEX)         sResult=tr("Hex");
    else if (id&ID_DISASM)      sResult=tr("Disasm");
    else if (id&ID_DEBUGGER)    sResult=tr("Debugger");
    else if (id&ID_ARCHIVE)     sResult=tr("Archive");
    else if (id&ID_TABLE)       sResult=tr("Table");

    return sResult;
}

XShortcuts::ID XShortcuts::getGroupEnd(XShortcuts::ID idGroup)
{
    int nEnd=0;

    if(idGroup==ID_ACTION)      nEnd=ID_ACTION__END;
    if(idGroup==ID_STRINGS)     nEnd=ID_STRINGS__END;
    if(idGroup==ID_SIGNATURES)  nEnd=ID_SIGNATURES__END;
    if(idGroup==ID_HEX)         nEnd=ID_HEX__END;
    if(idGroup==ID_DISASM)      nEnd=ID_DISASM__END;
    if(idGroup==ID_DEBUGGER)    nEnd=ID_DEBUGGER__END;
    if(idGroup==ID_ARCHIVE)     nEnd=ID_ARCHIVE__END;
    if(idGroup==ID_TABLE)       nEnd=ID_TABLE__END;

    return (ID)nEnd;
}

XShortcuts::ID XShortcuts::getGroupFromId(XShortcuts::ID id)
{
    qint32 nResult=id;

    nResult&=0xFFFF0000;

    return (ID)nResult;
}
