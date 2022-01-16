#include "ToDoListWidget.h"
#include "ui_ToDoListWidget.h"
#include <QCheckBox>
#include <QMessageBox>

const QString DEFAULT_XML_FILE_PATH = "demo.xml";

ToDoListWidget::ToDoListWidget(QWidget *parent)
    : QWidget(parent)
    , mUi(new Ui::ToDoListWidget)
    , mToDoItems()
    , mFinishedItems()
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

        AddToDoItem(mUi->leTitle->text(), mUi->cmbType->currentText(), mUi->dteExpectDate->text());
        QMessageBox::about(this, "Insert", "Inserted an item");
    });

    connect(mUi->btnReset, &QPushButton::clicked, this, [=](){
        mUi->leTitle->setText("");
        mUi->cmbType->setCurrentIndex(0);
        mUi->dteExpectDate->setDateTime(QDateTime::currentDateTime().addDays(1));
    });

    // Page2
    mUi->vlToDoList->setDirection(QVBoxLayout::BottomToTop);
    mDomParser.ReadFile(DEFAULT_XML_FILE_PATH);
    for (auto i : mDomParser.GetAllItems()) {
        AddToDoItem(i.title, i.type, i.expectDate);
    }

    // Page3
    mUi->vlDone->setDirection(QVBoxLayout::BottomToTop);
}

ToDoListWidget::~ToDoListWidget()
{
    mDomParser.DeleteAllItems();
    for (auto i : mToDoItems) {
        struct ItemContent newItem(i->GetTitle(), i->GetType(), i->GetExpectDate());
        mDomParser.InsertNewItem(newItem);
    }
    mDomParser.WriteFile(DEFAULT_XML_FILE_PATH);

    if (mUi)
        delete mUi;
}

ToDoItem *ToDoListWidget::AddToDoItem(QString title, QString type, QString date)
{
    ToDoItem *item = new ToDoItem(this, title, type, date);
    mToDoItems.append(item);
    mUi->vlToDoList->addWidget(item);

    connect(item, &ToDoItem::SigCheckboxToggle, this, &ToDoListWidget::SlotCheckboxToggle);
    connect(item, &ToDoItem::SigDeleteItem, this, &ToDoListWidget::SlotDeleteItem);

    return item;
}

void ToDoListWidget::CheckItemDone(ToDoItem *item, bool isDone)
{
    if (isDone) {
        mToDoItems.removeOne(item);
        mFinishedItems.append(item);
        mUi->vlDone->addWidget(item);
        mUi->vlToDoList->removeWidget(item);
    } else {
        mFinishedItems.removeOne(item);
        mToDoItems.append(item);
        mUi->vlDone->removeWidget(item);
        mUi->vlToDoList->addWidget(item);
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
    mFinishedItems.removeOne(item);
    if (item)
        delete item;
}
