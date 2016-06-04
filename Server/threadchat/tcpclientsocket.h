#ifndef TCPCLIENTSOCKET_H
#define TCPCLIENTSOCKET_H

#include "server.h"
#include <QObject>
#include <QTcpSocket>
#include "thread.h"
#include <iostream>
#include <QString>
#include <QTcpServer>
using namespace std;
class Server;
class Tcpclientsocket:public QObject
{
    Q_OBJECT
public:
    Tcpclientsocket(Server *, QTcpSocket *, QObject *parent=0);
private:
    Server *sourcelist;
    QTcpSocket *clientsocket;
    const QString CC_MESSAGE;
    const QString success;
    const QString fail;
    const QString p_SPLITER;
signals:
    void upDateServerShow(QString,QString);
    void upDateClientShow();
public slots:
    void threadStart();
    void slotReback(QString);
    void slotSignUp(QString,QString);
    void slotSignIn(QString,QString);
    void slotSignOut(QString);
    void slotSignText(QString,QString);
};

#endif // TCPCLIENTSOCKET_H
