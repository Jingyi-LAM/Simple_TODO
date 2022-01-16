#ifndef DOMPARSER_H
#define DOMPARSER_H

#include <QDomElement>
#include <QWidget>

struct ItemContent {
    QString title;
    QString type;
    QString expectDate;

    ItemContent(QString defaultTitle = "", QString defaultType = "", QString defaultEDate = "")
        : title(defaultTitle)
        , type(defaultType)
        , expectDate(defaultEDate)
    {

    }
};

class DomParser
{
public:
    DomParser();
    ~DomParser();

    bool ReadFile(const QString &fileName);
    bool WriteFile(const QString &fileName);
    const QList<struct ItemContent> GetAllItems(void);
    void InsertNewItem(struct ItemContent item);
    void DeleteAllItems(void);

private:
    void ParseToDoListElement(const QDomElement &element);
    void ParseItemElement(const QDomElement &element);
    QList<struct ItemContent> mItems;
};

#endif // DOMPARSER_H
