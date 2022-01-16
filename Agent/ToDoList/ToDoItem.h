#ifndef TODOITEM_H
#define TODOITEM_H

#include <QWidget>

namespace Ui {
class ToDoItem;
}

class ToDoItem : public QWidget
{
    Q_OBJECT

public:
    explicit ToDoItem(QWidget *parent = nullptr,
                      QString title = "N/A",
                      QString type = "N/A",
                      QString date = "N/A");
    ~ToDoItem();
    QString GetTitle(void);
    QString GetType(void);
    QString GetExpectDate(void);

signals:
    void SigCheckboxToggle(bool checked);
    void SigDeleteItem(void);

private:
    Ui::ToDoItem *mUi;
    QString mTitle;
    QString mType;
    QString mDate;
};

#endif // TODOITEM_H
