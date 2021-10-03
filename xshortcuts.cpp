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

void XShortcuts::addGroup(GROUPID groupId)
{
    qint32 nEnd=getGroupEnd(groupId);

    for(qint32 nId=(groupId<<GROUP_SH)+1;nId<nEnd;nId++)
    {
        g_listValueIDs.append((XShortcuts::ID)nId);
    }
}

void XShortcuts::addGroup(ID id) // TODO Remove
{
    qint32 nEnd=getGroupEnd((GROUPID)(id>>GROUP_SH));

    for(qint32 nId=id+1;nId<nEnd;nId++)
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

#ifdef QT_DEBUG
    if(pSettings)
    {
        qDebug("XShortcuts load file %s",pSettings->fileName().toLatin1().data());
    }
#endif

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

#ifdef QT_DEBUG
    if(pSettings)
    {
        qDebug("XShortcuts save file %s",pSettings->fileName().toLatin1().data());
    }
#endif

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
        GROUPID idGroup=getGroupId(id);

        for(qint32 nId=(idGroup<<GROUP_SH)+1;nId<getGroupEnd(idGroup);nId++)
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
    QString sResult=QString("Unknown");

    switch(id)
    {
        case ID_ACTION_COPY:                        sResult=QString("Shortcuts/Action/Copy");                       break;
        case ID_FILE_OPEN:                          sResult=QString("Shortcuts/File/Open");                         break;
        case ID_FILE_SAVE:                          sResult=QString("Shortcuts/File/Save");                         break;
        case ID_FILE_SAVEAS:                        sResult=QString("Shortcuts/File/SaveAs");                       break;
        case ID_FILE_CLOSE:                         sResult=QString("Shortcuts/File/Close");                        break;
        case ID_FILE_PRINT:                         sResult=QString("Shortcuts/File/Print");                        break;
        case ID_FILE_EXIT:                          sResult=QString("Shortcuts/File/Exit");                         break;
        case ID_STRINGS_COPYSTRING:                 sResult=QString("Shortcuts/Strings/CopyString");                break;
        case ID_STRINGS_COPYOFFSET:                 sResult=QString("Shortcuts/Strings/CopyOffset");                break;
        case ID_STRINGS_COPYSIZE:                   sResult=QString("Shortcuts/Strings/CopySize");                  break;
        case ID_STRINGS_HEX:                        sResult=QString("Shortcuts/Strings/Hex");                       break;
        case ID_STRINGS_DEMANGLE:                   sResult=QString("Shortcuts/Strings/Demangle");                  break;
        case ID_SIGNATURES_COPYNAME:                sResult=QString("Shortcuts/Signatures/CopyName");               break;
        case ID_SIGNATURES_COPYSIGNATURE:           sResult=QString("Shortcuts/Signatures/CopySignature");          break;
        case ID_SIGNATURES_COPYADDRESS:             sResult=QString("Shortcuts/Signatures/CopyAddress");            break;
        case ID_SIGNATURES_COPYOFFSET:              sResult=QString("Shortcuts/Signatures/CopyOffset");             break;
        case ID_SIGNATURES_COPYSIZE:                sResult=QString("Shortcuts/Signatures/CopySize");               break;
        case ID_SIGNATURES_HEX:                     sResult=QString("Shortcuts/Signatures/Hex");                    break;
        case ID_HEX_DUMPTOFILE:                     sResult=QString("Shortcuts/Hex/DumpToFile");                    break;
        case ID_HEX_GOTOADDRESS:                    sResult=QString("Shortcuts/Hex/GoToAddress");                   break;
        case ID_HEX_GOTOOFFSET:                     sResult=QString("Shortcuts/Hex/GoToOffset");                    break;
        case ID_HEX_SIGNATURE:                      sResult=QString("Shortcuts/Hex/Signature");                     break;
        case ID_HEX_FIND:                           sResult=QString("Shortcuts/Hex/Find");                          break;
        case ID_HEX_FINDNEXT:                       sResult=QString("Shortcuts/Hex/FindNext");                      break;
        case ID_HEX_SELECTALL:                      sResult=QString("Shortcuts/Hex/SelectAll");                     break;
        case ID_HEX_COPYASHEX:                      sResult=QString("Shortcuts/Hex/CopyAsHex");                     break;
        case ID_HEX_COPYCURSOROFFSET:               sResult=QString("Shortcuts/Hex/CopyCursorOffset");              break;
        case ID_HEX_COPYCURSORADDRESS:              sResult=QString("Shortcuts/Hex/CopyCursorAddress");             break;
        case ID_HEX_DISASM:                         sResult=QString("Shortcuts/Hex/Disasm");                        break;
        case ID_HEX_MEMORYMAP:                      sResult=QString("Shortcuts/Hex/MemoryMap");                     break;
        case ID_DISASM_DUMPTOFILE:                  sResult=QString("Shortcuts/Disasm/DumpToFile");                 break;
        case ID_DISASM_GOTOADDRESS:                 sResult=QString("Shortcuts/Disasm/GoToAddress");                break;
        case ID_DISASM_GOTOOFFSET:                  sResult=QString("Shortcuts/Disasm/GoToOffset");                 break;
        case ID_DISASM_GOTOENTRYPOINT:              sResult=QString("Shortcuts/Disasm/GoToEntryPoint");             break;
        case ID_DISASM_HEXSIGNATURE:                sResult=QString("Shortcuts/Disasm/HexSignature");               break;
        case ID_DISASM_SIGNATURE:                   sResult=QString("Shortcuts/Disasm/Signature");                  break;
        case ID_DISASM_FIND:                        sResult=QString("Shortcuts/Disasm/Find");                       break;
        case ID_DISASM_FINDNEXT:                    sResult=QString("Shortcuts/Disasm/FindNext");                   break;
        case ID_DISASM_SELECTALL:                   sResult=QString("Shortcuts/Disasm/SelectAll");                  break;
        case ID_DISASM_COPYASHEX:                   sResult=QString("Shortcuts/Disasm/CopyAsHex");                  break;
        case ID_DISASM_COPYCURSOROFFSET:            sResult=QString("Shortcuts/Disasm/CopyCursorOffset");           break;
        case ID_DISASM_COPYCURSORADDRESS:           sResult=QString("Shortcuts/Disasm/CopyCursorAddress");          break;
        case ID_DISASM_HEX:                         sResult=QString("Shortcuts/Disasm/Hex");                        break;
        case ID_DEBUGGER_FILE_OPEN:                 sResult=QString("Shortcuts/Debugger/File/Open");                break;
        case ID_DEBUGGER_FILE_CLOSE:                sResult=QString("Shortcuts/Debugger/File/Close");               break;
        case ID_DEBUGGER_FILE_EXIT:                 sResult=QString("Shortcuts/Debugger/File/Exit");                break;
        case ID_DEBUGGER_VIEW_CPU:                  sResult=QString("Shortcuts/Debugger/View/CPU");                 break;
        case ID_DEBUGGER_VIEW_ACTIONS:              sResult=QString("Shortcuts/Debugger/View/Actions");             break;
        case ID_DEBUGGER_VIEW_LOG:                  sResult=QString("Shortcuts/Debugger/View/Log");                 break;
        case ID_DEBUGGER_VIEW_BREAKPOINTS:          sResult=QString("Shortcuts/Debugger/View/Breakpoints");         break;
        case ID_DEBUGGER_VIEW_MEMORYMAP:            sResult=QString("Shortcuts/Debugger/View/MemoryMap");           break;
        case ID_DEBUGGER_VIEW_CALLSTACK:            sResult=QString("Shortcuts/Debugger/View/CallStack");           break;
        case ID_DEBUGGER_VIEW_THREADS:              sResult=QString("Shortcuts/Debugger/View/Threads");             break;
        case ID_DEBUGGER_VIEW_HANDLES:              sResult=QString("Shortcuts/Debugger/View/Handles");             break;
        case ID_DEBUGGER_DEBUG_RUN:                 sResult=QString("Shortcuts/Debugger/Debug/Run");                break;
        case ID_DEBUGGER_DEBUG_PAUSE:               sResult=QString("Shortcuts/Debugger/Debug/Pause");              break;
        case ID_DEBUGGER_DEBUG_STEPINTO:            sResult=QString("Shortcuts/Debugger/Debug/StepInto");           break;
        case ID_DEBUGGER_DEBUG_STEPOVER:            sResult=QString("Shortcuts/Debugger/Debug/StepOver");           break;
        case ID_DEBUGGER_DEBUG_STOP:                sResult=QString("Shortcuts/Debugger/Debug/Stop");               break;
        case ID_DEBUGGER_DEBUG_RESTART:             sResult=QString("Shortcuts/Debugger/Debug/Restart");            break;
        case ID_DEBUGGER_FILE_ATTACH:               sResult=QString("Shortcuts/Debugger/File/Attach");              break;
        case ID_DEBUGGER_FILE_DETACH:               sResult=QString("Shortcuts/Debugger/File/Detach");              break;
        case ID_DEBUGGER_DISASM_TOGGLE:             sResult=QString("Shortcuts/Debugger/Disasm/Toggle");            break;
        case ID_DEBUGGER_DISASM_DUMPTOFILE:         sResult=QString("Shortcuts/Debugger/Disasm/DumpToFile");        break;
        case ID_DEBUGGER_DISASM_GOTOADDRESS:        sResult=QString("Shortcuts/Debugger/Disasm/GoToAddress");       break;
        case ID_DEBUGGER_DISASM_HEXSIGNATURE:       sResult=QString("Shortcuts/Debugger/Disasm/HexSignature");      break;
        case ID_DEBUGGER_DISASM_SIGNATURE:          sResult=QString("Shortcuts/Debugger/Disasm/Signature");         break;
        case ID_DEBUGGER_DISASM_FIND:               sResult=QString("Shortcuts/Debugger/Disasm/Find");              break;
        case ID_DEBUGGER_DISASM_FINDNEXT:           sResult=QString("Shortcuts/Debugger/Disasm/FindNext");          break;
        case ID_DEBUGGER_DISASM_COPYASHEX:          sResult=QString("Shortcuts/Debugger/Disasm/CopyAsHex");         break;
        case ID_DEBUGGER_DISASM_COPYCURSORADDRESS:  sResult=QString("Shortcuts/Debugger/Disasm/CopyCursorAddress"); break;
        case ID_DEBUGGER_DISASM_SELECTALL:          sResult=QString("Shortcuts/Debugger/Disasm/SelectAll");         break;
        case ID_DEBUGGER_HEX_DUMPTOFILE:            sResult=QString("Shortcuts/Debugger/Hex/DumpToFile");           break;
        case ID_DEBUGGER_HEX_FIND:                  sResult=QString("Shortcuts/Debugger/Hex/Find");                 break;
        case ID_DEBUGGER_HEX_FINDNEXT:              sResult=QString("Shortcuts/Debugger/Hex/FindNext");             break;
        case ID_DEBUGGER_HEX_GOTOADDRESS:           sResult=QString("Shortcuts/Debugger/Hex/GoToAddress");          break;
        case ID_DEBUGGER_HEX_SIGNATURE:             sResult=QString("Shortcuts/Debugger/Hex/Signature");            break;
        case ID_DEBUGGER_HEX_COPYASHEX:             sResult=QString("Shortcuts/Debugger/Hex/CopyAsHex");            break;
        case ID_DEBUGGER_HEX_COPYCURSORADDRESS:     sResult=QString("Shortcuts/Debugger/Hex/CopyCursorAddress");    break;
        case ID_DEBUGGER_HEX_SELECTALL:             sResult=QString("Shortcuts/Debugger/Hex/SelectAll");            break;
        case ID_DEBUGGER_STACK_GOTOADDRESS:         sResult=QString("Shortcuts/Debugger/Stack/GoToAddress");        break;
        case ID_ARCHIVE_COPYFILENAME:               sResult=QString("Shortcuts/Archive/CopyFilename");              break;
        case ID_ARCHIVE_DUMPTOFILE:                 sResult=QString("Shortcuts/Archive/DumpToFile");                break;
        case ID_ARCHIVE_ENTROPY:                    sResult=QString("Shortcuts/Archive/Entropy");                   break;
        case ID_ARCHIVE_HASH:                       sResult=QString("Shortcuts/Archive/Hash");                      break;
        case ID_ARCHIVE_HEX:                        sResult=QString("Shortcuts/Archive/Hex");                       break;
        case ID_ARCHIVE_OPEN:                       sResult=QString("Shortcuts/Archive/Open");                      break;
        case ID_ARCHIVE_SCAN:                       sResult=QString("Shortcuts/Archive/Scan");                      break;
        case ID_ARCHIVE_STRINGS:                    sResult=QString("Shortcuts/Archive/Strings");                   break;
        case ID_TABLE_HEX:                          sResult=QString("Shortcuts/Table/Hex");                         break;
        case ID_TABLE_DISASM:                       sResult=QString("Shortcuts/Table/Disasm");                      break;
        case ID_PROCESS_STRUCTS:                    sResult=QString("Shortcuts/Process/Structs");                   break;
        case ID_PROCESS_DUMPTOFILE:                 sResult=QString("Shortcuts/Process/DumpToFile");                break;
        case ID_PROCESS_MEMORY_HEX:                 sResult=QString("Shortcuts/Process/Memory/Hex");                break;
        case ID_PROCESS_MEMORY_STRINGS:             sResult=QString("Shortcuts/Process/Memory/Strings");            break;
        case ID_PROCESS_MEMORY_SIGNATURES:          sResult=QString("Shortcuts/Process/Memory/Signatures");         break;
        case ID_PROCESS_FILE_VIEWER:                sResult=QString("Shortcuts/Process/File/Viewer");               break;
        case ID_PROCESS_FILE_COPYFILENAME:          sResult=QString("Shortcuts/Process/File/CopyFilename");         break;
        default:
        {
        #ifdef QT_DEBUG
            qDebug("UNKNOWN SHORTCUT!!!");
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
        case ID_DEBUGGER_FILE_OPEN:
        case ID_ARCHIVE_OPEN:
        case ID_FILE_OPEN:
            sResult=tr("Open");
            break;
        case ID_FILE_SAVE:
            sResult=tr("Save");
            break;
        case ID_FILE_SAVEAS:
            sResult=tr("Save As");
            break;
        case ID_FILE_CLOSE:
        case ID_DEBUGGER_FILE_CLOSE:
            sResult=tr("Close");
            break;
        case ID_FILE_PRINT:
            sResult=tr("Print");
            break;
        case ID_FILE_EXIT:
        case ID_DEBUGGER_FILE_EXIT:
            sResult=tr("Exit");
            break;
        case ID_ACTION_COPY:
            sResult=tr("Copy");
            break;
        case ID_STRINGS_COPYSTRING:
            sResult=tr("Copy string");
            break;
        case ID_STRINGS_COPYOFFSET:
            sResult=tr("Copy offset");
            break;
        case ID_STRINGS_COPYSIZE:
            sResult=tr("Copy size");
            break;
        case ID_STRINGS_HEX:
            sResult=tr("Hex");
            break;
        case ID_STRINGS_DEMANGLE:
            sResult=tr("Demangle");
            break;
        case ID_SIGNATURES_COPYNAME:
            sResult=tr("Copy name");
            break;
        case ID_SIGNATURES_COPYSIGNATURE:
            sResult=tr("Copy signature");
            break;
        case ID_SIGNATURES_COPYADDRESS:
            sResult=tr("Copy address");
            break;
        case ID_SIGNATURES_COPYOFFSET:
            sResult=tr("Copy offset");
            break;
        case ID_SIGNATURES_COPYSIZE:
            sResult=tr("Copy size");
            break;
        case ID_TABLE_HEX:
        case ID_DISASM_HEX:
        case ID_SIGNATURES_HEX:
        case ID_ARCHIVE_HEX:
        case ID_PROCESS_MEMORY_HEX:
            sResult=tr("Hex");
            break;
        case ID_HEX_DUMPTOFILE:
        case ID_DEBUGGER_HEX_DUMPTOFILE:
        case ID_DEBUGGER_DISASM_DUMPTOFILE:
        case ID_ARCHIVE_DUMPTOFILE:
        case ID_DISASM_DUMPTOFILE:
        case ID_PROCESS_DUMPTOFILE:
            sResult=tr("Dump to file");
            break;
        case ID_DISASM_GOTOADDRESS:
        case ID_DEBUGGER_HEX_GOTOADDRESS:
        case ID_DEBUGGER_DISASM_GOTOADDRESS:
        case ID_DEBUGGER_STACK_GOTOADDRESS:
        case ID_HEX_GOTOADDRESS:
            sResult=tr("Go to address");
            break;
        case ID_DISASM_GOTOOFFSET:
        case ID_HEX_GOTOOFFSET:
            sResult=tr("Go to offset");
            break;
        case ID_DEBUGGER_DISASM_SIGNATURE:
        case ID_DEBUGGER_HEX_SIGNATURE:
        case ID_DISASM_SIGNATURE:
        case ID_HEX_SIGNATURE:
            sResult=tr("Signature");
            break;
        case ID_PROCESS_MEMORY_SIGNATURES:
            sResult=tr("Signatures");
            break;
        case ID_DISASM_FIND:
        case ID_DEBUGGER_DISASM_FIND:
        case ID_DEBUGGER_HEX_FIND:
        case ID_HEX_FIND:
            sResult=tr("Find");
            break;
        case ID_DEBUGGER_DISASM_FINDNEXT:
        case ID_DEBUGGER_HEX_FINDNEXT:
        case ID_HEX_FINDNEXT:
        case ID_DISASM_FINDNEXT:
            sResult=tr("Find next");
            break;
        case ID_DISASM_SELECTALL:
        case ID_HEX_SELECTALL:
        case ID_DEBUGGER_DISASM_SELECTALL:
        case ID_DEBUGGER_HEX_SELECTALL:
            sResult=tr("Select all");
            break;
        case ID_DISASM_COPYASHEX:
        case ID_HEX_COPYASHEX:
        case ID_DEBUGGER_DISASM_COPYASHEX:
        case ID_DEBUGGER_HEX_COPYASHEX:
            sResult=tr("Copy as hex");
            break;
        case ID_DISASM_COPYCURSOROFFSET:
        case ID_HEX_COPYCURSOROFFSET:
            sResult=tr("Copy cursor offset");
            break;
        case ID_DISASM_COPYCURSORADDRESS:
        case ID_HEX_COPYCURSORADDRESS:
        case ID_DEBUGGER_DISASM_COPYCURSORADDRESS:
        case ID_DEBUGGER_HEX_COPYCURSORADDRESS:
            sResult=tr("Copy cursor address");
            break;
        case ID_TABLE_DISASM:
        case ID_HEX_DISASM:
            sResult=tr("Disasm");
            break;
        case ID_DEBUGGER_VIEW_MEMORYMAP:
        case ID_HEX_MEMORYMAP:
            sResult=tr("Memory map");
            break;
        case ID_DISASM_GOTOENTRYPOINT:
            sResult=tr("Go to entry point");
            break;
        case ID_DEBUGGER_DISASM_HEXSIGNATURE:
        case ID_DISASM_HEXSIGNATURE:
            sResult=tr("Hex signature");
            break;
        case ID_DEBUGGER_FILE_ATTACH:
            sResult=tr("Attach");
            break;
        case ID_DEBUGGER_FILE_DETACH:
            sResult=tr("Detach");
            break;
        case ID_DEBUGGER_VIEW_CPU:
            sResult=tr("CPU");
            break;
        case ID_DEBUGGER_VIEW_ACTIONS:
            sResult=tr("Actions");
            break;
        case ID_DEBUGGER_VIEW_LOG:
            sResult=tr("Log");
            break;
        case ID_DEBUGGER_VIEW_BREAKPOINTS:
            sResult=tr("Breakpoints");
            break;
        case ID_DEBUGGER_VIEW_CALLSTACK:
            sResult=tr("Call stack");
            break;
        case ID_DEBUGGER_VIEW_THREADS:
            sResult=tr("Threads");
            break;
        case ID_DEBUGGER_VIEW_HANDLES:
            sResult=tr("Handles");
            break;
        case ID_DEBUGGER_DEBUG_RUN:
            sResult=tr("Run");
            break;
        case ID_DEBUGGER_DEBUG_PAUSE:
            sResult=tr("Pause");
            break;
        case ID_DEBUGGER_DEBUG_STEPINTO:
            sResult=tr("Step into");
            break;
        case ID_DEBUGGER_DEBUG_STEPOVER:
            sResult=tr("Step over");
            break;
        case ID_DEBUGGER_DEBUG_STOP:
            sResult=tr("Stop");
            break;
        case ID_DEBUGGER_DEBUG_RESTART:
            sResult=tr("Restart");
            break;
        case ID_DEBUGGER_DISASM_TOGGLE:
            sResult=tr("Toggle");
            break;
        case ID_ARCHIVE_COPYFILENAME:
        case ID_PROCESS_FILE_COPYFILENAME:
            sResult=tr("Copy filename");
            break;
        case ID_ARCHIVE_ENTROPY:
            sResult=tr("Entropy");
            break;
        case ID_ARCHIVE_HASH:
            sResult=tr("Hash");
            break;
        case ID_ARCHIVE_SCAN:
            sResult=tr("Scan");
            break;
        case ID_ARCHIVE_STRINGS:
        case ID_PROCESS_MEMORY_STRINGS:
            sResult=tr("Strings");
            break;
        case ID_PROCESS_STRUCTS:
            sResult=tr("Structs");
            break;
        case ID_PROCESS_FILE_VIEWER:
            sResult=tr("Viewer");
            break;
        default:
            sResult=tr("Unknown");
    }

    return sResult;
}

QKeySequence XShortcuts::getDefault(XShortcuts::ID id)
{
    QKeySequence ksResult=QKeySequence();

    switch(id)
    {
        case ID_ACTION_COPY:
            ksResult=QKeySequence::Copy;
            break;
        case ID_FILE_OPEN:
            ksResult=QKeySequence();
            break;
        case ID_FILE_SAVE:
            ksResult=QKeySequence();
            break;
        case ID_FILE_SAVEAS:
            ksResult=QKeySequence();
            break;
        case ID_FILE_CLOSE:
            ksResult=QKeySequence();
            break;
        case ID_FILE_PRINT:
            ksResult=QKeySequence();
            break;
        case ID_FILE_EXIT:
            ksResult=QKeySequence();
            break;
        case ID_STRINGS_COPYSTRING:
            ksResult=QKeySequence::Copy;
            break;
        case ID_STRINGS_COPYOFFSET:
            ksResult=QKeySequence();
            break;
        case ID_STRINGS_COPYSIZE:
            ksResult=QKeySequence();
            break;
        case ID_STRINGS_HEX:
            ksResult=QKeySequence();
            break;
        case ID_STRINGS_DEMANGLE:
            ksResult=QKeySequence();
            break;
        case ID_SIGNATURES_COPYNAME:
            ksResult=QKeySequence::Copy;
            break;
        case ID_SIGNATURES_COPYSIGNATURE:
            ksResult=QKeySequence();
            break;
        case ID_SIGNATURES_COPYADDRESS:
            ksResult=QKeySequence();
            break;
        case ID_SIGNATURES_COPYOFFSET:
            ksResult=QKeySequence();
            break;
        case ID_SIGNATURES_COPYSIZE:
            ksResult=QKeySequence();
            break;
        case ID_SIGNATURES_HEX:
            ksResult=QKeySequence();
            break;
        case ID_HEX_DUMPTOFILE:
            ksResult=Qt::CTRL+Qt::Key_D;
            break;
        case ID_HEX_GOTOADDRESS:
            ksResult=Qt::CTRL+Qt::Key_G;
            break;
        case ID_HEX_GOTOOFFSET:
            ksResult=QKeySequence();
            break;
        case ID_HEX_SIGNATURE:
            ksResult=Qt::Key_S;
            break;
        case ID_HEX_FIND:
            ksResult=QKeySequence::Find;
            break;
        case ID_HEX_FINDNEXT:
            ksResult=QKeySequence::FindNext;
            break;
        case ID_HEX_SELECTALL:
            ksResult=QKeySequence::SelectAll;
            break;
        case ID_HEX_COPYASHEX:
            ksResult=QKeySequence::Copy;
            break;
        case ID_HEX_COPYCURSOROFFSET:
            ksResult=QKeySequence();
            break;
        case ID_HEX_COPYCURSORADDRESS:
            ksResult=QKeySequence();
            break;
        case ID_HEX_DISASM:
            ksResult=QKeySequence();
            break;
        case ID_HEX_MEMORYMAP:
            ksResult=QKeySequence();
            break;
        case ID_DISASM_DUMPTOFILE:
            ksResult=Qt::CTRL+Qt::Key_D;
            break;
        case ID_DISASM_GOTOADDRESS:
            ksResult=Qt::CTRL+Qt::Key_G;
            break;
        case ID_DISASM_GOTOOFFSET:
            ksResult=QKeySequence();
            break;
        case ID_DISASM_GOTOENTRYPOINT:
            ksResult=QKeySequence();
            break;
        case ID_DISASM_HEXSIGNATURE:
            ksResult=Qt::Key_S;
            break;
        case ID_DISASM_SIGNATURE:
            ksResult=Qt::SHIFT+Qt::Key_G;
            break;
        case ID_DISASM_FIND:
            ksResult=QKeySequence::Find;
            break;
        case ID_DISASM_FINDNEXT:
            ksResult=QKeySequence::FindNext;
            break;
        case ID_DISASM_SELECTALL:
            ksResult=QKeySequence::SelectAll;
            break;
        case ID_DISASM_COPYASHEX:
            ksResult=QKeySequence::Copy;
            break;
        case ID_DISASM_COPYCURSORADDRESS:
            ksResult=QKeySequence();
            break;
        case ID_DISASM_COPYCURSOROFFSET:
            ksResult=QKeySequence();
            break;
        case ID_DISASM_HEX:
            ksResult=QKeySequence();
            break;
        case ID_DEBUGGER_FILE_OPEN:
        #ifdef Q_OS_WIN
            ksResult=Qt::Key_F3;
        #endif
        #ifdef Q_OS_LINUX
            ksResult=QKeySequence(); // TODO
        #endif
        #ifdef Q_OS_OSX
            ksResult=Qt::CTRL+Qt::Key_O;
        #endif
            break;
        case ID_DEBUGGER_FILE_CLOSE:
            ksResult=QKeySequence();
            break;
        case ID_DEBUGGER_DEBUG_PAUSE:
            ksResult=Qt::Key_F12;
            break;
        case ID_DEBUGGER_FILE_EXIT:
            ksResult=Qt::ALT+Qt::Key_X;
            break;
        case ID_DEBUGGER_DEBUG_RUN:
            ksResult=Qt::Key_F9;
            break;
        case ID_DEBUGGER_DEBUG_STEPINTO:
            ksResult=Qt::Key_F7;
            break;
        case ID_DEBUGGER_DEBUG_STEPOVER:
            ksResult=Qt::Key_F8;
            break;
        case ID_DEBUGGER_DEBUG_STOP:
            ksResult=QKeySequence();
            break;
        case ID_DEBUGGER_DEBUG_RESTART:
            ksResult=QKeySequence();
            break;
        case ID_DEBUGGER_FILE_ATTACH:
        #ifdef Q_OS_WIN
            ksResult=Qt::ALT+Qt::Key_A;
        #endif
        #ifdef Q_OS_LINUX
            ksResult=QKeySequence(); // TODO
        #endif
        #ifdef Q_OS_OSX
            ksResult=QKeySequence(); // TODO
        #endif
            break;
        case ID_DEBUGGER_FILE_DETACH:
        #ifdef Q_OS_WIN
            ksResult=Qt::CTRL+Qt::ALT+Qt::Key_F2;
        #endif
        #ifdef Q_OS_LINUX
            ksResult=QKeySequence(); // TODO
        #endif
        #ifdef Q_OS_OSX
            ksResult=QKeySequence(); // TODO
        #endif
            break;
        case ID_DEBUGGER_DISASM_TOGGLE:
            ksResult=Qt::Key_F2;
            break;
        case ID_DEBUGGER_DISASM_DUMPTOFILE:
            ksResult=QKeySequence();
            break;
        case ID_DEBUGGER_DISASM_GOTOADDRESS:
            ksResult=QKeySequence();
            break;
        case ID_DEBUGGER_DISASM_HEXSIGNATURE:
            ksResult=QKeySequence();
            break;
        case ID_DEBUGGER_DISASM_SIGNATURE:
            ksResult=QKeySequence();
            break;
        case ID_DEBUGGER_DISASM_FIND:
            ksResult=QKeySequence();
            break;
        case ID_DEBUGGER_DISASM_FINDNEXT:
            ksResult=QKeySequence();
            break;
        case ID_DEBUGGER_DISASM_COPYASHEX:
            ksResult=QKeySequence();
            break;
        case ID_DEBUGGER_DISASM_COPYCURSORADDRESS:
            ksResult=QKeySequence();
            break;
        case ID_DEBUGGER_DISASM_SELECTALL:
            ksResult=QKeySequence();
            break;
        case ID_DEBUGGER_HEX_DUMPTOFILE:
            ksResult=QKeySequence();
            break;
        case ID_DEBUGGER_HEX_FIND:
            ksResult=QKeySequence();
            break;
        case ID_DEBUGGER_HEX_FINDNEXT:
            ksResult=QKeySequence();
            break;
        case ID_DEBUGGER_HEX_GOTOADDRESS:
            ksResult=QKeySequence();
            break;
        case ID_DEBUGGER_HEX_SIGNATURE:
            ksResult=QKeySequence();
            break;
        case ID_DEBUGGER_HEX_COPYASHEX:
            ksResult=QKeySequence();
            break;
        case ID_DEBUGGER_HEX_COPYCURSORADDRESS:
            ksResult=QKeySequence();
            break;
        case ID_DEBUGGER_HEX_SELECTALL:
            ksResult=QKeySequence();
            break;
        case ID_DEBUGGER_STACK_GOTOADDRESS:
            ksResult=QKeySequence();
            break;
        case ID_ARCHIVE_COPYFILENAME:
            ksResult=QKeySequence::Copy;
            break;
        case ID_ARCHIVE_DUMPTOFILE:
            ksResult=Qt::CTRL+Qt::Key_D;
            break;
        case ID_ARCHIVE_ENTROPY:
            ksResult=QKeySequence();
            break;
        case ID_ARCHIVE_HASH:
            ksResult=QKeySequence();
            break;
        case ID_ARCHIVE_HEX:
            ksResult=QKeySequence();
            break;
        case ID_ARCHIVE_OPEN:
            ksResult=QKeySequence();
            break;
        case ID_ARCHIVE_SCAN:
            ksResult=QKeySequence();
            break;
        case ID_ARCHIVE_STRINGS:
            ksResult=QKeySequence();
            break;
        case ID_TABLE_HEX:
            ksResult=QKeySequence();
            break;
        case ID_TABLE_DISASM:
            ksResult=QKeySequence();
            break;
        case ID_PROCESS_STRUCTS:
            ksResult=Qt::ALT+Qt::Key_S;
            break;
        case ID_PROCESS_DUMPTOFILE:
            ksResult=QKeySequence();
            break;
        case ID_PROCESS_MEMORY_HEX:
            ksResult=QKeySequence();
            break;
        case ID_PROCESS_MEMORY_STRINGS:
            ksResult=QKeySequence();
            break;
        case ID_PROCESS_MEMORY_SIGNATURES:
            ksResult=QKeySequence();
            break;
        case ID_PROCESS_FILE_VIEWER:
            ksResult=QKeySequence();
            break;
        case ID_PROCESS_FILE_COPYFILENAME:
            ksResult=QKeySequence();
            break;
        default:
            ksResult=QKeySequence();
    }

    return ksResult;
}

QString XShortcuts::groupIdToString(GROUPID groupId)
{
    QString sResult="";

    if      (groupId==GROUPID_ACTION)       sResult=tr("Action");
    else if (groupId==GROUPID_FILE)         sResult=tr("File");
    else if (groupId==GROUPID_VIEW)         sResult=tr("View");
    else if (groupId==GROUPID_STRINGS)      sResult=tr("Strings");
    else if (groupId==GROUPID_SIGNATURES)   sResult=tr("Signatures");
    else if (groupId==GROUPID_HEX)          sResult=tr("Hex");
    else if (groupId==GROUPID_DISASM)       sResult=tr("Disasm");
    else if (groupId==GROUPID_DEBUG)        sResult=tr("Debug");
    else if (groupId==GROUPID_DEBUGGER)     sResult=tr("Debugger");
    else if (groupId==GROUPID_REGISTERS)    sResult=tr("Registers");
    else if (groupId==GROUPID_STACK)        sResult=tr("Stack");
    else if (groupId==GROUPID_ARCHIVE)      sResult=tr("Archive");
    else if (groupId==GROUPID_TABLE)        sResult=tr("Table");
    else if (groupId==GROUPID_PROCESS)      sResult=tr("Process");
    else if (groupId==GROUPID_MEMORY)       sResult=tr("Memory");

    return sResult;
}

XShortcuts::ID XShortcuts::getGroupEnd(GROUPID groupId)
{
    int nEnd=0;

    // TODO STACK
    if(groupId==GROUPID_ACTION)         nEnd=ID_ACTION__END;
    if(groupId==GROUPID_STRINGS)        nEnd=ID_STRINGS__END;
    if(groupId==GROUPID_SIGNATURES)     nEnd=ID_SIGNATURES__END;
    if(groupId==GROUPID_HEX)            nEnd=ID_HEX__END;
    if(groupId==GROUPID_DISASM)         nEnd=ID_DISASM__END;
    if(groupId==GROUPID_DEBUGGER)       nEnd=ID_DEBUGGER__END;
    if(groupId==GROUPID_ARCHIVE)        nEnd=ID_ARCHIVE__END;
    if(groupId==GROUPID_TABLE)          nEnd=ID_TABLE__END;
    if(groupId==GROUPID_PROCESS)        nEnd=ID_PROCESS__END;

    return (ID)nEnd;
}

XShortcuts::GROUPID XShortcuts::getGroupId(XShortcuts::ID id)
{
    qint32 nResult=id;

    nResult&=0xFF000000;

    nResult>>=24;

    return (GROUPID)nResult;
}

XShortcuts::GROUPID XShortcuts::getSubgroupId(ID id)
{
    GROUPID result=GROUPID_UNKNOWN;

    switch(id)
    {
        case ID_DEBUGGER_FILE_ATTACH:
        case ID_DEBUGGER_FILE_CLOSE:
        case ID_DEBUGGER_FILE_DETACH:
        case ID_DEBUGGER_FILE_EXIT:
        case ID_DEBUGGER_FILE_OPEN:
        case ID_PROCESS_FILE_VIEWER:
        case ID_PROCESS_FILE_COPYFILENAME:
            result=GROUPID_FILE;
            break;
        case ID_DEBUGGER_DEBUG_PAUSE:
        case ID_DEBUGGER_DEBUG_RESTART:
        case ID_DEBUGGER_DEBUG_RUN:
        case ID_DEBUGGER_DEBUG_STEPINTO:
        case ID_DEBUGGER_DEBUG_STEPOVER:
        case ID_DEBUGGER_DEBUG_STOP:
            result=GROUPID_DEBUG;
            break;
        case ID_DEBUGGER_VIEW_ACTIONS:
        case ID_DEBUGGER_VIEW_BREAKPOINTS:
        case ID_DEBUGGER_VIEW_CALLSTACK:
        case ID_DEBUGGER_VIEW_CPU:
        case ID_DEBUGGER_VIEW_HANDLES:
        case ID_DEBUGGER_VIEW_LOG:
        case ID_DEBUGGER_VIEW_MEMORYMAP:
        case ID_DEBUGGER_VIEW_THREADS:
            result=GROUPID_VIEW;
            break;
        case ID_DEBUGGER_DISASM_TOGGLE:
        case ID_DEBUGGER_DISASM_COPYASHEX:
        case ID_DEBUGGER_DISASM_COPYCURSORADDRESS:
        case ID_DEBUGGER_DISASM_DUMPTOFILE:
        case ID_DEBUGGER_DISASM_FIND:
        case ID_DEBUGGER_DISASM_FINDNEXT:
        case ID_DEBUGGER_DISASM_GOTOADDRESS:
        case ID_DEBUGGER_DISASM_HEXSIGNATURE:
        case ID_DEBUGGER_DISASM_SELECTALL:
        case ID_DEBUGGER_DISASM_SIGNATURE:
            result=GROUPID_DISASM;
            break;
        case ID_DEBUGGER_HEX_DUMPTOFILE:
        case ID_DEBUGGER_HEX_FIND:
        case ID_DEBUGGER_HEX_FINDNEXT:
        case ID_DEBUGGER_HEX_GOTOADDRESS:
        case ID_DEBUGGER_HEX_SIGNATURE:
        case ID_DEBUGGER_HEX_COPYASHEX:
        case ID_DEBUGGER_HEX_COPYCURSORADDRESS:
        case ID_DEBUGGER_HEX_SELECTALL:
            result=GROUPID_HEX;
            break;
        case ID_DEBUGGER_STACK_GOTOADDRESS:
            result=GROUPID_STACK;
            break;
        case ID_PROCESS_MEMORY_HEX:
        case ID_PROCESS_MEMORY_SIGNATURES:
        case ID_PROCESS_MEMORY_STRINGS:
            result=GROUPID_MEMORY;
            break;
        default:
            result=GROUPID_UNKNOWN;
    }

    return result;
}
