#include "transaction.h"

Transaction::Transaction()
{
    id = 0;
    quantity = 0;
    subtotal = 0.0;
    total = 0.0;
//    itemPurchased = Item("", "");
    transactionDate = "";
}

Transaction::Transaction(QString transDate, int ID, QString itemName, double itemPrice, int quantityPur, double transSub, double transTotal)
                        : Item(itemName, itemPrice)
{
    transactionDate = transDate;
    id = ID;
//    itemPurchased = itemPur;
    quantity = quantityPur;
    subtotal = transSub;
    total = transTotal;
}

QString Transaction::GetTransactionDate() const
{
    return transactionDate;
}

int Transaction::GetBuyersID() const
{
    return id;
}

int Transaction::GetQuantityPurchased() const
{
    return quantity;
}

double Transaction::GetSubTotal() const
{
    return subtotal;
}

double Transaction::GetTotal() const
{
    return total;
}
