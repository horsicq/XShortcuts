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
#ifndef XSHORTCUTS_H
#define XSHORTCUTS_H

#include <QApplication>
#include <QDir>
#include <QKeySequence>
#include <QMap>
#include <QSettings>

class XShortcuts : public QObject
{
    Q_OBJECT

public:
    enum GROUPID
    {
        GROUPID_UNKNOWN=0,
        GROUPID_FILE,
        GROUPID_VIEW,
        GROUPID_DEBUGGER,
        GROUPID_DEBUG,
        GROUPID_ACTION,
        GROUPID_STRINGS,
        GROUPID_SIGNATURES,
        GROUPID_STRUCTS,
        GROUPID_HEX,
        GROUPID_DISASM,
        GROUPID_STACK,
        GROUPID_REGISTERS,
        GROUPID_ARCHIVE,
        GROUPID_TABLE,
        GROUPID_PROCESS,
        GROUPID_MEMORY,
        GROUPID_MEMORYMAP,
        GROUPID_MODULES,
        GROUPID_COPY,
        GROUPID_GOTO,
        GROUPID_EDIT,
        GROUPID_TOOLS,
        GROUPID_HELP
    };

    enum BASEID
    {
        BASEID_UNKNOWN=0,
        BASEID_COPY,
        BASEID_SHOW,
        BASEID_OPEN,
        BASEID_SAVE,
        BASEID_SAVEAS,
        BASEID_CLOSE,
        BASEID_PRINT,
        BASEID_EXIT,
    };

    static const qint32 GROUP_SH=24; // 0xFF000000 // TODO remove !!!

    // TODO Debugger execute till selection
    // TODO Debugger breakpoints
    // TODO tracing
    // TODO more
    enum ID
    {
        ID_UNKNOWN=0,
        ID_ACTION                           =GROUPID_ACTION<<GROUP_SH,
        ID_ACTION_COPY,
        ID_ACTION_SHOW,
        ID_ACTION__END,
        ID_FILE                             =GROUPID_FILE<<GROUP_SH,
        ID_FILE_OPEN,
        ID_FILE_SAVE,
        ID_FILE_SAVEAS,
        ID_FILE_CLOSE,
        ID_FILE_PRINT,
        ID_FILE_EXIT,
        ID_STRINGS                          =GROUPID_STRINGS<<GROUP_SH,
        ID_STRINGS_COPY_STRING,
        ID_STRINGS_COPY_OFFSET,
        ID_STRINGS_COPY_SIZE,
        ID_STRINGS_HEX,
        ID_STRINGS_DEMANGLE,
        ID_STRINGS_EDIT_STRING,
        ID_STRINGS__END,
        ID_SIGNATURES                       =GROUPID_SIGNATURES<<GROUP_SH,
        ID_SIGNATURES_COPY_NAME,
        ID_SIGNATURES_COPY_SIGNATURE,
        ID_SIGNATURES_COPY_ADDRESS,
        ID_SIGNATURES_COPY_OFFSET,
        ID_SIGNATURES_HEX,
        ID_SIGNATURES__END,
        ID_HEX                              =GROUPID_HEX<<GROUP_SH,
        ID_HEX_DUMPTOFILE,
        ID_HEX_GOTOOFFSET,
        ID_HEX_GOTOADDRESS,
        ID_HEX_SIGNATURE,
        ID_HEX_FIND,
        ID_HEX_FINDNEXT,
        ID_HEX_SELECTALL,
        ID_HEX_COPYASHEX,
        ID_HEX_COPYCURSOROFFSET,
        ID_HEX_COPYCURSORADDRESS,
        ID_HEX_DISASM,
        ID_HEX_MEMORYMAP,
        ID_HEX_EDITHEX,
        ID_HEX__END,
        ID_DISASM                           =GROUPID_DISASM<<GROUP_SH,
        ID_DISASM_DUMPTOFILE,
        ID_DISASM_GOTOADDRESS,
        ID_DISASM_GOTOOFFSET,
        ID_DISASM_GOTOENTRYPOINT,
        ID_DISASM_HEXSIGNATURE,
        ID_DISASM_SIGNATURE,
        ID_DISASM_FIND,
        ID_DISASM_FINDNEXT,
        ID_DISASM_SELECTALL,
        ID_DISASM_COPYASHEX,
        ID_DISASM_COPYCURSORADDRESS,
        ID_DISASM_COPYCURSOROFFSET,
        ID_DISASM_HEX,
        ID_DISASM__END,
        ID_DEBUGGER                         =GROUPID_DEBUGGER<<GROUP_SH,
        ID_DEBUGGER_FILE_OPEN,
        ID_DEBUGGER_FILE_CLOSE,
        ID_DEBUGGER_FILE_ATTACH,
        ID_DEBUGGER_FILE_DETACH,
        ID_DEBUGGER_FILE_EXIT,
        ID_DEBUGGER_VIEW_CPU,
        ID_DEBUGGER_VIEW_LOG,
        ID_DEBUGGER_VIEW_BREAKPOINTS,
        ID_DEBUGGER_VIEW_MEMORYMAP,
        ID_DEBUGGER_VIEW_CALLSTACK,
        ID_DEBUGGER_VIEW_THREADS,
        ID_DEBUGGER_VIEW_HANDLES,
        ID_DEBUGGER_VIEW_MODULES,
        ID_DEBUGGER_VIEW_SYMBOLS,
        ID_DEBUGGER_TOOLS_SHORTCUTS,
        ID_DEBUGGER_TOOLS_OPTIONS,
        ID_DEBUGGER_HELP_ABOUT,
        ID_DEBUGGER_DEBUG_RUN,
        ID_DEBUGGER_DEBUG_PAUSE,
        ID_DEBUGGER_DEBUG_STEPINTO,
        ID_DEBUGGER_DEBUG_STEPOVER,
        ID_DEBUGGER_DEBUG_STOP,
        ID_DEBUGGER_DEBUG_RESTART,
        ID_DEBUGGER_DISASM_BREAKPOINTTOGGLE,
        ID_DEBUGGER_DISASM_DUMPTOFILE,
        ID_DEBUGGER_DISASM_GOTOADDRESS,
        ID_DEBUGGER_DISASM_HEXSIGNATURE,
        ID_DEBUGGER_DISASM_SIGNATURE,
        ID_DEBUGGER_DISASM_FIND,
        ID_DEBUGGER_DISASM_FINDNEXT,
        ID_DEBUGGER_DISASM_COPYASHEX,
        ID_DEBUGGER_DISASM_COPYCURSORADDRESS,
        ID_DEBUGGER_DISASM_SELECTALL,
        ID_DEBUGGER_HEX_DUMPTOFILE,
        ID_DEBUGGER_HEX_FIND,
        ID_DEBUGGER_HEX_FINDNEXT,
        ID_DEBUGGER_HEX_GOTOADDRESS,
        ID_DEBUGGER_HEX_SIGNATURE,
        ID_DEBUGGER_HEX_COPYASHEX,
        ID_DEBUGGER_HEX_COPYCURSORADDRESS,
        ID_DEBUGGER_HEX_SELECTALL,
        ID_DEBUGGER_STACK_GOTOADDRESS,
        ID_DEBUGGER__END,
        ID_ARCHIVE                          =GROUPID_ARCHIVE<<GROUP_SH,
        ID_ARCHIVE_OPEN,
        ID_ARCHIVE_SCAN,
        ID_ARCHIVE_HEX,
        ID_ARCHIVE_STRINGS,
        ID_ARCHIVE_ENTROPY,
        ID_ARCHIVE_HASH,
        ID_ARCHIVE_COPYFILENAME,
        ID_ARCHIVE_DUMPTOFILE,
        ID_ARCHIVE__END,
        ID_TABLE                            =GROUPID_TABLE<<GROUP_SH,
        ID_TABLE_HEX,
        ID_TABLE_DISASM,
        ID_TABLE__END,
        ID_PROCESS                          =GROUPID_PROCESS<<GROUP_SH,
        ID_PROCESS_STRUCTS,
        ID_PROCESS_DUMPTOFILE,
        ID_PROCESS_MEMORY_HEX,
        ID_PROCESS_MEMORY_STRINGS,
        ID_PROCESS_MEMORY_SIGNATURES,
        ID_PROCESS_MEMORY_MEMORYMAP,
        ID_PROCESS_MEMORY_MODULES,
        ID_PROCESS_FILE_VIEWER,
        ID_PROCESS_FILE_FOLDER,
        ID_PROCESS_COPY_PID,
        ID_PROCESS_COPY_NAME,
        ID_PROCESS_COPY_FILENAME,
        ID_PROCESS__END,
        ID_MEMORYMAP                        =GROUPID_MEMORYMAP<<GROUP_SH,
        ID_MEMORYMAP_DUMPTOFILE,
        ID_MEMORYMAP__END,
        ID_MODULES                          =GROUPID_MODULES<<GROUP_SH,
        ID_MODULES_DUMPTOFILE,
        ID_MODULES__END,
    };

    explicit XShortcuts(QObject *pParent=nullptr);

    void setName(QString sValue);
    void setNative(bool bValue);
    void addGroup(GROUPID groupId);
    void addId(quint64 nId);
    void addGroup(ID id); // TODO remove !!!
    void setShortcutsIDs(QList<ID> listValueIDs);
    QList<ID> getShortcutsIDs(); // TODO remove
    void load();
    void save();
    QKeySequence getShortcut(ID id); // TODO remove
    void setShortcut(ID id,QKeySequence keyValue); // TODO remove
    bool checkShortcut(ID id,QKeySequence keyValue); // TODO remove
    static QString idToSettingsString(ID id); // TODO remove
    static QString idToString(ID id); // TODO remove
    static QKeySequence getDefault(ID id); // TODO remove
    static QKeySequence getDefault(quint64 nId); // TODO remove
    static QString groupIdToString(GROUPID groupId);
    static QString baseIdToString(BASEID baseId);
    static ID getGroupEnd(GROUPID groupId); // TODO remove
    static GROUPID getGroupId(ID id); // TODO remove
    static GROUPID getSubgroupId(ID id); // TODO remove

    // |quin32 main|quint32 subgroups|quint32 reserverd|quint32 nID
    static quint64 createShortcutsId(GROUPID groupId,QList<GROUPID> listSubgroup,BASEID baseId);
    static GROUPID getGroupId(quint64 nShortcutId);
    static QList<GROUPID> getSubgroupIds(quint64 nShortcutId);
    static BASEID getBaseId(quint64 nShortcutId);
    static QString baseIdToSettingsString(BASEID baseId);
    static QString groupIdToSettingsString(GROUPID groupId);

private:
    bool g_bIsNative;
    QString g_sName;
    QString g_sFilePath;
    QList<ID> __g_listValueIDs;
    QMap<quint64,QKeySequence> g_mapValues;
    QMap<ID,QKeySequence> __g_mapValues;
};

#endif // XSHORTCUTS_H
