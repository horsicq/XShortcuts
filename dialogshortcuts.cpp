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
}

DialogShortcuts::~DialogShortcuts()
{
    delete ui;
}

void DialogShortcuts::setData(XShortcuts *pShortcuts)
{
    g_pShortcuts=pShortcuts;

    QList<XShortcuts::ID> listIDs=pShortcuts->getShortcutsIDs();

    int nNumberOfRecords=listIDs.count();

    QStandardItemModel *pModel=new QStandardItemModel(nNumberOfRecords,3);
    pModel->setHeaderData(0,Qt::Horizontal,tr("Group"));
    pModel->setHeaderData(1,Qt::Horizontal,tr("Name"));
    pModel->setHeaderData(2,Qt::Horizontal,tr("Shortcut"));

    for(int i=0;i<nNumberOfRecords;i++)
    {
        XShortcuts::ID idShortcut=listIDs.at(i);

        QStandardItem *pTypeGroup=new QStandardItem;
        pTypeGroup->setText(XShortcuts::idToGroupString(idShortcut));
        pModel->setItem(i,0,pTypeGroup);

        QStandardItem *pTypeName=new QStandardItem;
        pTypeName->setText(XShortcuts::idToString(idShortcut));
        pModel->setItem(i,1,pTypeName);

        QStandardItem *pTypeShortcut=new QStandardItem;
        pTypeShortcut->setText(pShortcuts->getShortcut(idShortcut).toString());
        pModel->setItem(i,2,pTypeShortcut);
    }

    g_pFilter->setSourceModel(pModel);
    ui->tableViewShortcuts->setModel(g_pFilter);

    ui->tableViewShortcuts->setColumnWidth(0,100);  // TODO
    ui->tableViewShortcuts->setColumnWidth(1,200); // TODO
    ui->tableViewShortcuts->setColumnWidth(2,100); // TODO
}

void DialogShortcuts::on_lineEditFilter_textChanged(const QString &sString)
{
    g_pFilter->setFilterRegExp(sString);
    g_pFilter->setFilterCaseSensitivity(Qt::CaseInsensitive);
    g_pFilter->setFilterKeyColumn(1);
}
