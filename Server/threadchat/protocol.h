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
    void reBackSuccess(QTcpSocket *);
    void reBackFail(QTcpSocket *);
private:
    string recmessage;
    const QString CC_SIGNUP="2";
    const QString CC_SIGNIN= "3";
    const QString CC_MESSAGE ="4";
    const QString CC_SIGNOUT ="5";
    const QString CC_SUCCESS ="1";
    const QString CC_FAIL= "9";
    const QString  p_SERVERPORT ="1111";
    const QString  p_ENCOODING ="utf-8";
    const QString p_ENDOFDATA ="@@";
    const QString p_SPLITER  ="#";
    QString success="1@@";
    QString fail="0@@";
public:
    QString name;
    QString password;
    QString text;
};

#endif // PROTOCOL_H
