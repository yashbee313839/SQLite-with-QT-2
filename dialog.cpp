#include "dialog.h"
#include "ui_dialog.h"
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>
#include <QtCore>
#include <QtNetwork>
#include <QtGui>
#include <QString>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    socket=new QUdpSocket(this);
    socket->bind(QHostAddress::Any, 5000);
    connect(socket, SIGNAL(readyRead()), this, SLOT(DatagramRecv()));



    ui->setupUi(this);
    QSqlDatabase  mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("/home/cfast/Desktop/Yashwant_Rithwik/database3.db");
    mydb.open();
    QSqlQueryModel * modal =new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery(mydb);

    qry->prepare("select * from BH111");
    qry->exec();

    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
    mydb.close();

}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::DatagramRecv()
{
    QByteArray data;
    QHostAddress host;
    quint16 port;

    while(socket->hasPendingDatagrams()){
        qDebug()<< "Data read";
        data.resize(socket->pendingDatagramSize());
        socket->readDatagram(data.data(), data.size(), &host, &port);

        QString portStr;
        portStr.setNum(ulong(port));
        QString splitData(data);
        QStringList ex=splitData.split(' ');

        //trace->append(QString("%1:%2 -> %3").arg(host.toString(), portStr, data));
        QSqlQueryModel * modal =new QSqlQueryModel();
        QSqlDatabase  mydb = QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName("/home/cfast/Desktop/Yashwant_Rithwik/database3.db");
        mydb.open();
        QSqlQuery* qry=new QSqlQuery(mydb);
        qry->prepare("create table if not exists "+ex[0]+"(ID varchar(10),Range varchar(10),Azimuth varchar(10),Height varchar(10),Speed varchar(10),Time varchar(10))");
        if(qry->exec())
            qDebug()<<"Created";
        else
            qDebug() << "Not created";
        qry->prepare("insert into "+ex[0]+" values('"+ex[0]+"','"+ex[1]+"','"+ex[2]+"','"+ex[3]+"','"+ex[4]+"','"+ex[5]+"')");
        if(qry->exec())
            qDebug() << "Inserted";
        else
            qDebug() <<"Not Inserted";

        //QSqlQuery* qry=new QSqlQuery(mydb);
        qry->prepare("select * from BH111");
        qry->exec();

        modal->setQuery(*qry);
        ui->tableView->setModel(modal);
        mydb.close();
    }
}

