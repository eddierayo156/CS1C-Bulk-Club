#include "databasemanager.h"

// https://katecpp.wordpress.com/2015/08/28/sqlite-with-qt/ helps a lot

DatabaseManager::DatabaseManager()
{
    myDB = QSqlDatabase::addDatabase("QSQLITE");
    myDB.setDatabaseName(DB_PATH);

    if( QFile::exists(DB_PATH) )
    {
        if (!myDB.open()) //be careful, SQLITE will create the db if it doesn't exist and return true.
        {
            qDebug() << "Error: could not open connection to database.";
        }
        else
        {
            qDebug() << "Database connection opened.";
        }
    }
    else
    {
        qDebug() << "Cannot open database because the DB Path does not exist.";
    }
}

DatabaseManager::~DatabaseManager()
{
     myDB = QSqlDatabase::addDatabase("QSQLITE");
    if (myDB.isOpen())
    {
        myDB.close();
    }

    qDebug() << "Destroying Databasemanager";
}

bool DatabaseManager::isOpen() const
{
    return myDB.isOpen();
}

DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager dmInstance;

    return dmInstance;
}

bool DatabaseManager::ItemExists(const Item& item) const
{
    bool exists = false;
    QSqlQuery query;
    QString itemName = item.GetItemName();
    query.prepare("SELECT itemName FROM inventory WHERE itemName = (:itemName)");
    query.bindValue(":itemName", itemName);

    if(query.exec())
    {
        if(query.next())
        {
            exists = true;
        }
    }

    return exists;
}

bool DatabaseManager::AddItem(const Item& newItem)
{
    QSqlQuery query;
    QString itemName;
    double itemPrice;

    itemName = newItem.GetItemName();
    itemPrice = newItem.GetItemPrice();

    //edit to match up with the column names of the in the SQL db
    query.prepare("INSERT INTO inventory (itemName, itemPrice) VALUES (:itemName, :itemPrice)");
    query.bindValue(":itemName", itemName);
    query.bindValue(":itemPrice", itemPrice);

    if(query.exec())
    {
        qDebug() << "addItem worked:";
        return true;
    }
    else
    {
        qDebug() << "addItem error:"
                 << query.lastError();
        return false;
    }
}

bool DatabaseManager::RemoveItem(const Item& item)
{
    QSqlQuery query;
    QString itemName = item.GetItemName();

    if(ItemExists(item))
    {
        query.prepare("DELETE FROM inventory WHERE itemName = (:itemName)");
        query.bindValue(":itemName", itemName);

        if( query.exec() )
        {
            qDebug() << "Item deleted!";
            return true;
        }
        else
        {
            qDebug() << "Delete item failed: " << query.lastError();
            return false;
        }
    }
    return false;
}

// Member functions for the Database
bool DatabaseManager::MemberExists(int& newId)
{   
    bool exists = false;
    QSqlQuery query;
    int id = newId;

    query.prepare("SELECT id FROM members WHERE id = (:id)");
    query.bindValue(":id", id);

    if(query.exec())
    {
        if(query.next())
        {
            exists = true;
        }
    }

    return exists;
}

bool DatabaseManager::AddMember(QString name, int id, QString memberType, QString expirationDate)
{
    QSqlQuery query;

    query.prepare("INSERT INTO members (name, id, memberType, expirationDate) VALUES (:name, :id, :memType, :expDate)");
    query.bindValue(":name", name);
    query.bindValue(":id", id);
    query.bindValue(":memType", memberType);
    query.bindValue(":expDate", expirationDate);

    if(query.exec())
    {
        qDebug() << "addMember success:";
        return true;
    }
    else
    {
        qDebug() << "addMember fail:"
                 << query.lastError();
        return false;
    }
}

bool DatabaseManager::deleteMember(int memberId)
{
    QSqlQuery query;
    query.prepare("DELETE FROM members WHERE id = :id");
    query.bindValue(":id", memberId);

    if( query.exec() )
    {
        qDebug() << "Member deleted!";
        return true;
    }
    else
    {
        qDebug() << "Delete member failed: " << query.lastError();
        return false;
    }
}

//bool DatabaseManager::AddTransaction(QString transactionDate, QString id, QString itemName, QString price, QString quantity, QString subtotal, QString total)
bool DatabaseManager::AddTransaction(const Transaction& newTransaction)
{
    QSqlQuery query;
    QString itemName;
    double price;
    QString transactionDate;
    int id;
    int quantity;
    double subtotal= 0;
    double total = 0;
    int priceIndex = 0;

    itemName = newTransaction.GetItemName();
    price = newTransaction.GetItemPrice();
    transactionDate = newTransaction.GetTransactionDate();
    id = newTransaction.GetBuyersID();
    quantity = newTransaction.GetQuantityPurchased();
    subtotal = newTransaction.GetSubTotal();
    total = newTransaction.GetTotal();

    query.prepare("SELECT itemPrice,quantity FROM inventory WHERE itemName = (:itemName)");
    query.bindValue(":itemName", itemName);
    if(query.exec())
    {
        priceIndex = query.record().indexOf("itemPrice");
        while(query.next())
        {
            price = query.value(priceIndex).toDouble();
        }
    }
    qDebug() << price;

    subtotal = price * quantity;
    QString::number(subtotal, 'g', 2);
    total = subtotal * 1.0775;
    QString::number(total, 'g', 2);
    qDebug() << total;

    query.prepare("INSERT INTO transactions (transactionDate,id,itemName,price,quantity,subtotal,total) VALUES (:transDate, :id, :item, :price, :quantity, :subtotal, :total)");
    query.bindValue(":transDate", transactionDate);
    query.bindValue(":id", id);
    query.bindValue(":item", itemName);
    query.bindValue(":price", price);
    query.bindValue(":quantity", quantity);
    query.bindValue(":subtotal", subtotal);
    query.bindValue(":total", total);

    if(query.exec())
    {
        qDebug() << "transaction success:";
        return true;
    }
    else
    {
        qDebug() << "transaction failed:"
                 << query.lastError();
        return false;
    }
}
