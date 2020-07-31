#ifndef DISCUSSIONITEM_H
#define DISCUSSIONITEM_H
#include <QString>
#include <QDate>
#include <QXmlStreamWriter>

class DiscussionItem
{
protected:
    QString id;
    QString sender_id;
    QString content;
    QDate date_create;



public:
    static QString toQString(const QDate& input);
    static QDate toQDate(const QString& input);


    void setContent(const QString& content);

    QString getId();
    QString getSenderId();
    QString getContent();
    QDate getDateCreate();
    DiscussionItem(const QDate& date_create, const QString& id,const QString& sender_id,const QString& content );
    ~DiscussionItem();
    virtual void addToFile(QXmlStreamWriter & xml_writer)=0;
    virtual bool addView(const QString& ,bool)=0;
};

#endif // DISCUSSIONITEM_H
