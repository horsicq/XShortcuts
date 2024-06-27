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
#include "dialogshortcuts.h"

#include "ui_dialogshortcuts.h"

DialogShortcuts::DialogShortcuts(QWidget *pParent) : XShortcutsDialog(pParent), ui(new Ui::DialogShortcuts)
{
    ui->setupUi(this);

    g_pShortcuts = nullptr;
    g_pModel = nullptr;
    g_pFilter = new QSortFilterProxyModel(this);

    ui->lineEditShortcut->setEnabled(false);
    ui->lineEditShortcut->installEventFilter(this);
}

DialogShortcuts::~DialogShortcuts()
{
    delete ui;
}

void DialogShortcuts::setData(XShortcuts *pShortcuts)
{
    g_pShortcuts = pShortcuts;

    reload();
}

void DialogShortcuts::reload()
{
    // TODO remove old Model
    QList<XShortcuts::RECORD> listShortcuts = g_pShortcuts->getRecords();

    qint32 nNumberOfRecords = listShortcuts.count();

    g_pModel = new QStandardItemModel(nNumberOfRecords, 2);

    g_pModel->setHeaderData(COLUMN_NAME, Qt::Horizontal, tr("Name"));
    g_pModel->setHeaderData(COLUMN_SHORTCUT, Qt::Horizontal, tr("Shortcut"));

    for (qint32 i = 0; i < nNumberOfRecords; i++) {
        quint64 nId = listShortcuts.at(i).nId;

        XShortcuts::GROUPID groupId = XShortcuts::getGroupId(nId);
        QList<XShortcuts::GROUPID> listSubgroups = XShortcuts::getSubgroupIds(nId);
        XShortcuts::BASEID baseId = XShortcuts::getBaseId(nId);

        QString sName;
        sName += QString("%1 -> ").arg(XShortcuts::groupIdToString(groupId));

        for (qint32 j = 0; j < listSubgroups.count(); j++) {
            sName += QString("%1 -> ").arg(XShortcuts::groupIdToString(listSubgroups.at(j)));
        }

        sName += XShortcuts::baseIdToString(baseId);

        QStandardItem *pTypeName = new QStandardItem;
        pTypeName->setText(sName);
        g_pModel->setItem(i, COLUMN_NAME, pTypeName);

        QStandardItem *pTypeShortcut = new QStandardItem;
        pTypeShortcut->setText(listShortcuts.at(i).keySequence.toString(QKeySequence::NativeText));
        pTypeShortcut->setData(nId);
        g_pModel->setItem(i, COLUMN_SHORTCUT, pTypeShortcut);
    }

    g_pFilter->setSourceModel(g_pModel);
    ui->tableViewShortcuts->setModel(g_pFilter);

    ui->tableViewShortcuts->setColumnWidth(COLUMN_NAME, 350);      // TODO consts
    ui->tableViewShortcuts->setColumnWidth(COLUMN_SHORTCUT, 200);  // TODO consts

    // ui->tableViewShortcuts->sortByColumn(COLUMN_NAME, Qt::AscendingOrder);

    connect(ui->tableViewShortcuts->selectionModel(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)), SLOT(onCellChanged(QItemSelection, QItemSelection)));
}

bool DialogShortcuts::eventFilter(QObject *pObj, QEvent *pEvent)
{
    if (pObj == ui->lineEditShortcut) {
        if (pEvent->type() == QEvent::KeyPress) {
            QKeyEvent *pKeyEvent = static_cast<QKeyEvent *>(pEvent);
            Qt::Key key = static_cast<Qt::Key>(pKeyEvent->key());

            // Only modifiers without keys
            if ((key == Qt::Key_Control) || (key == Qt::Key_Shift) || (key == Qt::Key_Alt) || (key == Qt::Key_Meta)) {
                return false;
            }

            Qt::KeyboardModifiers kbModifiers = pKeyEvent->modifiers();

            qint32 nKey = key;

            if (kbModifiers & Qt::ShiftModifier) nKey += Qt::SHIFT;
            if (kbModifiers & Qt::ControlModifier) nKey += Qt::CTRL;
            if (kbModifiers & Qt::AltModifier) nKey += Qt::ALT;
            if (kbModifiers & Qt::MetaModifier) nKey += Qt::META;

            QKeySequence keyValue = QKeySequence(nKey);

            QString sText = keyValue.toString(QKeySequence::NativeText);

            if (g_pModel) {
                qint32 nRow = ui->tableViewShortcuts->currentIndex().row();

                if (nRow < g_pModel->rowCount()) {
                    QModelIndex index = ui->tableViewShortcuts->model()->index(nRow, COLUMN_SHORTCUT);

                    quint64 nId = ui->tableViewShortcuts->model()->data(index, Qt::UserRole + 1).toULongLong();

                    if (g_pShortcuts->checkShortcut(nId, keyValue)) {
                        ui->tableViewShortcuts->model()->setData(index, sText, Qt::DisplayRole);
                        g_pShortcuts->setShortcut(nId, keyValue);
                        ui->lineEditShortcut->setText(sText);
                    } else {
                        QString sGroup = XShortcuts::groupIdToString(XShortcuts::getGroupId(nId));
                        QString sErrorMessage = QString("%1: %2").arg(tr("Cannot set shortcut"), sText);

                        QMessageBox::critical(XOptions::getMainWidget(this), sGroup, sErrorMessage);
                    }
                }
            }

            return true;
        }
    }

    return QObject::eventFilter(pObj, pEvent);
}

void DialogShortcuts::on_lineEditFilter_textChanged(const QString &sString)
{
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
    g_pFilter->setFilterRegularExpression(sString);
#else
    g_pFilter->setFilterRegExp(sString);
#endif
    g_pFilter->setFilterCaseSensitivity(Qt::CaseInsensitive);
    g_pFilter->setFilterKeyColumn(COLUMN_NAME);
}

void DialogShortcuts::onCellChanged(const QItemSelection &itemSelected, const QItemSelection &itemDeselected)
{
    Q_UNUSED(itemDeselected)

    QModelIndexList listSelected = itemSelected.indexes();

    if (listSelected.count() >= 2) {
        QString sShortcut = listSelected.at(COLUMN_SHORTCUT).data().toString();
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

    if (g_pModel) {
        qint32 nRow = ui->tableViewShortcuts->currentIndex().row();

        if (nRow < g_pModel->rowCount()) {
            QModelIndex index = ui->tableViewShortcuts->model()->index(nRow, COLUMN_SHORTCUT);

            quint64 nId = ui->tableViewShortcuts->model()->data(index, Qt::UserRole + 1).toULongLong();

            ui->tableViewShortcuts->model()->setData(index, "", Qt::DisplayRole);
            ui->lineEditShortcut->setText("");
            g_pShortcuts->setShortcut(nId, QKeySequence());
        }
    }
}

void DialogShortcuts::on_pushButtonDefault_clicked()
{
    QList<XShortcuts::RECORD> listShortcuts = g_pShortcuts->getRecords();

    qint32 nNumberOfRecords = listShortcuts.count();

    for (qint32 i = 0; i < nNumberOfRecords; i++) {
        quint64 nId = listShortcuts.at(i).nId;

        g_pShortcuts->setShortcut(nId, g_pShortcuts->getDefault(nId));
    }

    reload();
}
