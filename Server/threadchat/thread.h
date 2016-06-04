#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <QtNetwork>
#include <QTcpSocket>
#include <iostream>
#include "protocol.h"
using namespace std;
class QTcpSocket;
class Thread:public QThread
{
    Q_OBJECT
public:
    Thread(QObject *parent,QTcpSocket *);
   void run();
private:
   QTcpSocket *clientsocket;
   int socketdesc;
   char buf[1024];
   string msg;
   QString success="1@@";
   QString fail="0@@";
public slots:
signals:
   void sigReback(QString);
   void sigSignUp(QString,QString);
   void sigSignIn(QString,QString);
   void sigSignOut(QString);
   void sigSignText(QString,QString);
};

#endif // THREAD_H
