#include "ToDoListWidget.h"
#include "ui_ToDoListWidget.h"
#include <QCheckBox>
#include <QMessageBox>

const QString DEFAULT_XML_FILE_PATH = "demo.xml";

ToDoListWidget::ToDoListWidget(QWidget *parent)
    : QWidget(parent)
    , mUi(new Ui::ToDoListWidget)
    , mItemContents()
    , mToDoItems()
{
    mUi->setupUi(this);

    // Page1
    mUi->dteExpectDate->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
    mUi->dteExpectDate->setCalendarPopup(true);
    mUi->dteExpectDate->setDateTime(QDateTime::currentDateTime().addDays(1));

    connect(mUi->btnInsert, &QPushButton::clicked, this, [=](){
        if (mUi->leTitle->text().isEmpty()) {
            QMessageBox::information(this, "Insert Fail", "No title input");
            return;
        }

        struct ItemContent newItemContent(mUi->leTitle->text(),
                                          mUi->cmbType->currentText(),
                                          mUi->dteExpectDate->text(),
                                          "",
                                          "",
                                          "open");
        AddToDoItem(newItemContent);
        QMessageBox::about(this, "Insert", "Inserted an item");
    });

    connect(mUi->btnReset, &QPushButton::clicked, this, [=](){
        mUi->leTitle->setText("");
        mUi->cmbType->setCurrentIndex(0);
        mUi->dteExpectDate->setDateTime(QDateTime::currentDateTime().addDays(1));
    });

    // Page2
    mUi->vlToDoList->setDirection(QVBoxLayout::BottomToTop);
    mDomParser.ReadFile(DEFAULT_XML_FILE_PATH, mItemContents);
    for (auto i : mItemContents) {
        AddToDoItem(i);
    }

    // Page3
    mUi->vlDone->setDirection(QVBoxLayout::BottomToTop);
}

ToDoListWidget::~ToDoListWidget()
{
    mItemContents.clear();
    for (auto i : mToDoItems) {
        mItemContents.append(i->GetItemContent());
    }
    mDomParser.WriteFile(DEFAULT_XML_FILE_PATH, mItemContents);

    if (mUi) {
        delete mUi;
        mUi = NULL;
    }
}

ToDoItem *ToDoListWidget::AddToDoItem(const struct ItemContent &itemContent)
{
    ToDoItem *item = new ToDoItem(this, itemContent);
    mToDoItems.append(item);

    if (itemContent.currentStatus == "resolve")
        mUi->vlDone->addWidget(item);
    else
        mUi->vlToDoList->addWidget(item);

    connect(item, &ToDoItem::SigCheckboxToggle, this, &ToDoListWidget::SlotCheckboxToggle);
    connect(item, &ToDoItem::SigDeleteItem, this, &ToDoListWidget::SlotDeleteItem);

    return item;
}

void ToDoListWidget::CheckItemDone(ToDoItem *item, bool isDone)
{
    if (isDone) {
        mUi->vlDone->addWidget(item);
        mUi->vlToDoList->removeWidget(item);
        item->ChangeStatus(ToDoItem::Resolve);
    } else {
        mUi->vlDone->removeWidget(item);
        mUi->vlToDoList->addWidget(item);
        item->ChangeStatus(ToDoItem::Reopen);
    }
}

void ToDoListWidget::SlotCheckboxToggle(bool checked)
{
    ToDoItem *item = qobject_cast<ToDoItem *>(sender());
    CheckItemDone(item, checked);
}

void ToDoListWidget::SlotDeleteItem(void)
{
    ToDoItem *item = qobject_cast<ToDoItem *>(sender());
    mUi->vlToDoList->removeWidget(item);
    mUi->vlDone->removeWidget(item);
    mToDoItems.removeOne(item);
    if (item)
        delete item;
}
