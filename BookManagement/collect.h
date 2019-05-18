#ifndef COLLECT_H
#define COLLECT_H

#include "model.h"
#include <QDialog>
#include<QStandardItem>
#include<QStandardItemModel>
#include<QString>


namespace Ui {
class collect;
}

class collect : public QDialog
{
    Q_OBJECT

public:
    explicit collect(Model &model, QWidget *parent = nullptr);
    ~collect();

private slots:


    void on_comboBox_currentIndexChanged(int index);
    void display(int row, Collect col);

private:
    Ui::collect *ui;
    Model *pModel;
    QStandardItemModel * itemModel;
};

#endif // COLLECT_H
