#ifndef UPDATA_H
#define UPDATA_H

#include <QDialog>
#include "model.h"
#include <QStandardItem>
#include <QStandardItemModel>

namespace Ui {
class updata;
}

class updata : public QDialog
{
    Q_OBJECT

public:
    explicit updata(Model &model, QWidget *parent = nullptr);
    ~updata();

private slots:
    void on_pushButton_clicked();
    void display(int row, Book bk);

    void on_pushButton_3_clicked();

    void on_lineEdit_ISBN_editingFinished();

    void on_pushButton_del_clicked();

private:
    Ui::updata *ui;

    Model *pModel;
    QStandardItemModel * itemModel;
    Book *book = nullptr;
    int m_i;
};

#endif // UPDATA_H
