#ifndef BOOK_H
#define BOOK_H
#include<QList>
#include<QString>

class Book
{
protected:
    QString isbn;			//ISBN号
    QString name;		//书名
    QString writer;		//作者
    QString press;		//出版社


public://因为要排序，所以下面数据成员要public 使可从对象直接访问
    int stock;		//库存量
    double price;		//单价

public:
    Book() {}		//空构造函数
    ~Book(){}		//虚析构函数



    QString getIsbn()const{return isbn;}				//返回ISBN号
    QString getName()const { return name; }
    QString getWriter()const { return writer; }
    QString getPress()const { return press; }
    void setId(const QString newIsbn) { isbn = newIsbn; }
    void setName(const QString newName) { name = newName; }
    void setWriter(const QString newWriter) { writer = newWriter; }
    void setPress(const QString newPress) { press = newPress; }
    int getStock()const { return stock; }
    double getPrice()const { return price; }

    void setBook(const QList<QString> &v);          //导入图书信息
    inline bool operator==(const Book &other);             //重载运算符 ==
    inline bool operator<(const Book &other);              //重载运算符 <


};


#endif // BOOK_H
