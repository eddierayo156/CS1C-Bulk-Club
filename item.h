#ifndef ITEM_H
#define ITEM_H

#include <QObject>

class Item
{
private:
    QString itemName;
    double  itemPrice;
public:
    Item();
    Item(QString name, double price);

    QString GetItemName() const;
    double GetItemPrice() const;
};

#endif // ITEM_H
