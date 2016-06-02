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
    void incomingConnection(int socketDescriptor);
    friend class Tcpclientsocket;
private:
    int socketDesc;
    Thread *thread;
    //bool enableconnect=1;
    //ClientMessaga *clientmessage;
    //QTcpSocket *clientsocket;
    QList<QTcpSocket *> clientsocketlist;
    QList<QString> clientnamelist;
    QList<QString> clientdatabase;
    QMap<QString,QTcpSocket *> namesocket;
    QList<QString> allnospeakname;
signals:
    void sigUpDateServerShow(QString,QString);
    void sigUpdateClientShow(QList<QString>,QList<QString>);
public slots:
    void slotUpDateServerShow(QString,QString);
    void slotUpdateClientShow();
    void slotAllowSpeak(QString);
    void slotNoSpeak(QString);
    void slotQuit(QString);
};

#endif // SERVER_H
