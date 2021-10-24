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
#include "dialogshortcuts.h"
#include "ui_dialogshortcuts.h"

DialogShortcuts::DialogShortcuts(QWidget *pParent) :
    QDialog(pParent),
    ui(new Ui::DialogShortcuts)
{
    ui->setupUi(this);

    g_pFilter=new QSortFilterProxyModel(this);

    ui->lineEditShortcut->setEnabled(false);
    ui->lineEditShortcut->installEventFilter(this);
}

DialogShortcuts::~DialogShortcuts()
{
    delete ui;
}

void DialogShortcuts::setData(XShortcuts *pShortcuts)
{
    g_pShortcuts=pShortcuts;

    QList<XShortcuts::ID> listIDs=pShortcuts->getShortcutsIDs();

    qint32 nNumberOfRecords=listIDs.count();

    g_pModel=new QStandardItemModel(nNumberOfRecords,3);
    g_pModel->setHeaderData(COLUMN_GROUP,Qt::Horizontal,tr("Group"));
    g_pModel->setHeaderData(COLUMN_NAME,Qt::Horizontal,tr("Name"));
    g_pModel->setHeaderData(COLUMN_SHORTCUT,Qt::Horizontal,tr("Shortcut"));

    for(qint32 i=0;i<nNumberOfRecords;i++)
    {
        XShortcuts::ID idShortcut=listIDs.at(i);

        XShortcuts::GROUPID groupId=XShortcuts::getGroupId(idShortcut);
        XShortcuts::GROUPID subgroupId=XShortcuts::getSubgroupId(idShortcut);

        QString sGroup=XShortcuts::groupIdToString(groupId);
        QString sSubgroup=XShortcuts::groupIdToString(subgroupId);

        if(subgroupId!=XShortcuts::GROUPID_UNKNOWN)
        {
            sGroup+=QString(" -> %1").arg(sSubgroup);
        }

        QStandardItem *pTypeGroup=new QStandardItem;
        pTypeGroup->setText(sGroup);
        g_pModel->setItem(i,COLUMN_GROUP,pTypeGroup);

        QStandardItem *pTypeName=new QStandardItem;
        pTypeName->setText(XShortcuts::idToString(idShortcut));
        g_pModel->setItem(i,COLUMN_NAME,pTypeName);

        QStandardItem *pTypeShortcut=new QStandardItem;
        pTypeShortcut->setText(pShortcuts->getShortcut(idShortcut).toString(QKeySequence::NativeText));
        pTypeShortcut->setData(idShortcut);
        g_pModel->setItem(i,COLUMN_SHORTCUT,pTypeShortcut);
    }

    g_pFilter->setSourceModel(g_pModel);
    ui->tableViewShortcuts->setModel(g_pFilter);

    ui->tableViewShortcuts->setColumnWidth(COLUMN_GROUP,150);       // TODO
    ui->tableViewShortcuts->setColumnWidth(COLUMN_NAME,200);        // TODO
    ui->tableViewShortcuts->setColumnWidth(COLUMN_SHORTCUT,200);    // TODO

    connect(ui->tableViewShortcuts->selectionModel(),
            SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            SLOT(onCellChanged(QItemSelection,QItemSelection)));
}

bool DialogShortcuts::eventFilter(QObject *pObj, QEvent *pEvent)
{
    if(pObj==ui->lineEditShortcut)
    {
        if(pEvent->type()==QEvent::KeyPress)
        {
            QKeyEvent *pKeyEvent=static_cast<QKeyEvent *>(pEvent);
            Qt::Key key=static_cast<Qt::Key>(pKeyEvent->key());

            // Only modifiers without keys
            if( (key==Qt::Key_Control)||
                (key==Qt::Key_Shift)||
                (key==Qt::Key_Alt)||
                (key==Qt::Key_Meta))
            {
                return false;
            }

            Qt::KeyboardModifiers kbModifiers=pKeyEvent->modifiers();

            qint32 nKey=key;

            if(kbModifiers&Qt::ShiftModifier)       nKey+=Qt::SHIFT;
            if(kbModifiers&Qt::ControlModifier)     nKey+=Qt::CTRL;
            if(kbModifiers&Qt::AltModifier)         nKey+=Qt::ALT;
            if(kbModifiers&Qt::MetaModifier)        nKey+=Qt::META;

            QKeySequence keyValue=QKeySequence(nKey);

            QString sText=keyValue.toString(QKeySequence::NativeText);

            if(g_pModel)
            {
                int nRow=ui->tableViewShortcuts->currentIndex().row();

                if(nRow<g_pModel->rowCount())
                {
                    QStandardItem *pItem=g_pModel->item(nRow,COLUMN_SHORTCUT);
                    XShortcuts::ID idShortcut=(XShortcuts::ID)(pItem->data().toUInt());

                    if(g_pShortcuts->checkShortcut(idShortcut,keyValue))
                    {
                        pItem->setText(sText);
                        g_pShortcuts->setShortcut(idShortcut,keyValue);
                        ui->lineEditShortcut->setText(sText);
                    }
                    else
                    {
                        QString sGroup=XShortcuts::groupIdToString(XShortcuts::getGroupId(idShortcut));
                        QString sErrorMessage=QString("%1: %2").arg(tr("Cannot set shortcut"),sText);
                        QMessageBox::critical(XOptions::getMainWidget(this),sGroup,sErrorMessage);
                    }
                }
            }

            return true;
        }
    }

    return QObject::eventFilter(pObj,pEvent);
}

void DialogShortcuts::on_lineEditFilter_textChanged(const QString &sString)
{
    g_pFilter->setFilterRegExp(sString);
    g_pFilter->setFilterCaseSensitivity(Qt::CaseInsensitive);
    g_pFilter->setFilterKeyColumn(COLUMN_NAME);
}

void DialogShortcuts::onCellChanged(const QItemSelection &itemSelected, const QItemSelection &itemDeselected)
{
    Q_UNUSED(itemDeselected)

    QModelIndexList listSelected=itemSelected.indexes();

    if(listSelected.count()>=3)
    {
        QString sShortcut=listSelected.at(COLUMN_SHORTCUT).data().toString();
        ui->lineEditShortcut->setEnabled(true);
        ui->lineEditShortcut->setText(sShortcut);
    }
}

void DialogShortcuts::on_pushButtonClose_clicked()
{
    this->close();
}

void DialogShortcuts::on_pushButtonClear_clicked()
{
    ui->lineEditShortcut->clear();

    if(g_pModel)
    {
        int nRow=ui->tableViewShortcuts->currentIndex().row();

        if(nRow<g_pModel->rowCount())
        {
            QStandardItem *pItem=g_pModel->item(nRow,COLUMN_SHORTCUT);
            XShortcuts::ID idShortcut=(XShortcuts::ID)(pItem->data().toUInt());

            pItem->setText("");
            ui->lineEditShortcut->setText("");
            g_pShortcuts->setShortcut(idShortcut,QKeySequence());
        }
    }
}
