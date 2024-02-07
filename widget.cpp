#include "widget.h"
#include "ui_widget.h"

#include <QtWidgets>
#include <QDebug>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ServerOpen();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::ServerOpen()
{
    QHostAddress hostadr;
    QList<QHostAddress> ipadrList = QNetworkInterface::allAddresses();

    if (hostadr.toString().isEmpty())
        hostadr = QHostAddress(QHostAddress::LocalHost);
    for (int i = 0; i < ipadrList.size(); i++) {
        if (ipadrList.at(i) != QHostAddress::LocalHost &&
            ipadrList.at(i).toIPv4Address()) {
            hostadr = ipadrList.at(i);
            break;
        }
    }

    tcpserver = new QTcpServer(this);
    if(!tcpserver->listen(hostadr,20000))
    {
        QMessageBox::critical(this, tr("TCP Sever"), tr("서버를 시작할 수 없습니다. 에러메세지 : %1.")
                                                         .arg(tcpserver->errorString()));
        close();
        return;
    }

    connect(tcpserver, SIGNAL(newConnection()), this, SLOT(Connection()));
    ui->te->clear();

}

void Widget::Connection()
{
    QTcpSocket *client = new QTcpSocket;
    connect(client, SIGNAL(disconnected()), client, SLOT(deleteLater()));
    QString currTime = QTime::currentTime().toString("hh시 mm분 ss초");

    QByteArray readdata = tcpclnt->readAll();
    QString message(readdata);
    qDebug() << message;

    ui->te->append(currTime);
    client->disconnectFromHost();
}
