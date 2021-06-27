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
#include "xshortcutswidget.h"

XShortcutsWidget::XShortcutsWidget(QWidget *pParent): QWidget(pParent)
{
    g_pShortcuts=&g_scEmpty;
    g_bIsActive=false;
}

void XShortcutsWidget::setShortcuts(XShortcuts *pShortcuts)
{
    g_pShortcuts=pShortcuts;

    if(g_bIsActive)
    {
        registerShortcuts(false);
        registerShortcuts(true);
    }
}

XShortcuts *XShortcutsWidget::getShortcuts()
{
    return g_pShortcuts;
}

void XShortcutsWidget::setActive(bool bState)
{
    g_bIsActive=bState;
}

QWidget *XShortcutsWidget::getMainWidget(QWidget *pWidget)
{
    QWidget *pResult=pWidget;

    while(pResult->parent())
    {
        pResult=qobject_cast<QWidget *>(pResult->parent());
    }

    return pResult;
}

bool XShortcutsWidget::eventFilter(QObject *pObj, QEvent *pEvent)
{
    Q_UNUSED(pObj)

    if(pEvent->type()==QEvent::FocusIn)
    {
        g_bIsActive=true;
        registerShortcuts(false);
        registerShortcuts(true);
    }
    else if(pEvent->type()==QEvent::FocusOut)
    {
        g_bIsActive=false;
        registerShortcuts(false);
    }

    return QWidget::eventFilter(pObj,pEvent);
}
