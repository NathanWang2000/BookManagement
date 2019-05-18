#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addbook.h"
#include "sellbook.h"
#include "model.h"
#include "query.h"
#include "updata.h"
#include "collect.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)  //给ui指针赋值
{
    ui->setupUi(this);      //根据设计模式的数据创建ui界面

}

MainWindow::~MainWindow()
{
    delete ui;              //释放ui界面的内存
}

void MainWindow::on_actions_triggered()     //菜单信号调用
{
    addBook a(model);
    a.exec();

}

void MainWindow::on_pushButton_clicked()    //按钮信号调用
{
    addBook a(model);
    a.exec();
}

void MainWindow::on_actiont_triggered()
{
    sellBook s(model);
    s.exec();
}

void MainWindow::on_pushButton_2_clicked()
{
    sellBook s(model);

    s.exec();
}

void MainWindow::on_actiont_2_triggered()
{
    query q(model);
    q.exec();
}

void MainWindow::on_pushButton_3_clicked()
{
    query q(model);
    q.exec();
}

void MainWindow::on_actiona_triggered()
{
    updata u(model);
    u.exec();
}


void MainWindow::on_pushButton_6_clicked()
{
    updata u(model);
    u.exec();
}

void MainWindow::on_actiona_2_triggered()
{
    collect c(model);
    c.exec();
}

void MainWindow::on_pushButton_4_clicked()
{
    collect c(model);
    c.exec();
}


void MainWindow::closeEvent( QCloseEvent * event )          //重载关闭窗口事件，添加用户确认功能
{
    switch( QMessageBox::information( this, "关闭系统确认",
                                      "系统将退出，请确认！",
                                      "退出", "取消", nullptr, 1 ) )    //由于0代表空指针常量，在此用nullptr代替
 {
    case 0:
        event->accept();    //继续执行关闭事件
        break;
    case 1:
        event->ignore();    //忽略关闭事件
        break;
    default:
        break;
 }
}

void MainWindow::on_actiona_3_triggered()
{
    if( QMessageBox::information( this, "关闭系统确认",
                                      "系统将退出，请确认！",
                                  "退出", "取消", nullptr, 1 ) == 0 ){
        exit(0);
    }
}


void MainWindow::on_pushButton_5_clicked()
{
    if( QMessageBox::information( this, "关闭系统确认",
                                      "系统将退出，请确认！",
                                  "退出", "取消", nullptr, 1 ) == 0 ){
        exit(0);
    }

}


void MainWindow::on_actiong_triggered()
{
    QMessageBox::aboutQt(nullptr, "About Qt");
}

void MainWindow::on_actiona_4_triggered()
{
    QMessageBox::about(nullptr,"版本信息","天津理工大学华信软件学院2018级\n课程设计：图书管理系统 v1.00\n作者：王浩辰");
}
