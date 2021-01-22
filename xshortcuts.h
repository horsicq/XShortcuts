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
        ID_HEX                  =0x20000,
        ID_HEX_DUMPTOFILE,
        ID_DISASM               =0x40000,
        ID_DISASM_DUMPTOFILE
    };

    explicit XShortcuts(QObject *pParent=nullptr);
    void setName(QString sName);
    void setValueIDs(QList<ID> listValueIDs);
    void load();
    void save();
    QString getApplicationDataPath();
    static QString idToSettingsString(ID id);
    static QString idToString(ID id);
    static QKeySequence getDefault(ID id);

private:
    QString g_sName;
    QString g_sFilePath;
    QList<ID> g_listValueIDs;
    QMap<ID,QKeySequence> g_mapValues;
};

#endif // XSHORTCUTS_H
