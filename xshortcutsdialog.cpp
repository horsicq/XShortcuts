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
#include "xshortcutsdialog.h"

XShortcutsDialog::XShortcutsDialog(QWidget *pParent): QDialog(pParent)
{
    g_pShortcuts=&g_scEmpty;
    g_pXOptions=&xOptionsEmpty;
    g_bIsFocused=false;
}

void XShortcutsDialog::setGlobal(XShortcuts *pShortcuts,XOptions *pXOptions)
{
    g_pShortcuts=pShortcuts;
    g_pXOptions=pXOptions;

    if(g_bIsFocused)
    {
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

void XShortcutsDialog::adjustView()
{

}

bool XShortcutsDialog::eventFilter(QObject *pObj, QEvent *pEvent)
{
    Q_UNUSED(pObj)

    if(pEvent->type()==QEvent::FocusIn)
    {
        g_bIsFocused=true;
        registerShortcuts(true);
    }
    else if(pEvent->type()==QEvent::FocusOut)
    {
        g_bIsFocused=false;
        registerShortcuts(false);
    }

    return QDialog::eventFilter(pObj,pEvent);
}

void XShortcutsDialog::registerShortcuts(bool bState)
{
    Q_UNUSED(bState)
}
