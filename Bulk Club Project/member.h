#ifndef MEMBER_H
#define MEMBER_H

#include <QObject>

class Member
{
private:
    QString memberName;
    QString memberId;
public:
    Member();
};


class Item
{
private:
    QString itemName;
    QString itemPrice;
public:
    Item();
    Item(QString name, QString price);

    QString GetItemName() const;
    QString GetItemPrice() const;
};

#endif // MEMBER_H
