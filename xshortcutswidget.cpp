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
#include "xshortcutswidget.h"

XShortcutsWidget::XShortcutsWidget(QWidget *pParent): QWidget(pParent)
{
    g_pShortcuts=&g_scEmpty;
    g_pXOptions=&g_xOptionsEmpty;
    g_bIsActive=false;
}

void XShortcutsWidget::setGlobal(XShortcuts *pShortcuts,XOptions *pXOptions)
{
    g_pShortcuts=pShortcuts;
    g_pXOptions=pXOptions;

    if(g_bIsActive)
    {
        registerShortcuts(false);
        registerShortcuts(true);
    }

    adjustView();
}

XShortcuts *XShortcutsWidget::getShortcuts()
{
    return g_pShortcuts;
}

XOptions *XShortcutsWidget::getGlobalOptions()
{
    return g_pXOptions;
}

void XShortcutsWidget::setActive(bool bState)
{
    g_bIsActive=bState;
}

void XShortcutsWidget::saveModel(QAbstractItemModel *pModel,QString sFileName)
{
    sFileName=QFileDialog::getSaveFileName(this,tr("Save"),sFileName,QString("%1 (*.txt);;%2 (*)").arg(tr("Text files"),tr("All files")));

    if(!sFileName.isEmpty())
    {
        if(!XOptions::saveModel(pModel,sFileName))
        {
            QMessageBox::critical(XOptions::getMainWidget(this),tr("Error"),QString("%1: %2").arg(tr("Cannot save file"),sFileName));
        }
    }
}

bool XShortcutsWidget::eventFilter(QObject *pObj,QEvent *pEvent)
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

//QSize XShortcutsWidget::sizeHint() const
//{
//    qDebug("XShortcutsWidget::sizeHint()");

//    QSize sizeHint=QWidget::sizeHint();

//    qDebug("height: %s %d",this->metaObject()->className(),sizeHint.height());

//    return sizeHint;
//}

void XShortcutsWidget::adjustView()
{

}

void XShortcutsWidget::_blockSignals(QObject **ppObjects,qint32 nCount,bool bState)
{
    for(qint32 i=0;i<nCount;i++)
    {
        if(ppObjects[i])
        {
            ppObjects[i]->blockSignals(bState);
        }
    }
}

#ifdef QT_CONCURRENT_LIB
void XShortcutsWidget::deleteOldAbstractModel(QAbstractItemModel **g_ppOldModel)
{
//#if QT_VERSION >= QT_VERSION_CHECK(6,0,0)
//    QFuture<void> future=QtConcurrent::run(&XShortcutsWidget::_deleteOldAbstractModel,this,g_ppOldModel);
//#else
//    QFuture<void> future=QtConcurrent::run(this,&XShortcutsWidget::_deleteOldAbstractModel,g_ppOldModel);
//#endif

//    return future;

    _deleteOldAbstractModel(g_ppOldModel);
}
#endif
#ifdef QT_CONCURRENT_LIB
QFuture<void> XShortcutsWidget::deleteOldStandardModel(QStandardItemModel **g_ppOldModel)
{
#if QT_VERSION >= QT_VERSION_CHECK(6,0,0)
    QFuture<void> future=QtConcurrent::run(&XShortcutsWidget::_deleteOldStandardModel,this,g_ppOldModel);
#else
    QFuture<void> future=QtConcurrent::run(this,&XShortcutsWidget::_deleteOldStandardModel,g_ppOldModel);
#endif

    return future;
}
#endif
#ifdef QT_CONCURRENT_LIB
void XShortcutsWidget::_deleteOldAbstractModel(QAbstractItemModel **g_ppOldModel)
{
    if(g_ppOldModel)
    {
        if(*g_ppOldModel)
        {
            delete (*g_ppOldModel);

            (*g_ppOldModel)=0;
        }
    }
}
#endif
#ifdef QT_CONCURRENT_LIB
void XShortcutsWidget::_deleteOldStandardModel(QStandardItemModel **g_ppOldModel)
{
    if(g_ppOldModel)
    {
        if(*g_ppOldModel)
        {
            delete (*g_ppOldModel);

            (*g_ppOldModel)=0;
        }
    }
}
#endif
void XShortcutsWidget::errorMessageSlot(QString sErrorMessage)
{
    QMessageBox::critical(XOptions::getMainWidget(this),tr("Error"),sErrorMessage);
}
