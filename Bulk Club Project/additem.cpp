#include "additem.h"
#include "ui_additem.h"

//additem::additem(QWidget *parent) :
//    QDialog(parent),
//    ui(new Ui::additem)
//{
//    ui->setupUi(this);
//}

additem::~additem()
{
    delete ui;
}

//void additem::on_addButton_clicked()
//{
//    QString name;
//    double price;

//    name = ui->itemName->text();
//    price = ui->itemPrice->value();

//    if(!myDB.ItemExists(Item(name,price)))
//    {
//        if(myDB.AddItem(Item(name, price)))
//        {
//            ui->message->setText("Item Added");
//            emit itemAdded();
//        }
//        else
//        {
//            ui->message->setText("Failed To Add Item'");
//        }
//    }
//    else
//    {
//        ui->message->setText("Item already exists");
//    }
//}
