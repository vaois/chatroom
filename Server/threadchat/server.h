#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>
#include <QThread>
#include <QString>
#include "tcpclientsocket.h"
#include "thread.h"
#include <QMap>
#include <iostream>
using namespace std;
class Server:public QTcpServer
{
    Q_OBJECT
public:
    Server(QObject *parent=0);
    ~Server();
    friend class Tcpclientsocket;       //声明Tcpclientsocket为友元函数
private:
    int socketDesc;
    Thread *thread;
    const int port;
    QList<QTcpSocket *> clientsocketlist;
    QList<QString> clientnamelist;
    QList<QString> clientdatabase;     //存储注册用户的信息，形式为name+“#”+password
    QMap<QString,QTcpSocket *> namesocket;
    QList<QString> allnospeakname;
signals:
    void sigUpDateServerShow(QString,QString);
    void sigUpdateClientShow(QList<QString>,QList<QString>);
public slots:
    void slotAcceptConnection();
    void slotUpDateServerShow(QString,QString);
    void slotUpdateClientShow();
    void slotAllowSpeak(QString);
    void slotNoSpeak(QString);
    void slotQuit(QString);
};

#endif // SERVER_H
