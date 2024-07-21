/* Copyright (c) 2021-2024 hors<horsicq@gmail.com>
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
#ifndef DIALOGSHORTCUTS_H
#define DIALOGSHORTCUTS_H

#include "xshortcutsdialog.h"
#include <QKeyEvent>
#include <QMessageBox>
#include <QSortFilterProxyModel>
#include <QStandardItemModel>

#include "xoptions.h"
#include "xshortcuts.h"

namespace Ui {
class DialogShortcuts;
}

class DialogShortcuts : public XShortcutsDialog {
    Q_OBJECT

    enum COLUMN {
        COLUMN_NAME = 0,
        COLUMN_SHORTCUT
    };

public:
    explicit DialogShortcuts(QWidget *pParent = nullptr);
    ~DialogShortcuts();

    virtual void adjustView();

    void setData(XShortcuts *pShortcuts);
    void reload();

protected:
    bool eventFilter(QObject *pObj, QEvent *pEvent) override;

private slots:
    void on_lineEditFilter_textChanged(const QString &sString);
    void onCellChanged(const QItemSelection &itemSelected, const QItemSelection &itemDeselected);
    void on_pushButtonClose_clicked();
    void on_pushButtonClear_clicked();
    void on_pushButtonDefault_clicked();

protected:
    virtual void registerShortcuts(bool bState);

private:
    Ui::DialogShortcuts *ui;
    XShortcuts *g_pShortcuts;
    QSortFilterProxyModel *g_pFilter;
    QStandardItemModel *g_pModel;
};

#endif  // DIALOGSHORTCUTS_H
