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
#ifndef XSHORTCUTSWIDGET_H
#define XSHORTCUTSWIDGET_H

#include <QShortcut>
#include <QWidget>

#include "xoptions.h"
#include "xshortcuts.h"
#ifdef QT_CONCURRENT_LIB
#include <QAbstractItemModel>
#include <QFuture>
#include <QStandardItemModel>
#include <QtConcurrent>
#endif

class XShortcutsWidget : public QWidget {
    Q_OBJECT

public:
    explicit XShortcutsWidget(QWidget *pParent = nullptr);

    virtual void setGlobal(XShortcuts *pShortcuts, XOptions *pXOptions);
    XShortcuts *getShortcuts();
    XOptions *getGlobalOptions();
    void setActive(bool bState);
    void saveTableModel(QAbstractItemModel *pModel, QString sFileName);
    void saveTreeModel(QAbstractItemModel *pModel, QString sFileName);
    void saveTextEdit(QTextEdit *pTextEdit, QString sFileName);
    virtual void adjustView();
    QString getOpenFileName(QString sDirectory);
    void _blockSignals(QObject **ppObjects, qint32 nCount, bool bState);
#ifdef QT_CONCURRENT_LIB
    void deleteOldAbstractModel(QAbstractItemModel **g_ppOldModel);
    QFuture<void> deleteOldStandardModel(QStandardItemModel **g_ppOldModel);
#endif
private:
#ifdef QT_CONCURRENT_LIB
    void _deleteOldAbstractModel(QAbstractItemModel **g_ppOldModel);
    void _deleteOldStandardModel(QStandardItemModel **g_ppOldModel);
#endif

private slots:
    void errorMessageSlot(QString sErrorMessage);

protected:
    bool eventFilter(QObject *pObj, QEvent *pEvent) override;
    virtual void registerShortcuts(bool bState) = 0;

private:
    bool g_bIsActive;
    XShortcuts *g_pShortcuts;
    XShortcuts g_scEmpty;
    XOptions *g_pXOptions;
    XOptions g_xOptionsEmpty;
};

#endif  // XSHORTCUTSWIDGET_H
