#ifndef ADDITEM_H
#define ADDITEM_H

#include <QDialog>
#include <QDebug>
#include "databasemanager.h"

namespace Ui {
class additem;
}

class additem : public QDialog
{
    Q_OBJECT

public:
    explicit additem(QWidget *parent = 0);
    ~additem();

private slots:
    void on_addButton_clicked();

signals:
    void itemAdded();
private:
    Ui::additem *ui;
    QSqlDatabase myDB;
};

#endif // ADDITEM_H
