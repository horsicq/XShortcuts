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
#ifndef XSHORTCUTSTSCROLLAREA_H
#define XSHORTCUTSTSCROLLAREA_H

#include <QAbstractScrollArea>

#include "xoptions.h"
#include "xshortcuts.h"

class XShortcutstScrollArea : public QAbstractScrollArea {
    Q_OBJECT

public:
    enum TCLOLOR {
        TCLOLOR_SELECTED = 0,
        TCLOLOR_BREAKPOINT,
        TCLOLOR_ANALYSED,
        TCLOLOR_SIZE
    };

    XShortcutstScrollArea(QWidget *pParent = nullptr);
    ~XShortcutstScrollArea();

    virtual void setGlobal(XShortcuts *pShortcuts, XOptions *pXOptions);
    static void setGlobalChildren(QWidget *pWidget, XShortcuts *pShortcuts, XOptions *pXOptions);
    XShortcuts *getShortcuts();
    XOptions *getGlobalOptions();
    bool isActive();
    void setActive(bool bState);
    virtual void adjustView() = 0;
    static void adjustViewChildren(QWidget *pWidget);
    virtual void reloadShortcuts();
    QColor getColor(TCLOLOR tcolor);
    void setColor(TCLOLOR tcolor, QColor color);
    static QColor getColorSelected(QColor color);
    static QColor getColorSelected(QWidget *pWidget);
    virtual void setReadonly(bool bState);
    virtual bool isReadonly();

    void addShortcut(quint64 nShortcutId, QWidget *pWidget, const char *pMethod);
    virtual void setLocation(quint64 nLocation, qint32 nLocationType, qint64 nSize);

protected:
    bool eventFilter(QObject *pObj, QEvent *pEvent) override;
    virtual void registerShortcuts(bool bState);

signals:
    void dataChanged(qint64 nDeviceOffset, qint64 nDeviceSize);
    void currentLocationChanged(quint64 nLocation, qint32 nLocationType, qint64 nSize);
    void followLocation(quint64 nLocation, qint32 nLocationType, qint64 nSize, qint32 nWidgetType);

private:
    bool g_bIsActive;
    XShortcuts *g_pShortcuts;
    XShortcuts g_scEmpty;
    XOptions *g_pXOptions;
    XOptions g_xOptionsEmpty;
    QColor g_color[TCLOLOR_SIZE];
    bool g_bIsReadonly;
    QList<XShortcuts::SHORTCUTITEM> g_listShortCuts;
};

#endif  // XSHORTCUTSTSCROLLAREA_H
