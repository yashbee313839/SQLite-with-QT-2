#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QModelIndex>
class QUdpSocket;
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

public slots:
    void DatagramRecv();
private:
    Ui::Dialog *ui;
    QUdpSocket *socket;
};

#endif // DIALOG_H
