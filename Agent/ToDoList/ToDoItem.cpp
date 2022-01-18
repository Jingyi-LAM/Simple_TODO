#include "ToDoItem.h"
#include "ui_ToDoItem.h"
#include <QDateTime>

ToDoItem::ToDoItem(QWidget *parent, const struct ItemContent &itemContent)
    : QWidget(parent)
    , mUi(new Ui::ToDoItem)
{
    mUi->setupUi(this);

    // Default UI
    if (itemContent.currentStatus == "resolve") {
        mUi->cbIsDone->setCheckState(Qt::Checked);
        mUi->lblTitle->setText("<s>" + itemContent.title + "</s>");
    } else {
        mUi->lblTitle->setText(itemContent.title);
    }
    mUi->lblType->setText(itemContent.type);
    mUi->lblDate->setText(itemContent.expectDate);
    mItemContent = itemContent;

    connect(mUi->cbIsDone, &QCheckBox::toggled, this, [=](bool checked){
        emit SigCheckboxToggle(checked);
        if (checked) {
            mUi->lblTitle->setText("<s>" + itemContent.title + "</s>");
        } else {
            mUi->lblTitle->setText(itemContent.title);
        }
    });

    connect(mUi->btnDelete, &QPushButton::clicked, this, &ToDoItem::SigDeleteItem);
}

ToDoItem::~ToDoItem()
{
    delete mUi;
}

void ToDoItem::ChangeStatus(ToDoItem::StatusType type)
{
    switch (type) {
    case ToDoItem::Open:
        mItemContent.currentStatus = "open";
        break;
    case ToDoItem::Resolve:
        mItemContent.currentStatus = "resolve";
        mItemContent.resolveDate = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
        break;
    case ToDoItem::Reopen:
        mItemContent.currentStatus = "reopen";
        mItemContent.reopenDate = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
        break;
    default:
        break;
    }
}

struct ItemContent ToDoItem::GetItemContent(void)
{
    return mItemContent;
}
