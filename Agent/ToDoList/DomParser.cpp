#include "DomParser.h"
#include <QDebug>
#include <QFile>
#include <QXmlStreamWriter>

DomParser::DomParser()
{

}

DomParser::~DomParser()
{

}

bool DomParser::ReadFile(const QString &fileName, QList<struct ItemContent> &items)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Failed to open " << fileName;
        return false;
    }

    QString errorString;
    int errorLine;
    int errorColumn;
    QDomDocument doc;

    if (!doc.setContent(&file, false, &errorString, &errorLine, &errorColumn)) {
        qDebug() << "Parse error at line " << errorLine << ", column " << errorColumn << ": " << errorString;
        return false;
    }

    QDomElement root = doc.documentElement();
    if (root.tagName() != "todo_list") {
        qDebug() << "Not a todo_list file";
        return false;
    }

    ParseToDoListElement(root, items);

    file.close();
    if (file.error()) {
        qDebug() << "Error occurred when closing " << fileName;
        return false;
    }
    return true;
}

void DomParser::ParseToDoListElement(const QDomElement &element, QList<struct ItemContent> &items)
{
    QDomNode child = element.firstChild();
    while (!child.isNull()) {
        if (child.toElement().tagName() == "item")
            ParseItemElement(child.toElement(), items);
        child = child.nextSibling();
    }
}

void DomParser::ParseItemElement(const QDomElement &element, QList<struct ItemContent> &items)
{
    struct ItemContent newItem;
    QDomNode child = element.firstChild();

    while (!child.isNull()) {
        if (child.toElement().tagName() == "title") {
            newItem.title = child.toElement().text();
        } else if (child.toElement().tagName() == "type") {
            newItem.type = child.toElement().text();
        } else if (child.toElement().tagName() == "expect_date") {
            newItem.expectDate = child.toElement().text();
        } else if (child.toElement().tagName() == "resolve_date") {
            newItem.resolveDate = child.toElement().text();
        } else if (child.toElement().tagName() == "reopen_date") {
            newItem.reopenDate = child.toElement().text();
        } else if (child.toElement().tagName() == "current_status") {
            newItem.currentStatus = child.toElement().text();
        } else {
            break;
        }
        child = child.nextSibling();
    }

    items.append(newItem);
}

bool DomParser::WriteFile(const QString &fileName, const QList<struct ItemContent> &items)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "Failed to open " << fileName;
        return false;
    }

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("todo_list");
    for (auto i : items) {
        xmlWriter.writeStartElement("item");
        xmlWriter.writeTextElement("title", i.title);
        xmlWriter.writeTextElement("type", i.type);
        xmlWriter.writeTextElement("expect_date", i.expectDate);
        xmlWriter.writeTextElement("resolve_date", i.resolveDate);
        xmlWriter.writeTextElement("reopen_date", i.reopenDate);
        xmlWriter.writeTextElement("current_status", i.currentStatus);
        xmlWriter.writeEndElement();
    }
    xmlWriter.writeEndDocument();

    file.close();
    if (file.error()) {
        qDebug() << "Error occurred when closing " << fileName;
        return false;
    }
    return true;
}



