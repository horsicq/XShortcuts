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
#include "xshortcutsdialog.h"

XShortcutsDialog::XShortcutsDialog(QWidget *pParent, bool bMaxMinHint) : QDialog(pParent)
{
    Qt::WindowFlags _winFlags = (Qt::Window | Qt::WindowCloseButtonHint); // TODO Check

    if (bMaxMinHint) {
        _winFlags |= Qt::WindowMinMaxButtonsHint;
    }
    setWindowFlags(_winFlags);

    g_pShortcuts = &g_scEmpty;
    g_pXOptions = &g_xOptionsEmpty;
    g_bIsActive = true;
}

XShortcutsDialog::~XShortcutsDialog()
{
#ifdef QT_DEBUG
    if (g_pXOptions == &g_xOptionsEmpty) {
        qDebug("NO OPTIONS: %s", this->objectName().toLatin1().data());
    }
#endif
}

void XShortcutsDialog::setGlobal(XShortcuts *pShortcuts, XOptions *pXOptions)
{
    g_pShortcuts = pShortcuts;
    g_pXOptions = pXOptions;

    if (g_bIsActive) {
        registerShortcuts(false);
        registerShortcuts(true);
    }

    adjustView();
}

XShortcuts *XShortcutsDialog::getShortcuts()
{
    return g_pShortcuts;
}

XOptions *XShortcutsDialog::getGlobalOptions()
{
    return g_pXOptions;
}

bool XShortcutsDialog::eventFilter(QObject *pObj, QEvent *pEvent)
{
    Q_UNUSED(pObj)

    if (pEvent->type() == QEvent::FocusIn) {
        g_bIsActive = true;
        registerShortcuts(true);
    } else if (pEvent->type() == QEvent::FocusOut) {
        g_bIsActive = false;
        registerShortcuts(false);
    }

    return QDialog::eventFilter(pObj, pEvent);
}
