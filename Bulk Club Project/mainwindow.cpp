#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if(DatabaseManager::instance().isOpen())
    {
        ui->label_status_2->setText("Success! Connected to database");
    }
    else
    {
        ui->label_status_2->setText("Failed to connect to database");
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_login_clicked()
{
    QString username;
    QString password;

    username = ui->lineEdit_username->text();
    password = ui->lineEdit_password->text();

    if(username == "admin123" && password == "saddleback123")
    {
        ui->lineEdit_username->setText("");
        ui->lineEdit_password->setText("");
        ui->label_status->setText("");
        ui->stackedWidget->setCurrentIndex(1);
    }
    else if(username == "manager123" && password == "password123")
    {
        ui->lineEdit_username->setText("");
        ui->lineEdit_password->setText("");
        ui->label_status->setText("");
        ui->stackedWidget->setCurrentIndex(2);
    }
    else
    {

        ui->label_status->setText("Invalid Username or Password");
        ui->lineEdit_password->setText("");
    }
}
// ADMIN FUNCTIONS
// admin to add/ delete club members
void MainWindow::on_pushButton_members_clicked()
{
    QString name;
    int id;
    QString membershipType;
    int nameIndex;
    int idIndex;
    int mTIndex;
    QSqlQuery query;
    QSqlQueryModel * model = new QSqlQueryModel();

    query.prepare("SELECT name,id, memberType FROM members");
    if(query.exec())
    {
        nameIndex = query.record().indexOf("name");
        idIndex = query.record().indexOf("id");
        mTIndex = query.record().indexOf("memberType");
        while(query.next())
        {
            name = query.value(nameIndex).toString();
            qDebug() << name;
            id = query.value(idIndex).toInt();
            membershipType = query.value(mTIndex).toString();
        }
    }

    model->setQuery(query);
    ui->tableView_8->setModel(model);
    ui->stackedWidget->setCurrentIndex(3);   
}

// admin to add/ delete items in inventory list
void MainWindow::on_pushButton_inventory_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);

    QString name;
    double price;
    int nameIndex;
    int priceIndex;
    QSqlQuery query;
    QSqlQueryModel * model = new QSqlQueryModel();

    query.prepare("SELECT itemName,itemPrice, quantity FROM inventory");
    if(query.exec())
    {
        nameIndex = query.record().indexOf("itemName");
        priceIndex = query.record().indexOf("itemPrice");
        while(query.next())
        {
            name = query.value(nameIndex).toString();
            price = query.value(priceIndex).toDouble();
        }
    }

    model->setQuery(query);
    ui->tableView_9->setModel(model);
}

// determine membership status (reg/executive)
void MainWindow::on_pushButton_memberships_clicked()
{
    ui->stackedWidget->setCurrentIndex(13);
}

// STORE MANAGER FUNCTIONS
// display sales of any given day
void MainWindow::on_pushButton_sales_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

// display total purchases for all members sorted by membership number
void MainWindow::on_pushButton_purchases_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}

// display qty of each item sold sorted by item name
void MainWindow::on_pushButton_qty_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}

// display reabtes for executive members
void MainWindow::on_pushButton_rebates_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
}

// enter month to recieve memberships that are expiring
void MainWindow::on_pushButton_expirations_clicked()
{
    ui->stackedWidget->setCurrentIndex(10);
}

// enter item to display qty sold and revenue
void MainWindow::on_pushButton_item_lookup_clicked()
{
    ui->stackedWidget->setCurrentIndex(11);
}

// enter membership number or name to display total purchases for that member
void MainWindow::on_pushButton_member_lookup_clicked()
{
    ui->stackedWidget->setCurrentIndex(12);
}

// convert reg status to executive
void MainWindow::on_pushButton_convert_clicked()
{
    ui->stackedWidget->setCurrentIndex(13);
}

// BACK FUNCTIONS TO RETURN TO HUBS
// admin manage members back button
void MainWindow::on_pushButton_back_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_back_inventory_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_back_memberships_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_back_report_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_back_purchases_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_back_qty_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->qty->setValue(0);
    ui->searchBox->setText("");
    ui->revenue_3->setValue(0.0);
}

void MainWindow::on_pushButton_back_rebates_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_back_expirations_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_back_item_lookup_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_back_member_lookup_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_back_convert_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_logout_admin_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_logout_manager_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_addItem_clicked()
{
    ui->stackedWidget->setCurrentIndex(14);

}

// add item button in add item window admin
void MainWindow::on_pushButton_clicked()
{
    QString name;
    double price;

    name = ui->itemName->text();
    price = ui->addItemPrice->value();

    if(!DatabaseManager::instance().ItemExists(Item(name,price)))
    {
        if(DatabaseManager::instance().AddItem(Item(name, price)))
        {
            ui->message->setText("Item Added");
        }
        else
        {
            ui->message->setText("Failed To Add Item'");
        }
    }
    else
    {
        ui->message->setText("Item already exists");
    }
}

// exit button add item admin
void MainWindow::on_pushButton_5_clicked()
{
    QString name;
    double price;
    int nameIndex;
    int priceIndex;
    QSqlQuery query;
    QSqlQueryModel * model = new QSqlQueryModel();

    query.prepare("SELECT itemName,itemPrice, quantity FROM inventory");
    if(query.exec())
    {
        nameIndex = query.record().indexOf("itemName");
        priceIndex = query.record().indexOf("itemPrice");
        while(query.next())
        {
            name = query.value(nameIndex).toString();
            price = query.value(priceIndex).toDouble();
        }
    }

    model->setQuery(query);
    ui->tableView_9->setModel(model);
    ui->stackedWidget->setCurrentIndex(4);
}

// remove item
void MainWindow::on_pushButton_2_clicked()
{
    QString name;
    double price;

    name = ui->itemName_2->text();
    price = ui->addItemPrice->value();

    if(DatabaseManager::instance().ItemExists(Item(name,price)))
    {
        if(DatabaseManager::instance().RemoveItem(Item(name,price)))
        {
            ui->message_2->setText("Item Removed");
        }
        else
        {
            ui->message_2->setText("Failed To Remove Item'");
        }
    }
    else
    {
        ui->message_2->setText("Item Could Not Be Found");
    }
}

//ADMIN - add member button, pushed
void MainWindow::on_addMemberButton_clicked()
{
        ui->stackedWidget->setCurrentIndex(16);
}

void MainWindow::on_pushButton_addFinish_clicked()
{
    QString name;
    int id;
    QString memType;
    QString expDate;

    name    = ui->lineEdit_newName->text();
    id      = ui->addId->value();
    memType = ui->lineEdit_newMemType->text();
    expDate = ui->lineEdit_newExpDate->text();

    ui->lineEdit_newName->setText("");
    ui->addId->setValue(0);
    ui->lineEdit_newMemType->setText("");
    ui->lineEdit_newExpDate->setText("");

    if(!DatabaseManager::instance().MemberExists(id))
    {
        if(DatabaseManager::instance().AddMember(name, id, memType, expDate))
        {
            ui->label_newMemStatus->setText("MEMBER ADDED!");
        }
        else
        {
            ui->label_newMemStatus->setText("ERROR: MEMBER ALREADY EXISTS");
        }
    }
    else
    {
        ui->label_newMemStatus->setText("MEMBER COULD NOT BE DELETED");
    }
}


void MainWindow::on_SearchMembDowngrade_clicked()
{
    ui->stackedWidget->setCurrentIndex(19);
        QSqlQuery query;
        QSqlQueryModel * model = new QSqlQueryModel;
        query.prepare("SELECT name,id,rebate FROM members WHERE memberType = 'Executive' AND rebate < 120");
        query.exec();

        model->setQuery(query);
        ui->tableView_12->setModel(model);
}

// upgrade back button
void MainWindow::on_pushButton_14_clicked()
{
    ui->stackedWidget->setCurrentIndex(13);
}

void MainWindow::on_SearchMembUpgrade_clicked()
{
    ui->stackedWidget->setCurrentIndex(18);

    QSqlQuery query;
    QSqlQueryModel * model = new QSqlQueryModel;
    query.prepare("SELECT name,id,totalSpent FROM members WHERE memberType = 'Regular' AND rebate > 55 ");
    query.exec();

    model->setQuery(query);
    ui->tableView_11->setModel(model);
}

// downgrade back button
void MainWindow::on_pushButton_15_clicked()
{
    ui->stackedWidget->setCurrentIndex(13);
}

void MainWindow::on_pushButton_Exit_clicked()
{
    QString name;
    int id;
    QString membershipType;
    int nameIndex;
    int idIndex;
    int mTIndex;
    QSqlQuery query;
    QSqlQueryModel * model = new QSqlQueryModel();

    query.prepare("SELECT name,id, memberType FROM members");
    if(query.exec())
    {
        nameIndex = query.record().indexOf("name");
        idIndex = query.record().indexOf("id");
        mTIndex = query.record().indexOf("memberType");
        while(query.next())
        {
            name = query.value(nameIndex).toString();
            qDebug() << name;
            id = query.value(idIndex).toInt();
            membershipType = query.value(mTIndex).toString();
        }
    }

    model->setQuery(query);
    ui->tableView_8->setModel(model);
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pushButton_Delete_clicked()
{
    int id;
    QString name;

    id = ui->deleteMember->value();

    if(DatabaseManager::instance().MemberExists(id))
    {
        if(DatabaseManager::instance().deleteMember(id))
        {
            ui->label_deleted->setText("Member has been succesfully deleted");
        }
        else
        {
            ui->label_deleted->setText("Member failed to delete");
        }
    }
    else
    {
        ui->label_deleted->setText("Member could not be deleted");
    }
}

//admin window purchase item
void MainWindow::on_pushButton_purchase_clicked()
{
    ui->stackedWidget->setCurrentIndex(20);

}

// add transaction
void MainWindow::on_pushButton_17_clicked()
{
    QSqlQuery query;
    int id;
    QString date;
    QString itemName;
    int itemQuantity;
    double price = 0;
    double subtotal = 0;
    double total = 0;

    id = ui->enterIdPurchase->value();
    date = ui->dateEdit->text();
    itemName = ui->itemEdit->text();
    itemQuantity = ui->purchaseQuantity->value();

    if(DatabaseManager::instance().MemberExists(id))
    {
        qDebug() << "Member Exists";
        if(DatabaseManager::instance().ItemExists(Item(itemName,price)))
        {
            qDebug() << "ItemExists";
            if(DatabaseManager::instance().AddTransaction(Transaction(date, id, itemName, price, itemQuantity, subtotal, total)))
            {
                ui->message_3->setText("Transaction Added");
            }
            else
            {
                ui->message_3->setText("Transaction Failed");
            }
        }
    }
}

// checks id for transaction
void MainWindow::on_pushButton_19_clicked()
{
    QSqlQuery query;
    int member;

    member = ui->enterIdPurchase->value();
    qDebug() << member;
    if(DatabaseManager::instance().MemberExists(member))
    {
        ui->message_4->setText("Member Does Exist");
    }
    else
    {
        ui->message_4->setText("Member Does NOT Exist");
    }
}

// check item for transaction
void MainWindow::on_pushButton_20_clicked()
{
    QSqlQuery query;
    QString itemName;
    double itemPrice;

    itemName = ui->itemEdit->text();
//    itemPrice = ui->priceEdit->text();

    qDebug() << itemName;
    if(DatabaseManager::instance().ItemExists(Item(itemName, itemPrice)))
    {
        ui->message_5->setText("Item Does Exist");
    }
    else
    {
        ui->message_5->setText("Item Does NOT Exist");
    }
}


// back button for transaction
void MainWindow::on_pushButton_18_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

// admin manage members delete member clicked
void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(17);
}

void MainWindow::on_pushButton_3_clicked()
{
//    ui->stackedWidget->setCurrentIndex(3);
    QString name;
    int id;
    QString membershipType;
    int nameIndex;
    int idIndex;
    int mTIndex;
    QSqlQuery query;
    QSqlQueryModel * model = new QSqlQueryModel();

    query.prepare("SELECT name,id, memberType FROM members");
    if(query.exec())
    {
        nameIndex = query.record().indexOf("name");
        idIndex = query.record().indexOf("id");
        mTIndex = query.record().indexOf("memberType");
        while(query.next())
        {
            name = query.value(nameIndex).toString();
            qDebug() << name;
            id = query.value(idIndex).toInt();
            membershipType = query.value(mTIndex).toString();
        }
    }

    model->setQuery(query);
    ui->tableView_8->setModel(model);
    ui->stackedWidget->setCurrentIndex(3);
}



// admin remove item
void MainWindow::on_pushButton_removeItem_clicked()
{
    ui->stackedWidget->setCurrentIndex(15);
}

// exit button for remove item
void MainWindow::on_pushButton_6_clicked()
{    
    QString name;
    double price;
    int nameIndex;
    int priceIndex;
    QSqlQuery query;
    QSqlQueryModel * model = new QSqlQueryModel();

    query.prepare("SELECT itemName,itemPrice, quantity FROM inventory");
    if(query.exec())
    {
        nameIndex = query.record().indexOf("itemName");
        priceIndex = query.record().indexOf("itemPrice");
        while(query.next())
        {
            name = query.value(nameIndex).toString();
            price = query.value(priceIndex).toDouble();
        }
    }

    model->setQuery(query);
    ui->tableView_9->setModel(model);
    ui->stackedWidget->setCurrentIndex(4);
}

// total purchase sorted by number
void MainWindow::on_LoadData_clicked()
{
    const int AR_SIZE = 100;
    double priceAr[AR_SIZE] = {0};
    double subTotal[AR_SIZE] = {0};
    double totalAr[AR_SIZE] = {0.0}; // will use to output to database
    int qtyAr[AR_SIZE] = {0};
    double total = 0;
    int index = 0;

    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQuery query;

    query.prepare("SELECT id,itemName,price,quantity FROM transactions ORDER BY id ASC");
    query.exec();

    // goes through each row and stores the price value into an array to calc total
    while(query.next() && index < AR_SIZE)
    {
        priceAr[index] = query.value(2).toDouble();
        qtyAr[index] = query.value(3).toInt();
        subTotal[index] = qtyAr[index] * priceAr[index];
        totalAr[index] = subTotal[index] * 1.0775;
//        qDebug() << subTotal[index] << "  "  << totalAr[index];
        index++;
    }

    model->setQuery(query);
    ui->tableView->setModel(model);

    // calculates grand total of purchases
    for (index = 0; index < AR_SIZE; index++)
    {
        if(priceAr[index] != 0.0 && qtyAr[index] != 0)
        {
            total = total + (qtyAr[index] * priceAr[index]);
        }
    }
    ui->total->setMaximum(9999999.99);
    ui->total->setValue(total);

}

// member lookup by name/id
void MainWindow::on_pushButton_7_clicked()
{
    QString member;

    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQuery query;

    member = ui->search_edit->text();

    // goes into member database and if a name is searched, will convert their
    // name into their id to be used to look into the transactions database
    query.prepare("SELECT id FROM members WHERE name = ?");
    query.addBindValue(member);
    query.exec();

    while(query.next())
    {
        member = query.value(0).toString();
    }

    // goes into transaction database to find the members transactions based off their
    // member id
    query.prepare("SELECT itemName,price,quantity FROM transactions WHERE id = ?");
    query.addBindValue(member);
    query.exec();

    model->setQuery(query);
    ui->tableView_2->setModel(model);
}

// item look up manager
void MainWindow::on_pushButton_8_clicked()
{
    const int AR_SIZE = 25;
    QString searchItem;
    double priceAr[AR_SIZE] = {0.0};
    int qtyAr[AR_SIZE] = {0};

    double revenue = 0;
    int totalQty = 0;
    int index = 0;

    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQuery query;

    searchItem = ui->item_edit->text();

    // goes to transactions database and will go row by row to get the price and qty of each item
    // and store into an array to later be used for calculations
    query.prepare("SELECT itemName,price,quantity FROM transactions WHERE itemName = ?");
    query.addBindValue(searchItem);
    query.exec();

    while(query.next() && index < AR_SIZE)
    {
        priceAr[index] = query.value(1).toDouble();
        qtyAr[index] = query.value(2).toInt();
        index++;
    }

    // calculates revenue of purchases
    for (index = 0; index < AR_SIZE; index++)
    {
        if(priceAr[index] != 0.0 && qtyAr[index] != 0)
        {
            revenue = revenue + (qtyAr[index] * priceAr[index]);
            totalQty = totalQty + qtyAr[index];
        }
    }

    ui->revenue->setMaximum(9999999.99);
    ui->revenue->setValue(revenue);

    ui->sold->setMaximum(9999999);
    ui->sold->setValue(totalQty);

    // goes to transactions databse and outputs the item name and qty that is being searched
    query.prepare("SELECT itemName,quantity FROM transactions WHERE itemName = ?");
    query.addBindValue(searchItem);
    query.exec();
    model->setQuery(query);
    ui->tableView_3->setModel(model);

}

// search by transaction date
void MainWindow::on_pushButton_9_clicked()
{
    QString searchDate;
    const int AR_SIZE = 20;
    double priceAr[AR_SIZE] = {0.0};
    int qtyAr[AR_SIZE] = {0};
    int idAr[AR_SIZE] = {0};
    double revenue = 0;
    int totalQty = 0;
    int index = 0;
    int exeIndex = 0;
    int dateIndex = 0;
    int id;
    double tax;

    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQueryModel * model2 = new QSqlQueryModel();
    QSqlQuery query;

    searchDate = ui->date_edit->text();

    // goes to transactions database and will go row by row to get the price and qty of each item
    // and store into an array to later be used for calculations
    query.prepare("SELECT itemName,price,quantity,id FROM transactions WHERE transactionDate = ?");
    query.addBindValue(searchDate);
    query.exec();

    while(query.next() && index < AR_SIZE)
    {
        priceAr[index] = query.value(1).toDouble();
        qtyAr[index] = query.value(2).toInt();
        idAr[index]  = query.value(3).toInt();
        index++;
        dateIndex++;
    }

    // calculates revenue of purchases
    for (index = 0; index < AR_SIZE; index++)
    {
        if(priceAr[index] != 0.0 && qtyAr[index] != 0)
        {
            revenue = revenue + (qtyAr[index] * priceAr[index]);
            totalQty = totalQty + qtyAr[index];
        }
    }

    index = 0;
    tax = revenue * .0775;
    revenue = tax + revenue;

    ui->totalrevenue->setMaximum(9999999.99);
    ui->totalrevenue->setValue(revenue);

    // goes to transactions database and outputs the item name and qty that is being searched
    query.prepare("SELECT itemName,price,quantity,id FROM transactions WHERE transactionDate = ?");
    query.addBindValue(searchDate);
    query.exec();
    model->setQuery(query);
    ui->tableView_4->setModel(model);

    std::vector<int> idA;
    for(index = 0; index < AR_SIZE; index++)
    {
        int id2 = idAr[index];
        idA.push_back(id2);
    }
    QSqlQuery qry(QString("SELECT name, memberType, id FROM members WHERE id IN (?%1) ORDER BY memberType ASC")
                    .arg(QString(", ?").repeated(idA.size()-1)));
    for(int i = 0; i < idA.size(); i++)
    {
        int id2 = idAr[i];
        qry.addBindValue(id2);
    }
    qry.exec();
    model2->setQuery(qry);
    ui->tableView_10->setModel(model2);

    QString("SELECT name, memberType, id FROM members WHERE id IN (?%1) AND memberType = 'Executive'")
                        .arg(QString(", ?").repeated(idA.size()-1));
    for(int i = 0; i < idA.size(); i++)
    {
        int id2 = idAr[i];
        qry.addBindValue(id2);
    }

}

// sort by Executive in transaction Date
void MainWindow::on_pushButton_12_clicked()
{
    QString searchDate;
    const int AR_SIZE = 25;
    int idAr[AR_SIZE] = {0};
    int index = 0;
    int exeIndex = 0;
    int dateIndex = 0;
    int id;

    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQueryModel * model2 = new QSqlQueryModel();
    QSqlQuery query;

    searchDate = ui->date_edit->text();

    // goes to transactions database and will go row by row to get the price and qty of each item
    // and store into an array to later be used for calculations
    query.prepare("SELECT itemName,price,quantity,id FROM transactions WHERE transactionDate = ?");
    query.addBindValue(searchDate);
    query.exec();

    while(query.next() && index < AR_SIZE)
    {
        idAr[index]  = query.value(3).toInt();
        index++;
        dateIndex++;
    }

    // goes to transactions database and outputs the item name and qty that is being searched
    query.prepare("SELECT itemName,price,quantity, id FROM transactions WHERE transactionDate = ?");
    query.addBindValue(searchDate);
    query.exec();
    model->setQuery(query);
    ui->tableView_4->setModel(model);

    std::vector<int> idA;
    for(index = 0; index < AR_SIZE; index++)
    {
        int id2 = idAr[index];
        idA.push_back(id2);
    }
    QSqlQuery qry(QString("SELECT name, memberType, id FROM members WHERE id IN (?%1) AND memberType = 'Executive'")
                    .arg(QString(", ?").repeated(idA.size()-1)));
    for(int i = 0; i < idA.size(); i++)
    {
        int id2 = idAr[i];
        qry.addBindValue(id2);
    }
    qry.exec();
    model2->setQuery(qry);
    ui->tableView_10->setModel(model2);

    query.prepare("SELECT memberType FROM members WHERE memberType = 'Executive'");
    while(query.next())
    {
        exeIndex++;
    }
    query.exec();
}

// sort by Regular in transaction date
void MainWindow::on_pushButton_16_clicked()
{
    QString searchDate;
    const int AR_SIZE = 25;
    int idAr[AR_SIZE] = {0};
    int index = 0;
    int exeIndex = 0;
    int dateIndex = 0;
    int id;

    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQueryModel * model2 = new QSqlQueryModel();
    QSqlQuery query;

    searchDate = ui->date_edit->text();

    // goes to transactions database and will go row by row to get the price and qty of each item
    // and store into an array to later be used for calculations
    query.prepare("SELECT itemName,price,quantity,id FROM transactions WHERE transactionDate = ?");
    query.addBindValue(searchDate);
    query.exec();

    while(query.next() && index < AR_SIZE)
    {
        idAr[index]  = query.value(3).toInt();
        index++;
        dateIndex++;
    }

    // goes to transactions database and outputs the item name and qty that is being searched
    query.prepare("SELECT itemName,price, quantity, id FROM transactions WHERE transactionDate = ?");
    query.addBindValue(searchDate);
    query.exec();
    model->setQuery(query);
    ui->tableView_4->setModel(model);

    std::vector<int> idA;
    for(index = 0; index < AR_SIZE; index++)
    {
        int id2 = idAr[index];
        idA.push_back(id2);
    }
    int regularIndex = 0;
    QSqlQuery qry(QString("SELECT name, memberType, id FROM members WHERE id IN (?%1) AND memberType = 'Regular'")
                    .arg(QString(", ?").repeated(idA.size()-1)));
    for(int i = 0; i < idA.size(); i++)
    {
        int id2 = idAr[i];
        qry.addBindValue(id2);
    }
    qry.exec();
    model2->setQuery(qry);
    ui->tableView_10->setModel(model2);
}

// search who expires with the month
void MainWindow::on_pushButton_10_clicked()
{
    int nameIndex;
    int idIndex;
    int mTypeIndex;
    int expDateIndex;
    QString name;
    int id;
    QString membershipType;
    QString expDate;
    QDate expirationDate;
    QDate searchMonth;
    QString searchMonth2;
    QSqlQuery query;
    QSqlQueryModel * model = new QSqlQueryModel;

    searchMonth2 = ui->month->text();
    searchMonth = QDate::fromString(searchMonth2, "MM");
    ui->listWidget->clear();
    ui->listWidget_2->clear();
    ui->listWidget_3->clear();

    query.prepare("SELECT name,id,memberType,expirationDate FROM members");
    if(query.exec())
    {
        nameIndex       = query.record().indexOf("name");
        idIndex         = query.record().indexOf("id");
        mTypeIndex      = query.record().indexOf("memberType");
        expDateIndex    = query.record().indexOf("expirationDate");
        while(query.next())
        {
            expDate = query.value(expDateIndex).toString();
            expirationDate = QDate::fromString(expDate, "MM/dd/yyyy");
            if(searchMonth.month() == expirationDate.month())
            {
                membershipType   = query.value(mTypeIndex).toString();
                name    = query.value(nameIndex).toString();
                id      = query.value(idIndex).toInt();
                QString idString = QString::number(id);
                ui->listWidget->addItem(name);
                ui->listWidget_2->addItem(idString);
                ui->listWidget_3->addItem(membershipType);
                qDebug() << membershipType << name << id;
            }
        }
    }
    expirationDate = searchMonth;
    model->setQuery(query);
    ui->tableView_5->setModel(model);

}

// rebates ui
void MainWindow::on_pushButton_11_clicked()
{
    const int AR_SIZE = 25;
    double priceAr[AR_SIZE] = {0.0};
    int qtyAr[AR_SIZE] = {0};
    double subTotalAr[AR_SIZE] = {0.0};
    double totalAr[AR_SIZE] = {0.0};

    double revenue = 0;
    int totalQty = 0;
    int index = 0;

    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQueryModel * model2 = new QSqlQueryModel();
    QSqlQuery query;

    while(query.next() && index < AR_SIZE)
    {
        priceAr[index] = query.value(1).toDouble();
        qtyAr[index] = query.value(2).toInt();
        index++;
    }


    // calculates revenue of purchases
    for (index = 0; index < AR_SIZE; index++)
    {
        if(priceAr[index] != 0.0 && qtyAr[index] != 0)
        {
            revenue = revenue + (qtyAr[index] * priceAr[index]);
            totalQty = totalQty + qtyAr[index];
        }
    }

    // goes to the members database and searched for membership types that are executive
    // and then outputs the members name, id, and rebate in ascending order by member id
    query.prepare("SELECT name,id,rebate FROM members WHERE memberType = 'Executive' ORDER BY id ASC");
    query.exec();

    model->setQuery(query);
    ui->tableView_6->setModel(model);

}

// quantity sold by item name
void MainWindow::on_pushButton_13_clicked()
{
    int qty;
    double price;
    double revenue;
    QString searchItem;
    QSqlQuery query;

    searchItem = ui->searchBox->text();

    //goes to db, finds item name, price, and qty from the inventory, where the item name
    //    equals the search item
    query.prepare("SELECT itemName,itemPrice, quantity FROM inventory WHERE itemName = ?");
    query.addBindValue(searchItem);
    query.exec();

    while(query.next())
    {
        price = query.value(1).toDouble();
        qty   = query.value(2).toInt();
    }
    revenue = price * qty;

    ui->qty->setMaximum(9999999);
    ui->qty->setValue(qty);
    ui->revenue_3->setMaximum(9999999.99);
    ui->revenue_3->setValue(revenue);
}


