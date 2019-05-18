#include "query.h"
#include "ui_query.h"
#include<QDebug>
#include<QMessageBox>
#include<QString>


query::query(const Model &model, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::query),
    pModel(&model)
{
    ui->setupUi(this);


    this->itemModel = new QStandardItemModel;   //创建Model对象

    //设置Model头
    this->itemModel->setHorizontalHeaderItem(0,new QStandardItem("ISBN号"));
    this->itemModel->setHorizontalHeaderItem(1,new QStandardItem("书名"));
    this->itemModel->setHorizontalHeaderItem(2,new QStandardItem("作者"));
    this->itemModel->setHorizontalHeaderItem(3,new QStandardItem("出版社"));
    this->itemModel->setHorizontalHeaderItem(4,new QStandardItem("库存量"));
    this->itemModel->setHorizontalHeaderItem(5,new QStandardItem("价格"));

    this->ui->tableView->setModel(itemModel);   //将Model绑定到View


}

query::~query()
{
    delete ui;
}

void query::on_pushButton_clicked()
{
    int index = this->ui->comboBox->currentIndex();     //获取搜索项目序号
    QString content = this->ui->lineEdit->text();       //获取搜索内容
    QList<Book> queryList = doQuery(index,content);     //获得查询结果
    std::sort(queryList.begin(),queryList.end(),comp);  //排序
    if(queryList.empty()){                              //若未查询到
        QMessageBox::warning(this,"提示","查询图书不存在！","确定");
//        this->ui->lineEdit->clear();        //清除文本框
//        this->ui->lineEdit->setFocus();     //将焦点甚至在文本框
    }else{
        this->itemModel->clear();           //清空表格
        //重新设置表头
        this->itemModel->setHorizontalHeaderItem(0,new QStandardItem("ISBN号"));
        this->itemModel->setHorizontalHeaderItem(1,new QStandardItem("书名"));
        this->itemModel->setHorizontalHeaderItem(2,new QStandardItem("作者"));
        this->itemModel->setHorizontalHeaderItem(3,new QStandardItem("出版社"));
        this->itemModel->setHorizontalHeaderItem(4,new QStandardItem("库存量"));
        this->itemModel->setHorizontalHeaderItem(5,new QStandardItem("价格"));

        this->ui->tableView->setModel(itemModel);   //重新绑定
        int row =0;
        for (int i=0;i<queryList.length();++i) {
            display(row++,queryList[i]);
        }
    }
}

QList<Book> query::doQuery(const int &index,const QString &content){
    QList<Book> queryList;      //新建列表，接收查询结果
    //先判断搜索项目，再遍历
    switch (index) {
    case 1:
        for (int i=0;i<pModel->bookList.length();++i) {
            if(content==pModel->bookList[i].getIsbn()){
                queryList.append(pModel->bookList[i]);
            }
        }
        break;
    case 2:
        for (int i=0;i<pModel->bookList.length();++i) {
            if(content==pModel->bookList[i].getName()){
                queryList.append(pModel->bookList[i]);
            }
        }
        break;
    case 3:
        for (int i=0;i<pModel->bookList.length();++i) {
            if(content==pModel->bookList[i].getWriter()){
                queryList.append(pModel->bookList[i]);
            }
        }
        break;
    case 4:
        for (int i=0;i<pModel->bookList.length();++i) {
            if(content==pModel->bookList[i].getPress()){
                queryList.append(pModel->bookList[i]);
            }
        }
        break;
    case 5:
        for (int i=0;i<pModel->bookList.length();++i) {
                queryList.append(pModel->bookList[i]);

        }
        break;
    default:
        break;
    }
    return queryList;
}

void query::display(int row, Book bk){

    for (int i=0;i<6;++i) {
        switch (i) {
        case 0:
            this->itemModel->setItem(row,i,new QStandardItem(bk.getIsbn()));
            break;
        case 1:
            this->itemModel->setItem(row,i,new QStandardItem(bk.getName()));
            break;
        case 2:
            this->itemModel->setItem(row,i,new QStandardItem(bk.getWriter()));
            break;
        case 3:
            this->itemModel->setItem(row,i,new QStandardItem(bk.getPress()));
            break;
        case 4:
            this->itemModel->setItem(row,i,new QStandardItem(QString::number(bk.stock)));
            break;
        case 5:
            this->itemModel->setItem(row,i,new QStandardItem(QString::number(bk.price)));
            break;
        default:
            break;
        }
    }

}

bool query::comp(const Book & a, const Book & b)    //设置排序规则
{
    if (a.stock > b.stock) {
        return true;
    }
    else if (a.stock == b.stock && a.price > b.price) {
        return true;
    }
    return false;
}


void query::on_comboBox_currentIndexChanged(int index)  //用户选择“图书一览”时，被调用
{
    if(index == 5){
        this->ui->lineEdit->clear();                    //清除文本框
        this->ui->lineEdit->setEnabled(false);          //设置内容编辑框失效
    }
    else{
        this->ui->lineEdit->setEnabled(true);           //设置内容编辑框有效
        this->ui->lineEdit->setFocus();
    }
}
