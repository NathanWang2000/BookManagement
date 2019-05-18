#include "addbook.h"
#include "ui_addbook.h"
#include "book.h"
#include<QMessageBox>
#include<QDebug>
#include<QString>
#include<QRegExpValidator>


addBook::addBook(Model &model, QWidget *parent ) :
    QDialog(parent),
    ui(new Ui::addBook),
    pModel(&model)
{
    ui->setupUi(this);

    QRegExp rxS("^(0|[1-9][0-9]*)$");                                       //正则对象，只能输入正整数
    QRegExpValidator *validatorStock = new QRegExpValidator(rxS, this);     //动态创建正则检验器并绑定正则对象
    /*
     * 这里new的指针，不用delete释放内存，因为Qt会自动delete掉。
     * 前提1：new的必须是QObject的子类.前提2：new时必须设定了父对象（本例中的this）
    */
    this->ui->lineEdit_stock->setValidator(validatorStock);                 //设置文本框的检验器

    QRegExp rxP("^[0-9]+(.[0-9]{2})?$");     //正则表达式，只能输入正浮点数
    QRegExpValidator *validatorPrice = new QRegExpValidator(rxP, this);
    this->ui->lineEdit_price->setValidator(validatorPrice);

    this->ui->lineEdit_ISBN->setFocus();    //使ISBN文本编辑框获得焦点

}

addBook::~addBook()
{
    delete ui;
}

void addBook::on_Btn_submit_clicked()        //提交按钮点击信号槽函数
{
    QString isbn = this->ui->lineEdit_ISBN->text();         //获得ISBN文本编辑框文本
    QString name = this->ui->lineEdit_name->text();
    QString writer = this->ui->lineEdit_writer->text();
    QString press = this->ui->lineEdit_press->text();
    QString stock = this->ui->lineEdit_stock->text();
    QString price = this->ui->lineEdit_price->text();
    //确认对话框内容
    QString content = "ISBN号：" + isbn + '\n' + "书名：" + name + '\n' + "作者：" + writer + '\n' + "出版社：" + press + '\n' + "库存量：" + stock + '\n' + "价格："+ price;

    int ret = -1;
    if(isbn.length()<1 || name.length()<1 || writer.length()<1 || press.length()<1 || stock.length()<1 || price.length()<1){    //检查各项是否为空
        QMessageBox::critical(this,"错误","各项信息不能为空，请继续填写！","确定");
    }else{
        ret = QMessageBox::question(this,"请确认信息",content ,"确认","取消");
    }
    Book book;
    if(ret==0){
        book.setId(isbn);
        book.setName(name);
        book.setWriter(writer);
        book.setPress(press);
        book.stock = stock.toInt();
        book.price = price.toDouble();
    }
   pModel->bookList.append(book);   //把确认后的图书对象添加到缓存列表
   pModel->saveFile();              //将缓存列表保存到硬盘文件
   clearUserInterface();           //清除全部文本框内容
   this->ui->lineEdit_ISBN->setFocus();    //使ISBN文本编辑框重新获得焦点



}

void addBook::on_lineEdit_ISBN_editingFinished()        //检查输入内容是否已存在
{
    QStringList isbnList =pModel->getIsbnList();
    QString isbn = this->ui->lineEdit_ISBN->text();
    if(isbnList.contains(isbn)){                        //如果输入内容已存在
        QMessageBox::warning(this,"错误","ISBN号已存在，请重新填写！","确定");
        this->ui->lineEdit_ISBN->clear();
        this->ui->lineEdit_ISBN->setFocus();

    }

}
//bool addBook::isUnique(const QStringList &isbnList,const QString &isbn){
//    for (int i=0;i<isbnList.length();++i) {
//        if(isbn==isbnList[i]){
//            return false;
//        }
//    }
//    return true;
//}
void addBook::clearUserInterface(){
    this->ui->lineEdit_ISBN->clear();
    this->ui->lineEdit_name->clear();
    this->ui->lineEdit_writer->clear();
    this->ui->lineEdit_press->clear();
    this->ui->lineEdit_stock->clear();
    this->ui->lineEdit_price->clear();
}

void addBook::on_Btn_reset_clicked()
{
    clearUserInterface();
    this->ui->lineEdit_ISBN->setFocus();
}

void addBook::on_Btn_cancel_clicked()
{
    this->close();
}
