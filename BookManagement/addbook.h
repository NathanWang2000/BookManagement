#ifndef ADDBOOK_H
#define ADDBOOK_H

#include "model.h"
#include <QDialog>
#include<QString>
#include<QList>

namespace Ui {
class addBook;
}

class addBook : public QDialog
{
    Q_OBJECT

public:
    explicit addBook( Model &model, QWidget *parent = nullptr);
    ~addBook();
    //bool isUnique(const QStringList &isbnList,const QString &isbn);
    void clearUserInterface();      //清除全部输入

private slots:
    void on_Btn_submit_clicked();

    void on_lineEdit_ISBN_editingFinished();

    void on_Btn_reset_clicked();

    void on_Btn_cancel_clicked();

private:
    Ui::addBook *ui;    //创建addbook的ui指针
    Model *pModel;      //创建Model类指针

};

#endif // ADDBOOK_H
