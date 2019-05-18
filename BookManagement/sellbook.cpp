#include "sellbook.h"
#include "ui_sellbook.h"
#include <QDebug>
#include <QMessageBox>
#include <QString>

sellBook::sellBook(Model &model, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sellBook),
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

sellBook::~sellBook()
{
    delete ui;
}

void sellBook::on_pushButton_clicked()
{
    book = nullptr;
    QString isbn = this->ui->lineEdit->text();
    if(isbn != ""){
        for (int i=0;i<pModel->bookList.length();++i) {
            if(isbn==pModel->bookList[i].getIsbn()){
                book = &pModel->bookList[i];
                display(0,*book);
            }
        }
    }

    if(book == nullptr){
        QMessageBox::warning(this,"警告","ISBN号不存在，请重新输入！","确定");
        this->ui->lineEdit->setFocus();
    }
}

void sellBook::display(int row, Book bk){

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

void sellBook::on_pushButton_2_clicked()
{
    if(book != nullptr){
        int num = this->ui->spinBox->value();

        if(this->ui->radioButton_buy->isChecked()){
            if(QMessageBox::question(this,"确认","确认购入吗？","确定","取消") == 0){
                book->stock += num;
               pModel->saveFile();
            }
        }else if (this->ui->radioButton_sell->isChecked()) {
            if(num>book->stock){
                QMessageBox::critical(this,"错误","库存不足！！！","确定");
            }else{
                if(QMessageBox::question(this,"确认","确认售出吗？","确定","取消") == 0){
                    book->stock -= num;
                   pModel->saveFile();
                }
            }

        }else{
            QMessageBox::warning(this,"警告","请选择购入或售出！","确定");
        }
        display(0,*book);
    }else{
        QMessageBox::warning(this,"警告","请先输入ISBN号","确定");
    }


}
