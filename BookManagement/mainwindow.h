#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "model.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);     //explicit 不能用等号传参
    ~MainWindow();
    void closeEvent( QCloseEvent * event );

private slots:
    void on_actions_triggered();
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_4_clicked();
    void on_actiont_triggered();
    void on_actiont_2_triggered();
    void on_actiona_triggered();
    void on_actiona_2_triggered();
    void on_actiona_3_triggered();
    void on_actiong_triggered();
    void on_actiona_4_triggered();

private:
    Ui::MainWindow *ui;
    Model model;
};

#endif // MAINWINDOW_H
