#include "model.h"
#include<QFile>
#include<QTextStream>
#include<QMessageBox>
#include<QDebug>
Model::Model()
{

    QString line;                                               //行内容
    QFile file("../data/data.txt");                             //创建文件对象
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)){    //文件打开方式为读写和文本模式，以读写形式打开时为了防止首次使用时数据文件不存在。
      return;
    }
    QTextStream in(&file);                                      //创建文本流对象
    while (!in.atEnd()) {           //循环（未到文件末尾）
      QString line = in.readLine();                             //逐行读取文件
      QStringList strList = line.split(" ");                    //以空格切割行内容
      Book tempBook;                                            //创建临时图书对象
      tempBook.setBook(strList);                                //导入图书数据
      bookList.append(tempBook);                                //将图书装入缓存
    }
    file.close();                                               //关闭文件

}
QStringList Model::getIsbnList(){   //取得ISBN号列表
    QStringList isbnList;
    for(int i=0;i<bookList.length();++i){
        isbnList.append(bookList.at(i).getIsbn());
    }
    return isbnList;
}


void Model::saveFile(){             //保存缓存至文件
    QFile file("data.txt");                                     //创建文件对象并打开文件
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){    //文件打开方式为写入和文本模式
        return;
    }
    QTextStream out(&file);                                     //创建文本流对象
    Book tempBook;                                              //创建临时图书对象
    for (int i=0;i<bookList.length();++i) {                     //遍历缓存列表，将图书信息写入文件
        tempBook = bookList[i];
        out << tempBook.getIsbn() << " " << tempBook.getName() << " "
            << tempBook.getWriter() << " " << tempBook.getPress() << " "
            << tempBook.getStock() << " " << tempBook.getPrice() << "\n";
    }
    file.close();                                               //关闭文件
}

QList<Collect> Model::getCollectList(const QString cType)
{
    QList<Collect> collectList;		//创建统计信息容器
    QList<QString> strTemp;				//创建临时字符串容器

    if (cType == "writer") {
        //遍历bookList取出所有作者并去重
        for (int i = 0; i < bookList.size(); i++) {
            strTemp.push_back(bookList[i].getWriter());
        }
        strRemoveDuplicates(strTemp);		//去重
        //遍历所有作者，获取作者在bookList中有几本书
        for (int j = 0; j<strTemp.size(); j++)
        {
            int count = 0;
            for (int k = 0; k < bookList.size(); k++)
            {
                if (strTemp[j] == bookList[k].getWriter())
                {
                    count++;
                }
            }
            //创建统计对象，赋值并装入统计信息容器
            Collect *co = new Collect;//创建一个统计信息对象
            co->strCollectType = strTemp[j];
            co->cAmount = count;
            collectList.push_back(*co);
            delete co;
        }
        std::sort(collectList.begin(), collectList.end(), compCollect);	//容器排序

        return collectList;
    }
    else if (cType == "press") {
        for (int i = 0; i < bookList.size(); i++) {
            strTemp.push_back(bookList[i].getPress());
        }
        strRemoveDuplicates(strTemp);
        for (int j = 0; j < strTemp.size(); j++)
        {
            int count = 0;
            for (int k = 0; k < bookList.size(); k++)
            {
                if (strTemp[j] == bookList[k].getPress())
                {
                    count++;
                }
            }
            Collect *co = new Collect;
            co->strCollectType = strTemp[j];
            co->cAmount = count;
            collectList.push_back(*co);
            delete co;
        }
        std::sort(collectList.begin(), collectList.end(), compCollect);

        return collectList;
    }
    else if (cType == "stock") {
        for (int i = 0; i < bookList.size(); i++) {
            strTemp.push_back(QString::number(bookList[i].getStock()));
        }
        strRemoveDuplicates(strTemp);
        for (int j = 0; j < strTemp.size(); j++)
        {
            int count = 0;
            for (int k = 0; k < bookList.size(); k++)
            {
                if (strTemp[j] == QString::number(bookList[k].getStock()))
                {
                    count++;
                }
            }
            Collect *co = new Collect;
            co->strCollectType = strTemp[j];
            co->cAmount = count;
            collectList.push_back(*co);
            delete co;
        }
        std::sort(collectList.begin(), collectList.end(), compCollect);

        return collectList;
    }
    else if (cType == "price") {
        for (int i = 0; i < bookList.size(); i++) {
            strTemp.push_back(QString::number(bookList[i].getPrice()));
        }
        strRemoveDuplicates(strTemp);
        for (int j = 0; j < strTemp.size(); j++)
        {
            int count = 0;
            for (int k = 0; k < bookList.size(); k++)
            {
                if (strTemp[j] == QString::number(bookList[k].getPrice()))
                {
                    count++;
                }
            }
            Collect *co = new Collect;
            co->strCollectType = strTemp[j];
            co->cAmount = count;
            collectList.push_back(*co);
            delete co;
        }
        std::sort(collectList.begin(), collectList.end(), compCollect);

        return collectList;
    }

    return collectList;
}

void Model::strRemoveDuplicates(QList<QString>& toRemove)
{
    std::sort(toRemove.begin(), toRemove.end());
    QList<QString>::iterator it = std::unique(toRemove.begin(), toRemove.end());
    toRemove.erase(it, toRemove.end());
}

bool Model::compCollect(const Collect & a, const Collect & b)
{
    if (a.cAmount > b.cAmount) {	//以数据做比较
        return true;
    }
    return false;
}


