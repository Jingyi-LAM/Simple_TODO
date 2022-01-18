#ifndef TODOLISTWIDGET_H
#define TODOLISTWIDGET_H

#include <QWidget>
#include "DomParser.h"
#include "ToDoItem.h"

namespace Ui {
class ToDoListWidget;
}

class ToDoListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ToDoListWidget(QWidget *parent = nullptr);
    ~ToDoListWidget();

    ToDoItem *AddToDoItem(const struct ItemContent &itemContent);
    void CheckItemDone(ToDoItem *item, bool isDone);

    void SlotCheckboxToggle(bool checked);
    void SlotDeleteItem(void);

private:
    Ui::ToDoListWidget *mUi;
    DomParser mDomParser;
    QList<struct ItemContent> mItemContents;
    QList<ToDoItem *> mToDoItems;
};

#endif // TODOLISTWIDGET_H
