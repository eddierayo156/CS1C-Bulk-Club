#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QtSql>
#include "item.h"

class Transaction : public Item
{
private:
    QString  transactionDate;
    int  id;
    int  quantity;
    double  subtotal;
    double  total;
public:
    Transaction();
    Transaction(QString, int, QString, double, int, double, double);
    QString GetTransactionDate() const;
    int GetBuyersID() const;
    int GetQuantityPurchased() const;
    double GetSubTotal() const;
    double GetTotal() const;
};

#endif // TRANSACTION_H
