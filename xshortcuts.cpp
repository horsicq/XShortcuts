/* Copyright (c) 2021-2022 hors<horsicq@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "xshortcuts.h"

XShortcuts::XShortcuts(QObject *pParent) : QObject(pParent)
{
    g_bIsNative=false;
}

void XShortcuts::setName(QString sValue)
{
    // mb TODO different names for Windows and macOS
    // TODO Check
    this->g_sName=sValue;
}

void XShortcuts::setNative(bool bValue)
{
    g_bIsNative=bValue;
}

void XShortcuts::addGroup(GROUPID groupId)
{
    if(groupId==GROUPID_FILE)
    {
        addId(X_ID_FILE_OPEN);
        addId(X_ID_FILE_SAVE);
        addId(X_ID_FILE_SAVEAS);
        addId(X_ID_FILE_CLOSE);
        addId(X_ID_FILE_PRINT);
        addId(X_ID_FILE_EXIT);
    }
    else if(groupId==GROUPID_VIEW)
    {

    }
    else if(groupId==GROUPID_DEBUGGER)
    {
        addId(X_ID_DEBUGGER_FILE_OPEN);
        addId(X_ID_DEBUGGER_FILE_CLOSE);
        addId(X_ID_DEBUGGER_FILE_ATTACH);
        addId(X_ID_DEBUGGER_FILE_DETACH);
        addId(X_ID_DEBUGGER_FILE_EXIT);
        addId(X_ID_DEBUGGER_VIEW_CPU);
        addId(X_ID_DEBUGGER_VIEW_LOG);
        addId(X_ID_DEBUGGER_VIEW_BREAKPOINTS);
        addId(X_ID_DEBUGGER_VIEW_MEMORYMAP);
        addId(X_ID_DEBUGGER_VIEW_CALLSTACK);
        addId(X_ID_DEBUGGER_VIEW_THREADS);
        addId(X_ID_DEBUGGER_VIEW_HANDLES);
        addId(X_ID_DEBUGGER_VIEW_MODULES);
        addId(X_ID_DEBUGGER_VIEW_SYMBOLS);
        addId(X_ID_DEBUGGER_TOOLS_SHORTCUTS);
        addId(X_ID_DEBUGGER_TOOLS_OPTIONS);
        addId(X_ID_DEBUGGER_HELP_ABOUT);
        addId(X_ID_DEBUGGER_DEBUG_RUN);
        addId(X_ID_DEBUGGER_DEBUG_PAUSE);
        addId(X_ID_DEBUGGER_DEBUG_STEPINTO);
        addId(X_ID_DEBUGGER_DEBUG_STEPOVER);
        addId(X_ID_DEBUGGER_DEBUG_STOP);
        addId(X_ID_DEBUGGER_DEBUG_RESTART);
        addId(X_ID_DEBUGGER_DISASM_BREAKPOINT_TOGGLE);
        addId(X_ID_DEBUGGER_DISASM_DUMPTOFILE);
        addId(X_ID_DEBUGGER_DISASM_GOTO_ADDRESS);
        addId(X_ID_DEBUGGER_DISASM_HEX_SIGNATURE);
        addId(X_ID_DEBUGGER_DISASM_SIGNATURE);
        addId(X_ID_DEBUGGER_DISASM_FIND_STRING);
        addId(X_ID_DEBUGGER_DISASM_FIND_VALUE);
        addId(X_ID_DEBUGGER_DISASM_FIND_SIGNATURE);
        addId(X_ID_DEBUGGER_DISASM_FIND_NEXT);
        addId(X_ID_DEBUGGER_DISASM_COPY_HEX);
        addId(X_ID_DEBUGGER_DISASM_COPY_ADDRESS);
        addId(X_ID_DEBUGGER_DISASM_SELECT_ALL);
        addId(X_ID_DEBUGGER_DISASM_EDIT_HEX);
        addId(X_ID_DEBUGGER_HEX_DUMPTOFILE);
        addId(X_ID_DEBUGGER_HEX_FIND_STRING);
        addId(X_ID_DEBUGGER_HEX_FIND_VALUE);
        addId(X_ID_DEBUGGER_HEX_FIND_SIGNATURE);
        addId(X_ID_DEBUGGER_HEX_FIND_NEXT);
        addId(X_ID_DEBUGGER_HEX_GOTO_ADDRESS);
        addId(X_ID_DEBUGGER_HEX_SIGNATURE);
        addId(X_ID_DEBUGGER_HEX_COPY_HEX);
        addId(X_ID_DEBUGGER_HEX_COPY_ADDRESS);
        addId(X_ID_DEBUGGER_HEX_SELECT_ALL);
        addId(X_ID_DEBUGGER_HEX_EDIT_HEX);
        addId(X_ID_DEBUGGER_STACK_GOTO_ADDRESS);
        addId(X_ID_DEBUGGER_STACK_EDIT_HEX);
    }
    else if(groupId==GROUPID_DEBUG)
    {

    }
    else if(groupId==GROUPID_ACTION)
    {
        addId(createShortcutsId(groupId,QList<GROUPID>(),BASEID_COPY));
        addId(createShortcutsId(groupId,QList<GROUPID>(),BASEID_SHOW));
    }
    else if(groupId==GROUPID_STRINGS)
    {
        addId(X_ID_STRINGS_COPY_STRING);
        addId(X_ID_STRINGS_COPY_OFFSET);
        addId(X_ID_STRINGS_COPY_SIZE);
        addId(X_ID_STRINGS_FOLLOWIN_HEX);
        addId(X_ID_STRINGS_DEMANGLE);
        addId(X_ID_STRINGS_EDIT_STRING);
    }
    else if(groupId==GROUPID_SIGNATURES)
    {
        addId(X_ID_SIGNATURES_COPY_NAME);
        addId(X_ID_SIGNATURES_COPY_SIGNATURE);
        addId(X_ID_SIGNATURES_COPY_ADDRESS);
        addId(X_ID_SIGNATURES_COPY_OFFSET);
        addId(X_ID_SIGNATURES_FOLLOWIN_HEX);
    }
    else if(groupId==GROUPID_STRUCT)
    {

    }
    else if(groupId==GROUPID_HEX)
    {
        addId(X_ID_HEX_DUMPTOFILE);
        addId(X_ID_HEX_GOTO_OFFSET);
        addId(X_ID_HEX_GOTO_ADDRESS);
        addId(X_ID_HEX_SIGNATURE);
        addId(X_ID_HEX_FIND_STRING);
        addId(X_ID_HEX_FIND_SIGNATURE);
        addId(X_ID_HEX_FIND_VALUE);
        addId(X_ID_HEX_FIND_NEXT);
        addId(X_ID_HEX_SELECT_ALL);
        addId(X_ID_HEX_COPY_HEX);
        addId(X_ID_HEX_COPY_OFFSET);
        addId(X_ID_HEX_COPY_ADDRESS);
        addId(X_ID_HEX_FOLLOWIN_DISASM);
        addId(X_ID_HEX_FOLLOWIN_MEMORYMAP);
        addId(X_ID_HEX_EDIT_HEX);
    }
    else if(groupId==GROUPID_DISASM)
    { 
        addId(X_ID_DISASM_DUMPTOFILE);
        addId(X_ID_DISASM_GOTO_OFFSET);
        addId(X_ID_DISASM_GOTO_ADDRESS);
        addId(X_ID_DISASM_GOTO_ENTRYPOINT);
        addId(X_ID_DISASM_SIGNATURE);
        addId(X_ID_DISASM_HEX_SIGNATURE);
        addId(X_ID_DISASM_FIND_STRING);
        addId(X_ID_DISASM_FIND_SIGNATURE);
        addId(X_ID_DISASM_FIND_VALUE);
        addId(X_ID_DISASM_FIND_NEXT);
        addId(X_ID_DISASM_SELECT_ALL);
        addId(X_ID_DISASM_COPY_HEX);
        addId(X_ID_DISASM_COPY_OFFSET);
        addId(X_ID_DISASM_COPY_ADDRESS);
        addId(X_ID_DISASM_FOLLOWIN_HEX);
        addId(X_ID_DISASM_EDIT_HEX);
    }
    else if(groupId==GROUPID_STACK)
    {

    }
    else if(groupId==GROUPID_REGISTERS)
    {

    }
    else if(groupId==GROUPID_ARCHIVE)
    {
        addId(X_ID_ARCHIVE_OPEN);
        addId(X_ID_ARCHIVE_SCAN);
        addId(X_ID_ARCHIVE_HEX);
        addId(X_ID_ARCHIVE_STRINGS);
        addId(X_ID_ARCHIVE_ENTROPY);
        addId(X_ID_ARCHIVE_HASH);
        addId(X_ID_ARCHIVE_COPY_FILENAME);
        addId(X_ID_ARCHIVE_DUMPTOFILE);
    }
    else if(groupId==GROUPID_TABLE)
    {

    }
    else if(groupId==GROUPID_PROCESS)
    {
        addId(X_ID_PROCESS_STRUCTS);
        addId(X_ID_PROCESS_DUMPTOFILE);
        addId(X_ID_PROCESS_MEMORY_HEX);
        addId(X_ID_PROCESS_MEMORY_STRINGS);
        addId(X_ID_PROCESS_MEMORY_SIGNATURES);
        addId(X_ID_PROCESS_MEMORY_MEMORYMAP);
        addId(X_ID_PROCESS_MEMORY_MODULES);
        addId(X_ID_PROCESS_SHOWIN_VIEWER);
        addId(X_ID_PROCESS_SHOWIN_FOLDER);
        addId(X_ID_PROCESS_COPY_PID);
        addId(X_ID_PROCESS_COPY_NAME);
        addId(X_ID_PROCESS_COPY_FILENAME);
    }
    else if(groupId==GROUPID_MEMORY)
    {

    }
    else if(groupId==GROUPID_MEMORYMAP)
    {
        addId(X_ID_MEMORYMAP_DUMPTOFILE);
    }
    else if(groupId==GROUPID_MODULES)
    {
        addId(X_ID_MODULES_DUMPTOFILE);
    }
    else if(groupId==GROUPID_COPY)
    {

    }
    else if(groupId==GROUPID_GOTO)
    {

    }
    else if(groupId==GROUPID_EDIT)
    {

    }
    else if(groupId==GROUPID_FIND)
    {

    }
    else if(groupId==GROUPID_TOOLS)
    {

    }
    else if(groupId==GROUPID_HELP)
    {

    }
    else if(groupId==GROUPID_SELECT)
    {

    }
    else if(groupId==GROUPID_FOLLOWIN)
    {

    }
    else if(groupId==GROUPID_SHOWIN)
    {

    }
    else if(groupId==GROUPID_BREAKPOINT)
    {

    }
}

void XShortcuts::addId(quint64 nId)
{
    g_mapValues.insert(nId,getDefault(nId));
}

void XShortcuts::addGroup(ID id) // TODO Remove
{

}

QList<quint64> XShortcuts::getShortcutsIDs()
{
    return g_mapValues.keys();
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
        qDebug("XShortcuts: load file %s",pSettings->fileName().toUtf8().data());
    }
#endif

    if(pSettings)
    {
        QList<quint64> listKeys=g_mapValues.keys();

        qint32 nNumberOfRecords=listKeys.count();

        for(qint32 i=0;i<nNumberOfRecords;i++)
        {
            quint64 nId=listKeys.at(i);
            QKeySequence ksDefault=getDefault(nId);

            QString sPath=idToSettingsString(nId);

            g_mapValues.insert(nId,QKeySequence::fromString(pSettings->value(sPath,ksDefault).toString()));
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
        qDebug("XShortcuts: save file %s",pSettings->fileName().toUtf8().data());
    }
#endif

    if(pSettings)
    {
        QList<quint64> listKeys=g_mapValues.keys();

        qint32 nNumberOfRecords=listKeys.count();

        for(qint32 i=0;i<nNumberOfRecords;i++)
        {
            quint64 nId=listKeys.at(i);

            QString sPath=idToSettingsString(nId);

            pSettings->setValue(sPath,g_mapValues.value(nId).toString());
        }
    }

    if(pSettings)
    {
        delete pSettings;
    }
}

QKeySequence XShortcuts::getShortcut(quint64 nId)
{
#ifdef QT_DEBUG
    if(!g_mapValues.contains(nId))
    {
        QString sErrorString=idToSettingsString(nId);
        qDebug("%s",sErrorString.toLatin1().data());
    }
#endif
    return g_mapValues.value(nId);
}

void XShortcuts::setShortcut(quint64 nId,QKeySequence keyValue)
{
    g_mapValues.insert(nId,keyValue);
}

bool XShortcuts::checkShortcut(quint64 nId,QKeySequence keyValue)
{
    bool bResult=true;

    if(keyValue!=QKeySequence())
    {
        GROUPID idGroup=getGroupId(nId);

        QList<quint64> listIds=g_mapValues.keys();

        qint32 nNumberOfRecords=listIds.count();

        for(qint32 i=0;i<nNumberOfRecords;i++)
        {
            quint64 _nId=listIds.at(i);

            if(_nId!=nId)
            {
                if(getGroupId(_nId)==idGroup)
                {
                    QKeySequence _keyValue=getShortcut(_nId);
                    if(_keyValue==keyValue)
                    {
                        bResult=false;
                        break;
                    }
                }
            }
        }
    }

    return bResult;
}

QString XShortcuts::idToSettingsString(quint64 nId)
{
    QString sResult;

    GROUPID groupId=getGroupId(nId);
    QList<GROUPID> listSubgroupIds=getSubgroupIds(nId);
    BASEID baseId=getBaseId(nId);

    sResult+=QString("XShortcuts/%1/").arg(groupIdToSettingsString(groupId));

    qint32 nNumberOfRecords=listSubgroupIds.count();

    for(qint32 i=0;i<nNumberOfRecords;i++)
    {
        sResult+=QString("%1/").arg(groupIdToSettingsString(listSubgroupIds.at(i)));
    }

    sResult+=QString("%1").arg(baseIdToSettingsString(baseId));

    return sResult;
}

QKeySequence XShortcuts::getDefault(quint64 nId)
{
    // TODO use defines
    QKeySequence ksResult=QKeySequence();

    GROUPID groupId=getGroupId(nId);

    if(groupId==GROUPID_FILE)
    {
        if      (nId==X_ID_FILE_OPEN)                       ksResult=QKeySequence();
        else if (nId==X_ID_FILE_SAVE)                       ksResult=QKeySequence();
        else if (nId==X_ID_FILE_SAVEAS)                     ksResult=QKeySequence();
        else if (nId==X_ID_FILE_CLOSE)                      ksResult=QKeySequence();
        else if (nId==X_ID_FILE_PRINT)                      ksResult=QKeySequence();
        else if (nId==X_ID_FILE_EXIT)                       ksResult=QKeySequence();
    }
    else if(groupId==GROUPID_VIEW)
    {

    }
    else if(groupId==GROUPID_DEBUGGER)
    {
        if      (nId==X_ID_DEBUGGER_FILE_OPEN)                  ksResult=QKeySequence::Open;
        else if (nId==X_ID_DEBUGGER_FILE_CLOSE)                 ksResult=QKeySequence::Close;
        else if (nId==X_ID_DEBUGGER_FILE_ATTACH)                ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_FILE_DETACH)                ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_FILE_EXIT)                  ksResult=QKeySequence::Quit;
        else if (nId==X_ID_DEBUGGER_VIEW_CPU)                   ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_VIEW_LOG)                   ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_VIEW_BREAKPOINTS)           ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_VIEW_MEMORYMAP)             ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_VIEW_CALLSTACK)             ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_VIEW_THREADS)               ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_VIEW_HANDLES)               ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_VIEW_MODULES)               ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_VIEW_SYMBOLS)               ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_TOOLS_SHORTCUTS)            ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_TOOLS_OPTIONS)              ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_HELP_ABOUT)                 ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_DEBUG_RUN)                  ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_DEBUG_PAUSE)                ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_DEBUG_STEPINTO)             ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_DEBUG_STEPOVER)             ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_DEBUG_STOP)                 ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_DEBUG_RESTART)              ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_DISASM_BREAKPOINT_TOGGLE)
        {
        #ifdef Q_OS_WIN
            ksResult=Qt::Key_F2;
        #else
            ksResult=QKeySequence();
        #endif
        }
        else if (nId==X_ID_DEBUGGER_DISASM_DUMPTOFILE)          ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_DISASM_GOTO_ADDRESS)        ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_DISASM_HEX_SIGNATURE)       ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_DISASM_SIGNATURE)           ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_DISASM_FIND_STRING)         ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_DISASM_FIND_VALUE)          ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_DISASM_FIND_SIGNATURE)      ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_DISASM_FIND_NEXT)           ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_DISASM_COPY_HEX)            ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_DISASM_COPY_ADDRESS)        ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_DISASM_SELECT_ALL)          ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_DISASM_EDIT_HEX)            ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_HEX_DUMPTOFILE)             ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_HEX_FIND_STRING)            ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_HEX_FIND_VALUE)             ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_HEX_FIND_SIGNATURE)         ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_HEX_FIND_NEXT)              ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_HEX_GOTO_ADDRESS)           ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_HEX_SIGNATURE)              ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_HEX_COPY_HEX)               ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_HEX_COPY_ADDRESS)           ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_HEX_SELECT_ALL)             ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_HEX_EDIT_HEX)               ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_STACK_GOTO_ADDRESS)         ksResult=QKeySequence();
        else if (nId==X_ID_DEBUGGER_STACK_EDIT_HEX)             ksResult=QKeySequence();
    }
    else if(groupId==GROUPID_DEBUG)
    {

    }
    else if(groupId==GROUPID_ACTION)
    {

    }
    else if(groupId==GROUPID_STRING)
    {
        if      (nId==X_ID_STRINGS_COPY_STRING)         ksResult=QKeySequence::Copy;
        else if (nId==X_ID_STRINGS_COPY_OFFSET)         ksResult=QKeySequence();
        else if (nId==X_ID_STRINGS_COPY_SIZE)           ksResult=QKeySequence();
        else if (nId==X_ID_STRINGS_FOLLOWIN_HEX)        ksResult=QKeySequence();
        else if (nId==X_ID_STRINGS_DEMANGLE)            ksResult=QKeySequence();
        else if (nId==X_ID_STRINGS_EDIT_STRING)         ksResult=QKeySequence();
    }
    else if(groupId==GROUPID_SIGNATURE)
    {
        if      (nId==X_ID_SIGNATURES_COPY_NAME)        ksResult=QKeySequence::Copy;
        else if (nId==X_ID_SIGNATURES_COPY_SIGNATURE)   ksResult=QKeySequence();
        else if (nId==X_ID_SIGNATURES_COPY_ADDRESS)     ksResult=QKeySequence();
        else if (nId==X_ID_SIGNATURES_COPY_OFFSET)      ksResult=QKeySequence();
        else if (nId==X_ID_SIGNATURES_FOLLOWIN_HEX)     ksResult=QKeySequence();
    }
    else if(groupId==GROUPID_STRUCT)
    {

    }
    else if(groupId==GROUPID_HEX)
    {
        if      (nId==X_ID_HEX_DUMPTOFILE)              ksResult=Qt::CTRL+Qt::Key_D;
        else if (nId==X_ID_HEX_GOTO_OFFSET)             ksResult=Qt::CTRL+Qt::Key_G;
        else if (nId==X_ID_HEX_GOTO_ADDRESS)            ksResult=QKeySequence();
        else if (nId==X_ID_HEX_SIGNATURE)               ksResult=QKeySequence();
        else if (nId==X_ID_HEX_FIND_STRING)             ksResult=QKeySequence::Find;
        else if (nId==X_ID_HEX_FIND_SIGNATURE)          ksResult=QKeySequence();
        else if (nId==X_ID_HEX_FIND_VALUE)              ksResult=QKeySequence();
        else if (nId==X_ID_HEX_FIND_NEXT)               ksResult=QKeySequence::FindNext;
        else if (nId==X_ID_HEX_SELECT_ALL)              ksResult=QKeySequence::SelectAll;
        else if (nId==X_ID_HEX_COPY_HEX)                ksResult=QKeySequence();
        else if (nId==X_ID_HEX_COPY_OFFSET)             ksResult=QKeySequence();
        else if (nId==X_ID_HEX_COPY_ADDRESS)            ksResult=QKeySequence();
        else if (nId==X_ID_HEX_FOLLOWIN_DISASM)         ksResult=QKeySequence();
        else if (nId==X_ID_HEX_FOLLOWIN_MEMORYMAP)      ksResult=QKeySequence();
        else if (nId==X_ID_HEX_EDIT_HEX)                ksResult=QKeySequence();
    }
    else if(groupId==GROUPID_DISASM)
    {
        if      (nId==X_ID_DISASM_DUMPTOFILE)           ksResult=Qt::CTRL+Qt::Key_D;
        else if (nId==X_ID_DISASM_GOTO_OFFSET)          ksResult=Qt::CTRL+Qt::Key_G;
        else if (nId==X_ID_DISASM_GOTO_ADDRESS)         ksResult=QKeySequence();
        else if (nId==X_ID_DISASM_GOTO_ENTRYPOINT)      ksResult=QKeySequence();
        else if (nId==X_ID_DISASM_SIGNATURE)            ksResult=Qt::SHIFT+Qt::Key_G;
        else if (nId==X_ID_DISASM_HEX_SIGNATURE)        ksResult=Qt::Key_S;
        else if (nId==X_ID_DISASM_FIND_STRING)          ksResult=QKeySequence::Find;
        else if (nId==X_ID_DISASM_FIND_SIGNATURE)       ksResult=QKeySequence();
        else if (nId==X_ID_DISASM_FIND_VALUE)           ksResult=QKeySequence();
        else if (nId==X_ID_DISASM_FIND_NEXT)            ksResult=QKeySequence::FindNext;
        else if (nId==X_ID_DISASM_SELECT_ALL)           ksResult=QKeySequence::SelectAll;
        else if (nId==X_ID_DISASM_COPY_HEX)             ksResult=QKeySequence::Copy;
        else if (nId==X_ID_DISASM_COPY_OFFSET)          ksResult=QKeySequence();
        else if (nId==X_ID_DISASM_COPY_ADDRESS)         ksResult=QKeySequence();
        else if (nId==X_ID_DISASM_FOLLOWIN_HEX)         ksResult=QKeySequence();
    }
    else if(groupId==GROUPID_STACK)
    {

    }
    else if(groupId==GROUPID_REGISTERS)
    {

    }
    else if(groupId==GROUPID_ARCHIVE)
    {
        if      (nId==X_ID_ARCHIVE_OPEN)                ksResult=QKeySequence();
        else if (nId==X_ID_ARCHIVE_SCAN)                ksResult=QKeySequence();
        else if (nId==X_ID_ARCHIVE_HEX)                 ksResult=QKeySequence();
        else if (nId==X_ID_ARCHIVE_STRINGS)             ksResult=QKeySequence();
        else if (nId==X_ID_ARCHIVE_ENTROPY)             ksResult=QKeySequence();
        else if (nId==X_ID_ARCHIVE_HASH)                ksResult=QKeySequence();
        else if (nId==X_ID_ARCHIVE_COPY_FILENAME)       ksResult=QKeySequence();
        else if (nId==X_ID_ARCHIVE_DUMPTOFILE)          ksResult=QKeySequence();
    }
    else if(groupId==GROUPID_TABLE)
    {

    }
    else if(groupId==GROUPID_PROCESS)
    {
        if      (nId==X_ID_PROCESS_STRUCTS)             ksResult=QKeySequence();
        else if (nId==X_ID_PROCESS_DUMPTOFILE)          ksResult=QKeySequence();
        else if (nId==X_ID_PROCESS_MEMORY_HEX)          ksResult=QKeySequence();
        else if (nId==X_ID_PROCESS_MEMORY_STRINGS)      ksResult=QKeySequence();
        else if (nId==X_ID_PROCESS_MEMORY_SIGNATURES)   ksResult=QKeySequence();
        else if (nId==X_ID_PROCESS_MEMORY_MEMORYMAP)    ksResult=QKeySequence();
        else if (nId==X_ID_PROCESS_MEMORY_MODULES)      ksResult=QKeySequence();
        else if (nId==X_ID_PROCESS_SHOWIN_VIEWER)       ksResult=QKeySequence();
        else if (nId==X_ID_PROCESS_SHOWIN_FOLDER)       ksResult=QKeySequence();
        else if (nId==X_ID_PROCESS_COPY_PID)            ksResult=QKeySequence();
        else if (nId==X_ID_PROCESS_COPY_NAME)           ksResult=QKeySequence();
        else if (nId==X_ID_PROCESS_COPY_FILENAME)       ksResult=QKeySequence();
    }
    else if(groupId==GROUPID_MEMORY)
    {

    }
    else if(groupId==GROUPID_MEMORYMAP)
    {
        if      (nId==X_ID_MEMORYMAP_DUMPTOFILE)        ksResult=QKeySequence();
    }
    else if(groupId==GROUPID_MODULES)
    {
        if      (nId==X_ID_MODULES_DUMPTOFILE)          ksResult=QKeySequence();
    }
    else if(groupId==GROUPID_COPY)
    {

    }
    else if(groupId==GROUPID_GOTO)
    {

    }
    else if(groupId==GROUPID_EDIT)
    {

    }
    else if(groupId==GROUPID_FIND)
    {

    }
    else if(groupId==GROUPID_TOOLS)
    {

    }
    else if(groupId==GROUPID_HELP)
    {

    }
    else if(groupId==GROUPID_SELECT)
    {

    }
    else if(groupId==GROUPID_FOLLOWIN)
    {

    }
    else if(groupId==GROUPID_SHOWIN)
    {

    }
    else if(groupId==GROUPID_BREAKPOINT)
    {

    }

    return ksResult;
}

QString XShortcuts::groupIdToString(GROUPID groupId)
{
    QString sResult="";

    if      (groupId==GROUPID_ACTION)       sResult=tr("Action");
    else if (groupId==GROUPID_FILE)         sResult=tr("File");
    else if (groupId==GROUPID_VIEW)         sResult=tr("View");
    else if (groupId==GROUPID_STRING)       sResult=tr("String");
    else if (groupId==GROUPID_STRINGS)      sResult=tr("Strings");
    else if (groupId==GROUPID_SIGNATURE)    sResult=tr("Signature");
    else if (groupId==GROUPID_SIGNATURES)   sResult=tr("Signatures");
    else if (groupId==GROUPID_STRUCT)       sResult=tr("Struct");
    else if (groupId==GROUPID_HEX)          sResult=tr("Hex");
    else if (groupId==GROUPID_DISASM)       sResult=tr("Disasm");
    else if (groupId==GROUPID_DEBUG)        sResult=tr("Debug");
    else if (groupId==GROUPID_DEBUGGER)     sResult=tr("Debugger");
    else if (groupId==GROUPID_REGISTER)     sResult=tr("Register");
    else if (groupId==GROUPID_STACK)        sResult=tr("Stack");
    else if (groupId==GROUPID_ARCHIVE)      sResult=tr("Archive");
    else if (groupId==GROUPID_TABLE)        sResult=tr("Table");
    else if (groupId==GROUPID_PROCESS)      sResult=tr("Process");
    else if (groupId==GROUPID_MEMORY)       sResult=tr("Memory");
    else if (groupId==GROUPID_COPY)         sResult=tr("Copy");
    else if (groupId==GROUPID_EDIT)         sResult=tr("Edit");
    else if (groupId==GROUPID_FIND)         sResult=tr("Find");
    else if (groupId==GROUPID_GOTO)         sResult=tr("Go to");
    else if (groupId==GROUPID_TOOLS)        sResult=tr("Tools");
    else if (groupId==GROUPID_HELP)         sResult=tr("Help");
    else if (groupId==GROUPID_SELECT)       sResult=tr("Select");
    else if (groupId==GROUPID_FOLLOWIN)     sResult=tr("Follow in");
    else if (groupId==GROUPID_SHOWIN)       sResult=tr("Show in");
    else if (groupId==GROUPID_BREAKPOINT)   sResult=tr("Breakpoint");
    else if (groupId==GROUPID_MODULES)      sResult=tr("Modules");
    else if (groupId==GROUPID_MEMORYMAP)    sResult=tr("Memory map");

    return sResult;
}

QString XShortcuts::baseIdToString(BASEID baseId)
{
    QString sResult;

    if      (baseId==BASEID_COPY)           sResult=tr("Copy");
    else if (baseId==BASEID_SHOW)           sResult=tr("Show");
    else if (baseId==BASEID_OPEN)           sResult=tr("Open");
    else if (baseId==BASEID_SAVE)           sResult=tr("Save");
    else if (baseId==BASEID_SAVEAS)         sResult=tr("Save as");
    else if (baseId==BASEID_CLOSE)          sResult=tr("Close");
    else if (baseId==BASEID_PRINT)          sResult=tr("Print");
    else if (baseId==BASEID_EXIT)           sResult=tr("Exit");
    else if (baseId==BASEID_DUMPTOFILE)     sResult=tr("Dump to file");
    else if (baseId==BASEID_ADDRESS)        sResult=tr("Address");
    else if (baseId==BASEID_ENTRYPOINT)     sResult=tr("Entry point");
    else if (baseId==BASEID_OFFSET)         sResult=tr("Offset");
    else if (baseId==BASEID_SIZE)           sResult=tr("Size");
    else if (baseId==BASEID_STRING)         sResult=tr("String");
    else if (baseId==BASEID_STRINGS)        sResult=tr("Strings");
    else if (baseId==BASEID_SIGNATURE)      sResult=tr("Signature");
    else if (baseId==BASEID_SIGNATURES)     sResult=tr("Signatures");
    else if (baseId==BASEID_HEX)            sResult=tr("Hex");
    else if (baseId==BASEID_DEMANGLE)       sResult=tr("Demangle");
    else if (baseId==BASEID_NAME)           sResult=tr("Name");
    else if (baseId==BASEID_NEXT)           sResult=tr("Next");
    else if (baseId==BASEID_VALUE)          sResult=tr("Value");
    else if (baseId==BASEID_ALL)            sResult=tr("All");
    else if (baseId==BASEID_DISASM)         sResult=tr("Disasm");
    else if (baseId==BASEID_MEMORYMAP)      sResult=tr("Memory map");
    else if (baseId==BASEID_ATTACH)         sResult=tr("Attach");
    else if (baseId==BASEID_DETACH)         sResult=tr("Detach");
    else if (baseId==BASEID_CPU)            sResult=tr("CPU");
    else if (baseId==BASEID_LOG)            sResult=tr("Log");
    else if (baseId==BASEID_BREAKPOINTS)    sResult=tr("Breakpoints");
    else if (baseId==BASEID_CALLSTACK)      sResult=tr("Callstack");
    else if (baseId==BASEID_THREADS)        sResult=tr("Threads");
    else if (baseId==BASEID_HANDLES)        sResult=tr("Handles");
    else if (baseId==BASEID_MODULES)        sResult=tr("Modules");
    else if (baseId==BASEID_SYMBOLS)        sResult=tr("Symbols");
    else if (baseId==BASEID_SHORTCUTS)      sResult=tr("Shortcuts");
    else if (baseId==BASEID_OPTIONS)        sResult=tr("Options");
    else if (baseId==BASEID_ABOUT)          sResult=tr("About");
    else if (baseId==BASEID_FILENAME)       sResult=tr("File name");
    else if (baseId==BASEID_STRUCTS)        sResult=tr("Structs");
    else if (baseId==BASEID_VIEWER)         sResult=tr("Viewer");
    else if (baseId==BASEID_FOLDER)         sResult=tr("Folder");
    else if (baseId==BASEID_PID)            sResult=QString("PID");
    else if (baseId==BASEID_RUN)            sResult=tr("Run");
    else if (baseId==BASEID_PAUSE)          sResult=tr("Pause");
    else if (baseId==BASEID_STEPINTO)       sResult=tr("Step into");
    else if (baseId==BASEID_STEPOVER)       sResult=tr("Step over");
    else if (baseId==BASEID_STOP)           sResult=tr("Stop");
    else if (baseId==BASEID_RESTART)        sResult=tr("Restart");
    else if (baseId==BASEID_TOGGLE)         sResult=tr("Toggle");
    else if (baseId==BASEID_SCAN)           sResult=tr("Scan");
    else if (baseId==BASEID_ENTROPY)        sResult=tr("Entropy");
    else if (baseId==BASEID_HASH)           sResult=tr("Hash");
    else if (baseId==BASEID_STACK)          sResult=tr("Stack");

    return sResult;
}

quint64 XShortcuts::createShortcutsId(GROUPID groupId,QList<GROUPID>listSubgroup,BASEID baseId)
{
    quint64 nResult=0;

    quint64 nSubgoups=0;

    qint32 nNumberOfRecords=listSubgroup.count();

    for(qint32 i=0;i<nNumberOfRecords;i++)
    {
        nSubgoups|=(((quint64)1)<<(listSubgroup.at(i)));
    }

    nResult=(((quint64)groupId)<<(16*3))|(((quint64)nSubgoups)<<(16))|((quint64)baseId);

    return nResult;
}

XShortcuts::GROUPID XShortcuts::getGroupId(quint64 nShortcutId)
{
    GROUPID result=GROUPID_UNKNOWN;

    result=(GROUPID)(nShortcutId>>(16*3));

    return result;
}

QList<XShortcuts::GROUPID> XShortcuts::getSubgroupIds(quint64 nShortcutId)
{
    QList<GROUPID> listResult;

    quint32 nSubgroups=(quint32)(nShortcutId>>16);

    for(qint32 i=0;i<32;i++)
    {
        if(nSubgroups&(1<<i))
        {
            GROUPID groupId=(GROUPID)i;

            listResult.append(groupId);
        }
    }

    return listResult;
}

XShortcuts::BASEID XShortcuts::getBaseId(quint64 nShortcutId)
{
    BASEID result=BASEID_UNKNOWN;

    result=(BASEID)(nShortcutId&0xFFFF);

    return result;
}

QString XShortcuts::baseIdToSettingsString(BASEID baseId)
{
    QString sResult;

    if      (baseId==BASEID_COPY)           sResult=QString("Copy");
    else if (baseId==BASEID_SHOW)           sResult=QString("Show");
    else if (baseId==BASEID_OPEN)           sResult=QString("Open");
    else if (baseId==BASEID_SAVE)           sResult=QString("Save");
    else if (baseId==BASEID_SAVEAS)         sResult=QString("SaveAs");
    else if (baseId==BASEID_CLOSE)          sResult=QString("Close");
    else if (baseId==BASEID_PRINT)          sResult=QString("Print");
    else if (baseId==BASEID_EXIT)           sResult=QString("Exit");
    else if (baseId==BASEID_DUMPTOFILE)     sResult=QString("DumpToFile");
    else if (baseId==BASEID_ADDRESS)        sResult=QString("Address");
    else if (baseId==BASEID_ENTRYPOINT)     sResult=QString("EntryPoint");
    else if (baseId==BASEID_OFFSET)         sResult=QString("Offset");
    else if (baseId==BASEID_SIZE)           sResult=QString("Size");
    else if (baseId==BASEID_STRING)         sResult=QString("String");
    else if (baseId==BASEID_STRINGS)        sResult=QString("Strings");
    else if (baseId==BASEID_SIGNATURE)      sResult=QString("Signature");
    else if (baseId==BASEID_SIGNATURES)     sResult=QString("Signatures");
    else if (baseId==BASEID_HEX)            sResult=QString("Hex");
    else if (baseId==BASEID_DEMANGLE)       sResult=QString("Demangle");
    else if (baseId==BASEID_NAME)           sResult=QString("Name");
    else if (baseId==BASEID_NEXT)           sResult=QString("Next");
    else if (baseId==BASEID_VALUE)          sResult=QString("Value");
    else if (baseId==BASEID_ALL)            sResult=QString("All");
    else if (baseId==BASEID_DISASM)         sResult=QString("Disasm");
    else if (baseId==BASEID_MEMORYMAP)      sResult=QString("MemoryMap");
    else if (baseId==BASEID_ATTACH)         sResult=QString("Attach");
    else if (baseId==BASEID_DETACH)         sResult=QString("Detach");
    else if (baseId==BASEID_CPU)            sResult=QString("CPU");
    else if (baseId==BASEID_LOG)            sResult=QString("Log");
    else if (baseId==BASEID_BREAKPOINTS)    sResult=QString("Breakpoints");
    else if (baseId==BASEID_CALLSTACK)      sResult=QString("Callstack");
    else if (baseId==BASEID_THREADS)        sResult=QString("Threads");
    else if (baseId==BASEID_HANDLES)        sResult=QString("Handles");
    else if (baseId==BASEID_MODULES)        sResult=QString("Modules");
    else if (baseId==BASEID_SYMBOLS)        sResult=QString("Symbols");
    else if (baseId==BASEID_SHORTCUTS)      sResult=QString("Shortcuts");
    else if (baseId==BASEID_OPTIONS)        sResult=QString("Options");
    else if (baseId==BASEID_ABOUT)          sResult=QString("About");
    else if (baseId==BASEID_FILENAME)       sResult=QString("FileName");
    else if (baseId==BASEID_STRUCTS)        sResult=QString("Structs");
    else if (baseId==BASEID_VIEWER)         sResult=QString("Viewer");
    else if (baseId==BASEID_FOLDER)         sResult=QString("Folder");
    else if (baseId==BASEID_PID)            sResult=QString("PID");
    else if (baseId==BASEID_RUN)            sResult=QString("Run");
    else if (baseId==BASEID_PAUSE)          sResult=QString("Pause");
    else if (baseId==BASEID_STEPINTO)       sResult=QString("StepInto");
    else if (baseId==BASEID_STEPOVER)       sResult=QString("StepOver");
    else if (baseId==BASEID_STOP)           sResult=QString("Stop");
    else if (baseId==BASEID_RESTART)        sResult=QString("Restart");
    else if (baseId==BASEID_TOGGLE)         sResult=QString("Toggle");
    else if (baseId==BASEID_SCAN)           sResult=QString("Scan");
    else if (baseId==BASEID_ENTROPY)        sResult=QString("Entropy");
    else if (baseId==BASEID_HASH)           sResult=QString("Hash");
    else if (baseId==BASEID_STACK)          sResult=QString("Stack");

    return sResult;
}

QString XShortcuts::groupIdToSettingsString(GROUPID groupId)
{
    QString sResult="";

    if      (groupId==GROUPID_ACTION)       sResult=QString("Action");
    else if (groupId==GROUPID_FILE)         sResult=QString("File");
    else if (groupId==GROUPID_VIEW)         sResult=QString("View");
    else if (groupId==GROUPID_STRING)       sResult=QString("String");
    else if (groupId==GROUPID_STRINGS)      sResult=QString("Strings");
    else if (groupId==GROUPID_SIGNATURE)    sResult=QString("Signature");
    else if (groupId==GROUPID_SIGNATURES)   sResult=QString("Signatures");
    else if (groupId==GROUPID_STRUCT)       sResult=QString("Struct");
    else if (groupId==GROUPID_HEX)          sResult=QString("Hex");
    else if (groupId==GROUPID_DISASM)       sResult=QString("Disasm");
    else if (groupId==GROUPID_DEBUG)        sResult=QString("Debug");
    else if (groupId==GROUPID_DEBUGGER)     sResult=QString("Debugger");
    else if (groupId==GROUPID_REGISTER)     sResult=QString("Register");
    else if (groupId==GROUPID_STACK)        sResult=QString("Stack");
    else if (groupId==GROUPID_ARCHIVE)      sResult=QString("Archive");
    else if (groupId==GROUPID_TABLE)        sResult=QString("Table");
    else if (groupId==GROUPID_PROCESS)      sResult=QString("Process");
    else if (groupId==GROUPID_MEMORY)       sResult=QString("Memory");
    else if (groupId==GROUPID_COPY)         sResult=QString("Copy");
    else if (groupId==GROUPID_EDIT)         sResult=QString("Edit");
    else if (groupId==GROUPID_FIND)         sResult=QString("Find");
    else if (groupId==GROUPID_GOTO)         sResult=QString("GoTo");
    else if (groupId==GROUPID_TOOLS)        sResult=QString("Tools");
    else if (groupId==GROUPID_HELP)         sResult=QString("Help");
    else if (groupId==GROUPID_SELECT)       sResult=QString("Select");
    else if (groupId==GROUPID_FOLLOWIN)     sResult=QString("FollowIn");
    else if (groupId==GROUPID_SHOWIN)       sResult=QString("ShowIn");
    else if (groupId==GROUPID_BREAKPOINT)   sResult=QString("Breakpoint");
    else if (groupId==GROUPID_MODULES)      sResult=QString("Modules");
    else if (groupId==GROUPID_MEMORYMAP)    sResult=QString("MemoryMap");

    return sResult;
}
