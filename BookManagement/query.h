#ifndef QUERY_H
#define QUERY_H

#include "model.h"
#include <QDialog>
#include<QStandardItem>
#include<QStandardItemModel>

namespace Ui {
class query;
}

class query : public QDialog
{
    Q_OBJECT

public:
    explicit query(const Model &model, QWidget *parent = nullptr);
    ~query();
    QList<Book> doQuery(const int &index,const QString &content);
    void display(int row, Book bk);
    static bool comp(const Book &a, const Book &b);


private slots:
    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::query *ui;
    const Model *pModel;
    QStandardItemModel * itemModel;
};

#endif // QUERY_H
