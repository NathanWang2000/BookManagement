#ifndef SELLBOOK_H
#define SELLBOOK_H

#include <QDialog>
#include "model.h"
#include <QStandardItem>
#include <QStandardItemModel>

namespace Ui {
class sellBook;
}

class sellBook : public QDialog
{
    Q_OBJECT

public:
    explicit sellBook(Model &model, QWidget *parent = nullptr);
    ~sellBook();

private slots:
    void on_pushButton_clicked();
    void display(int row, Book bk);

    void on_pushButton_2_clicked();

private:
    Ui::sellBook *ui;
    Model *pModel;
    QStandardItemModel * itemModel;
    Book *book = nullptr;
};

#endif // SELLBOOK_H
