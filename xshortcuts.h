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
#ifndef XSHORTCUTS_H
#define XSHORTCUTS_H

#include <QMap>
#include <QDir>
#include <QSettings>
#include <QApplication>
#include <QKeySequence>

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
        GROUPID_HEX,
        GROUPID_DISASM,
        GROUPID_ARCHIVE,
        GROUPID_TABLE,
    };

    static const int GROUP_SH=24;

    // TODO the subgroup
    enum ID
    {
        ID_ACTION                   =GROUPID_ACTION<<GROUP_SH,
        ID_ACTION_COPY,
        ID_ACTION__END,
        ID_FILE                     =GROUPID_FILE<<GROUP_SH,
        ID_FILE_OPEN,
        ID_FILE_SAVE,
        ID_FILE_CLOSE,
        ID_FILE_EXIT,
        ID_STRINGS                  =GROUPID_STRINGS<<GROUP_SH,
        ID_STRINGS_COPYSTRING,
        ID_STRINGS_COPYOFFSET,
        ID_STRINGS_COPYSIZE,
        ID_STRINGS_HEX,
        ID_STRINGS_DEMANGLE,
        ID_STRINGS__END,
        ID_SIGNATURES               =GROUPID_SIGNATURES<<GROUP_SH,
        ID_SIGNATURES_COPYNAME,
        ID_SIGNATURES_COPYSIGNATURE,
        ID_SIGNATURES_COPYADDRESS,
        ID_SIGNATURES_COPYOFFSET,
        ID_SIGNATURES_COPYSIZE,
        ID_SIGNATURES_HEX,
        ID_SIGNATURES__END,
        ID_HEX                      =GROUPID_HEX<<GROUP_SH,
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
        ID_HEX__END,
        ID_DISASM                   =GROUPID_DISASM<<GROUP_SH,
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
        ID_DEBUGGER                 =GROUPID_DEBUGGER<<GROUP_SH,
        ID_DEBUGGER_FILE_OPEN,
        ID_DEBUGGER_FILE_CLOSE,
        ID_DEBUGGER_FILE_ATTACH,
        ID_DEBUGGER_FILE_DETACH,
        ID_DEBUGGER_FILE_EXIT,
        ID_DEBUGGER_VIEW_CPU,
        ID_DEBUGGER_VIEW_ACTIONS,
        ID_DEBUGGER_VIEW_LOG,
        ID_DEBUGGER_VIEW_BREAKPOINTS,
        ID_DEBUGGER_VIEW_MEMORYMAP,
        ID_DEBUGGER_VIEW_CALLSTACK,
        ID_DEBUGGER_VIEW_THREADS,
        ID_DEBUGGER_VIEW_HANDLES,
        ID_DEBUGGER_DEBUG_RUN,
        ID_DEBUGGER_DEBUG_PAUSE,
        ID_DEBUGGER_DEBUG_TOGGLE,
        ID_DEBUGGER_DEBUG_STEPINTO,
        ID_DEBUGGER_DEBUG_STEPOVER,
        ID_DEBUGGER_DEBUG_STOP,
        ID_DEBUGGER_DEBUG_RESTART,
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
        ID_DEBUGGER_HEX_GOTOADDRESS,
        ID_DEBUGGER_HEX_SELECTALL,
        ID_DEBUGGER__END,
        ID_ARCHIVE                  =GROUPID_ARCHIVE<<GROUP_SH,
        ID_ARCHIVE_OPEN,
        ID_ARCHIVE_SCAN,
        ID_ARCHIVE_HEX,
        ID_ARCHIVE_STRINGS,
        ID_ARCHIVE_ENTROPY,
        ID_ARCHIVE_HASH,
        ID_ARCHIVE_COPYFILENAME,
        ID_ARCHIVE_DUMPTOFILE,
        ID_ARCHIVE__END,
        ID_TABLE                    =GROUPID_TABLE<<GROUP_SH,
        ID_TABLE_HEX,
        ID_TABLE_DISASM,
        ID_TABLE__END
        // TODO More
    };

    explicit XShortcuts(QObject *pParent=nullptr);
    void setName(QString sValue);
    void setNative(bool bValue);
    void addGroup(GROUPID groupId);
    void addGroup(ID id); // TODO remove
    void setShortcutsIDs(QList<ID> listValueIDs);
    QList<ID> getShortcutsIDs();
    void load();
    void save();
    QKeySequence getShortcut(ID id);
    void setShortcut(ID id,QKeySequence keyValue);
    bool checkShortcut(ID id,QKeySequence keyValue);

    static QString idToSettingsString(ID id);
    static QString idToString(ID id);
    static QKeySequence getDefault(ID id);
    static QString groupIdToString(GROUPID groupId);
    static ID getGroupEnd(GROUPID groupId);
    static GROUPID getGroupId(ID id);
    static GROUPID getSubgroupId(ID id);

private:
    bool g_bIsNative;
    QString g_sName;
    QString g_sFilePath;
    QList<ID> g_listValueIDs;
    QMap<ID,QKeySequence> g_mapValues;
};

#endif // XSHORTCUTS_H
