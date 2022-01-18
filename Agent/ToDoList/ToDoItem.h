#ifndef TODOITEM_H
#define TODOITEM_H

#include <QWidget>
#include "DomParser.h"

namespace Ui {
class ToDoItem;
}

struct ItemContent {
    QString title;
    QString type;
    QString expectDate;
    QString resolveDate;
    QString reopenDate;
    QString currentStatus;

    ItemContent(QString defaultTitle = "",
                QString defaultType = "",
                QString defaultEDate = "",
                QString defaultRDate = "",
                QString defaultODate = "",
                QString defaultCurrentStatus = "")
        : title(defaultTitle)
        , type(defaultType)
        , expectDate(defaultEDate)
        , resolveDate(defaultRDate)
        , reopenDate(defaultODate)
        , currentStatus(defaultCurrentStatus)
    {

    }
};

class ToDoItem : public QWidget
{
    Q_OBJECT

public:
    enum StatusType {
        Open = 0,
        Resolve,
        Reopen,
    };

    explicit ToDoItem(QWidget *parent, const struct ItemContent &itemContent);
    ~ToDoItem();
    void ChangeStatus(ToDoItem::StatusType);
    struct ItemContent GetItemContent(void);

signals:
    void SigCheckboxToggle(bool checked);
    void SigDeleteItem(void);

private:
    Ui::ToDoItem *mUi;
    struct ItemContent mItemContent;
};

#endif // TODOITEM_H
