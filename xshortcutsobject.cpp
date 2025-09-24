/* Copyright (c) 2021-2025 hors<horsicq@gmail.com>
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
#include "xshortcutsobject.h"

XShortcutsObject::XShortcutsObject()
{
    g_pShortcuts = &g_scEmpty;
    g_pXOptions = &g_xOptionsEmpty;
    g_bIsActive = false;
    m_bIsReadonly = false;
}

void XShortcutsObject::setGlobal(XShortcuts *pShortcuts, XOptions *pXOptions)
{
    g_pShortcuts = pShortcuts;
    g_pXOptions = pXOptions;

    if (g_bIsActive) {
        reloadShortcuts();
    }

    adjustView();
}

XShortcuts *XShortcutsObject::getShortcuts()
{
    return g_pShortcuts;
}

XOptions *XShortcutsObject::getGlobalOptions()
{
    return g_pXOptions;
}

bool XShortcutsObject::isActive()
{
    return g_bIsActive;
}

void XShortcutsObject::setActive(bool bState)
{
    g_bIsActive = bState;
}

void XShortcutsObject::reloadShortcuts()
{
    registerShortcuts(false);
    registerShortcuts(true);
}

void XShortcutsObject::registerShortcuts(bool bState)
{
    g_pShortcuts->registerShortcuts(&g_listShortCuts, bState);
}

void XShortcutsObject::setReadonly(bool bState)
{
    m_bIsReadonly = bState;
}

bool XShortcutsObject::isReadonly()
{
    return m_bIsReadonly;
}

void XShortcutsObject::addShortcut(quint64 nShortcutId, QWidget *pRecv, const char *pMethod)
{
    XShortcuts::SHORTCUTITEM record = {};
    record.nShortcutId = nShortcutId;
    record.pRecv = pRecv;
    record.pMethod = pMethod;

    g_listShortCuts.append(record);
}

void XShortcutsObject::reloadData(bool bSaveSelection)
{
    Q_UNUSED(bSaveSelection)
#ifdef QT_DEBUG
    qDebug("reloadData");
#endif
}

void XShortcutsObject::setLocation(quint64 nLocation, qint32 nLocationType, qint64 nSize)
{
    Q_UNUSED(nLocation)
    Q_UNUSED(nLocationType)
    Q_UNUSED(nSize)
#ifdef QT_DEBUG
    qDebug("setLocation");
#endif
}
