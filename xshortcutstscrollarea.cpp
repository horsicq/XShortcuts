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
#include "xshortcutstscrollarea.h"

XShortcutstScrollArea::XShortcutstScrollArea(QWidget *pParent) : QAbstractScrollArea(pParent)
{
    g_pShortcuts = &g_scEmpty;
    g_pXOptions = &g_xOptionsEmpty;
    g_bIsActive = false;

    g_color[TCLOLOR_SELECTED] = getColorSelected(viewport());
    g_color[TCLOLOR_BREAKPOINT] = Qt::red;              // mb TODO
    g_color[TCLOLOR_ANALYSED] = QColor(100, 0, 0, 10);  // TODO
}

void XShortcutstScrollArea::setGlobal(XShortcuts *pShortcuts, XOptions *pXOptions)
{
    g_pShortcuts = pShortcuts;
    g_pXOptions = pXOptions;

    if (g_bIsActive) {
        reloadShortcuts();
    }

    adjustView();
}

XShortcuts *XShortcutstScrollArea::getShortcuts()
{
    return g_pShortcuts;
}

XOptions *XShortcutstScrollArea::getGlobalOptions()
{
    return g_pXOptions;
}

bool XShortcutstScrollArea::isActive()
{
    return g_bIsActive;
}

void XShortcutstScrollArea::setActive(bool bState)
{
    g_bIsActive = bState;
}

bool XShortcutstScrollArea::eventFilter(QObject *pObj, QEvent *pEvent)
{
    Q_UNUSED(pObj)

    if (pEvent->type() == QEvent::FocusIn) {
        g_bIsActive = true;
        reloadShortcuts();
    } else if (pEvent->type() == QEvent::FocusOut) {
        g_bIsActive = false;
        registerShortcuts(false);
    }

    return QAbstractScrollArea::eventFilter(pObj, pEvent);
}

void XShortcutstScrollArea::adjustView()
{
    if (g_pXOptions) {
        g_pXOptions->adjustWidget(this);
    }
}

void XShortcutstScrollArea::reloadShortcuts()
{
    registerShortcuts(false);
    registerShortcuts(true);
}

QColor XShortcutstScrollArea::getColor(TCLOLOR tcolor)
{
    return g_color[tcolor];
}

void XShortcutstScrollArea::setColor(TCLOLOR tcolor, QColor color)
{
    g_color[tcolor] = color;
}

QColor XShortcutstScrollArea::getColorSelected(QColor color)
{
    color.setAlpha(50);
    color = color.darker(150);

    return color;
}

QColor XShortcutstScrollArea::getColorSelected(QWidget *pWidget)
{
    QColor colorBackground = pWidget->palette().window().color();
    return getColorSelected(colorBackground);
}
