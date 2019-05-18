#include "collect.h"
#include "ui_collect.h"
#include<QDebug>

collect::collect(Model &model,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::collect),
    pModel(&model)
{
    ui->setupUi(this);

    this->itemModel = new QStandardItemModel;   //创建Model对象

    //设置Model头
    this->itemModel->setHorizontalHeaderItem(0,new QStandardItem("类目"));
    this->itemModel->setHorizontalHeaderItem(1,new QStandardItem("汇总册数"));
    this->ui->tableView->setModel(itemModel);   //将Model绑定到View
    this->ui->label_total->clear();
}

collect::~collect()
{
    delete ui;
}


void collect::on_comboBox_currentIndexChanged(int index)
{

    switch (index) {
    case 1:
    {
        this->itemModel->clear();
        QList<Collect> collectList =pModel->getCollectList("writer");
        //设置Model头
        this->itemModel->setHorizontalHeaderItem(0,new QStandardItem("作者"));
        this->itemModel->setHorizontalHeaderItem(1,new QStandardItem("汇总册数"));
        this->ui->tableView->setModel(itemModel);   //将Model绑定到View
        int row =0;

        for (int i=0;i<collectList.length();++i) {
            display(row++,collectList[i]);
        }
        break;
    }
    case 2:
    {
        this->itemModel->clear();
        QList<Collect> collectList =pModel->getCollectList("press");
        //设置Model头
        this->itemModel->setHorizontalHeaderItem(0,new QStandardItem("出版社"));
        this->itemModel->setHorizontalHeaderItem(1,new QStandardItem("汇总册数"));
        this->ui->tableView->setModel(itemModel);   //将Model绑定到View
        int row =0;

        for (int i=0;i<collectList.length();++i) {
            display(row++,collectList[i]);
        }
        break;
    }
    case 3:
    {
        this->itemModel->clear();
        QList<Collect> collectList =pModel->getCollectList("stock");
        //设置Model头
        this->itemModel->setHorizontalHeaderItem(0,new QStandardItem("库存量"));
        this->itemModel->setHorizontalHeaderItem(1,new QStandardItem("汇总册数"));
        this->ui->tableView->setModel(itemModel);   //将Model绑定到View
        int row =0;

        for (int i=0;i<collectList.length();++i) {
            display(row++,collectList[i]);
        }
        break;
    }
    case 4:
    {
        this->itemModel->clear();
        QList<Collect> collectList =pModel->getCollectList("price");
        //设置Model头
        this->itemModel->setHorizontalHeaderItem(0,new QStandardItem("价格"));
        this->itemModel->setHorizontalHeaderItem(1,new QStandardItem("汇总册数"));
        this->ui->tableView->setModel(itemModel);   //将Model绑定到View
        int row =0;

        for (int i=0;i<collectList.length();++i) {
            display(row++,collectList[i]);
        }
        break;
    }
    }
    int n =pModel->bookList.length();
    this->ui->label_total->setText("共有图书 " + QString::number(n) + " 册");
}

void collect::display(int row, Collect col){

    for (int i=0;i<2;++i) {
        switch (i) {
        case 0:
            this->itemModel->setItem(row,i,new QStandardItem(col.strCollectType));
            break;
        case 1:
            this->itemModel->setItem(row,i,new QStandardItem(QString::number(col.cAmount)));
            break;
        default:
            break;
        }
    }

}
