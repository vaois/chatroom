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
class Tcpclientsocket:public QTcpSocket
{
    Q_OBJECT
public:
     //Tcpclientsocket(QObject *parent=0);
    Tcpclientsocket(Server *, QObject *parent=0);
private:
    Server *sourcelist;
    const QString CC_MESSAGE ="4";
    QString success="1@@";
    QString fail="0@@";
    const QString p_SPLITER  ="#";
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
