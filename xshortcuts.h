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
    enum ID
    {
        ID_ACTION               =0x10000,
        ID_ACTION_COPY,
        ID_ACTION__END,
        ID_STRINGS              =0x20000,
        ID_STRINGS_COPYSTRING,
        ID_STRINGS_COPYOFFSET,
        ID_STRINGS_COPYSIZE,
        ID_STRINGS_HEX,
        ID_STRINGS__END,
        ID_HEX                  =0x40000,
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
        ID_DISASM               =0x80000,
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
        ID_DEBUGGER             =0x100000,
        ID_DEBUGGER_RUN,
        ID_DEBUGGER_BREAKPOINT,
        ID_DEBUGGER_STEPINTO,
        ID_DEBUGGER_STEPOVER,
        ID_DEBUGGER__END,
        ID_ARCHIVE              =0x200000,
        ID_ARCHIVE_OPEN,
        ID_ARCHIVE_SCAN,
        ID_ARCHIVE_HEX,
        ID_ARCHIVE_STRINGS,
        ID_ARCHIVE_ENTROPY,
        ID_ARCHIVE_HASH,
        ID_ARCHIVE_COPYFILENAME,
        ID_ARCHIVE_DUMPTOFILE,
        ID_ARCHIVE__END,
        ID_TABLE               =0x400000,
        ID_TABLE_HEX,
        ID_TABLE_DISASM,
        ID_TABLE__END
    };

    explicit XShortcuts(QObject *pParent=nullptr);
    void setName(QString sName);
    void addGroup(ID idGroup);
    void setShortcutsIDs(QList<ID> listValueIDs);
    QList<ID> getShortcutsIDs();
    void load();
    void save();
    QKeySequence getShortcut(ID id);
    void setShortcut(ID id,QKeySequence keyValue);
    bool checkShortcut(ID id,QKeySequence keyValue);

    static QString getApplicationDataPath();
    static QString idToSettingsString(ID id);
    static QString idToString(ID id);
    static QKeySequence getDefault(ID id);
    static QString idToGroupString(ID id);
    static ID getGroupEnd(ID idGroup);
    static ID getGroupFromId(ID id);

private:
    QString g_sName;
    QString g_sFilePath;
    QList<ID> g_listValueIDs;
    QMap<ID,QKeySequence> g_mapValues;
};

#endif // XSHORTCUTS_H
