#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QObject>
#include <iostream>
#include <QTcpSocket>
using namespace std;
class Protocol:public QObject
{
    Q_OBJECT
public:
    Protocol(QObject *parent,string msg);
    ~Protocol();
    char handle();
    void reBackSuccess(QTcpSocket * );
    void reBackFail(QTcpSocket *);
private:
    string recmessage;
    const QString CC_SIGNUP;
    const QString CC_SIGNIN;
    const QString CC_MESSAGE;
    const QString CC_SIGNOUT;
    const QString CC_SUCCESS;
    const QString CC_FAIL;
    const QString  p_SERVERPORT;
    const QString  p_ENCOODING;
    const QString p_ENDOFDATA;
    const QString p_SPLITER;
    const  QString success;
    const QString fail;
public:
    QString name;
    QString password;
    QString text;
};

#endif // PROTOCOL_H
