#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include <QtSql>
#include<QDebug>
#include <QFileInfo>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSqlDatabase  mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("/home/cfast/Desktop/Yashwant_Rithwik/database3.db");
    if(!mydb.open())
        ui->label->setText("Not connected");
    else
        ui->label->setText("Connected...");
   mydb.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Login_clicked()
{
    if(ui->lineEdit_name->text()=="2" & ui->lineEdit_password->text()=="2"){
        this->hide();
        Dialog d;
        d.setModal(true);
        d.exec();
    }
    else
        QMessageBox::warning(this,"Invlaid","Username and password is incorrect");
}
