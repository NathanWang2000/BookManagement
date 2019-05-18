#include "updata.h"
#include "ui_updata.h"
#include <QMessageBox>
#include <QString>

updata::updata(Model &model, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::updata),
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

updata::~updata()
{
    delete ui;
}

void updata::on_pushButton_clicked()
{
    book = nullptr;
    QString isbn = this->ui->lineEdit_search->text();
    if(isbn != ""){
        for (int i=0;i<pModel->bookList.length();++i) {
            if(isbn==pModel->bookList[i].getIsbn()){
                book = &pModel->bookList[i];
                m_i = i;
                display(0,*book);
                break;
            }
        }
    }

    if(book == nullptr){
        QMessageBox::warning(this,"警告","ISBN号不存在，请重新输入！","确定");
        this->ui->lineEdit_search->setFocus();
    }
}


void updata::display(int row, Book bk){

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

void updata::on_pushButton_3_clicked()
{
    if(book != nullptr && QMessageBox::question(this,"确认","确认修改吗？","确定","取消") == 0){
        if(this->ui->lineEdit_ISBN->text() != ""){
           book->setId(this->ui->lineEdit_ISBN->text());
        }
        if(this->ui->lineEdit_name->text() != ""){
           book->setName(this->ui->lineEdit_name->text());
        }
        if(this->ui->lineEdit_writer->text() != ""){
           book->setWriter(this->ui->lineEdit_writer->text());
        }
        if(this->ui->lineEdit_press->text() != ""){
           book->setPress(this->ui->lineEdit_press->text());
        }
        if(this->ui->lineEdit_stock->text() != ""){
           book->stock = this->ui->lineEdit_stock->text().toInt();
        }
        if(this->ui->lineEdit_price->text() != ""){
           book->price = this->ui->lineEdit_price->text().toDouble();
        }
        pModel->saveFile();
        display(0,*book);
    }else if (book == nullptr) {
        QMessageBox::warning(this,"警告","请先输入ISBN号","确定");
        this->ui->lineEdit_search->setFocus();
    }

}


void updata::on_lineEdit_ISBN_editingFinished()
{
    QString isbn = this->ui->lineEdit_ISBN->text();
    if(isbn == book->getIsbn()){
        QMessageBox::information(this,"提示","修改值与原值相同","确定");
    }else if(pModel->getIsbnList().contains(isbn)){
        QMessageBox::warning(this,"错误","ISBN号已存在，请重新填写！","确定");
        this->ui->lineEdit_ISBN->clear();
        this->ui->lineEdit_ISBN->setFocus();
    }
}

void updata::on_pushButton_del_clicked()
{
    if (QMessageBox::question(this,"确认","确认删除吗？","确定","取消") == 0) {
        pModel->bookList.removeAt(m_i);
        this->itemModel->clear();           //清空表格
        //重新设置表头
        this->itemModel->setHorizontalHeaderItem(0,new QStandardItem("ISBN号"));
        this->itemModel->setHorizontalHeaderItem(1,new QStandardItem("书名"));
        this->itemModel->setHorizontalHeaderItem(2,new QStandardItem("作者"));
        this->itemModel->setHorizontalHeaderItem(3,new QStandardItem("出版社"));
        this->itemModel->setHorizontalHeaderItem(4,new QStandardItem("库存量"));
        this->itemModel->setHorizontalHeaderItem(5,new QStandardItem("价格"));
        }
}
