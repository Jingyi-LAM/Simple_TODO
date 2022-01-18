#ifndef DOMPARSER_H
#define DOMPARSER_H

#include <QDomElement>
#include <QWidget>
#include "ToDoItem.h"

class DomParser
{
public:
    DomParser();
    ~DomParser();

    bool ReadFile(const QString &fileName, QList<struct ItemContent> &items);
    bool WriteFile(const QString &fileName, const QList<struct ItemContent> &items);

private:
    void ParseToDoListElement(const QDomElement &element, QList<struct ItemContent> &items);
    void ParseItemElement(const QDomElement &element, QList<struct ItemContent> &items);
};

#endif // DOMPARSER_H
