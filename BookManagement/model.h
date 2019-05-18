#ifndef MODEL_H
#define MODEL_H
#include "book.h"

class Collect
{//因为会被其他类的静态成员函数调用，所以此类声明必须写在调用之前
public:
    QString strCollectType;
    int cAmount;

};


class Model
{
public:
    Model();							//构造函数


    QList<Book> bookList;				//图书数据缓存容器
    QStringList getIsbnList();		//获得图书ISBN号数据集合
    void saveFile();					//保存缓存区数据到文件
    QList<Book> getQuery(const QString qType, const QString qKeyword);				//按关键字查询
    QList<Collect> getCollectList(const QString cType);
    void strRemoveDuplicates(QList<QString>& toRemove);



    //定义Book类型比较类型，<升序，>降序（按库存量,价格顺序多重排序），
    static bool comp(const Book &a, const Book &b);/*函数必须是静态static的,否则报错*/

    static bool compCollect(const Collect & a, const Collect & b);

};

#endif // MODEL_H
