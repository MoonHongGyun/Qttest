#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQueryModel>
#include <QtNetwork>

class QTcpServer;
class QNetworkSession;

namespace Ui {
class Widget;
}


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

    QTcpServer *tcpserver;
    QTcpSocket *tcpclnt;
    void ServerOpen();

private slots:
    void Connection();
};
#endif // WIDGET_H
