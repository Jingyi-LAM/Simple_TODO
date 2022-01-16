#include "ToDoItem.h"
#include "ui_ToDoItem.h"

ToDoItem::ToDoItem(QWidget *parent, QString title, QString type, QString date)
    : QWidget(parent)
    , mUi(new Ui::ToDoItem)
    , mTitle(title)
    , mType(type)
    , mDate(date)
{
    mUi->setupUi(this);
    mUi->lblTitle->setText(mTitle);
    mUi->lblType->setText(mType);
    mUi->lblDate->setText(mDate);

    connect(mUi->cbIsDone, &QCheckBox::toggled, this, [=](bool checked){
        emit SigCheckboxToggle(checked);
        if (checked) {
            mUi->lblTitle->setText("<s>" + mTitle + "</s>");
        } else {
            mUi->lblTitle->setText(mTitle);
        }
    });

    connect(mUi->btnDelete, &QPushButton::clicked, this, &ToDoItem::SigDeleteItem);
}

ToDoItem::~ToDoItem()
{
    delete mUi;
}

QString ToDoItem::GetTitle(void)
{
    return mTitle;
}

QString ToDoItem::GetType(void)
{
    return mType;
}

QString ToDoItem::GetExpectDate(void)
{
    return mDate;
}
