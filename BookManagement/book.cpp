#include "book.h"



void Book::setBook(const QList<QString>& v)
{
    this->isbn = v[0];
    this->name = v[1];
    this->writer = v[2];
    this->press = v[3];
    this->stock = v[4].toInt();
    this->price = v[5].toDouble();
}

//bool Book::operator==(const Book &other){               //重载运算符==
//    if(this->getIsbn().compare(other.getIsbn()) == 0){
//        return true;
//    }else {
//        return false;
//    }
//}

//bool Book::operator<(const Book &other){                //重载运算符 <
//    if(this->getStock() < other.getStock()){
//        return false;
//    }
//    else if(this->getStock() == other.getStock() || this->getPrice() < other.getPrice()){
//        return false;
//    }
//    return true;
//}
