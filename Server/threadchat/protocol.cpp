#include "protocol.h"

Protocol::Protocol(QObject *parent,string msg):
    CC_SIGNUP("2"),
    CC_SIGNIN ("3"),
    CC_MESSAGE("4"),
    CC_SIGNOUT("5"),
    CC_SUCCESS("1"),
    CC_FAIL("9"),
    p_SERVERPORT("1111"),
    p_ENCOODING("utf-8"),
    p_ENDOFDATA ("@@"),
    p_SPLITER("#"),
    success("1@@"),
    fail("0@@")
{
   recmessage=msg;
}
Protocol::~Protocol()
{
}
char Protocol::handle()
{
    char action;
    int possition=0;
    QString sourcemsg;
    sourcemsg=QString::fromStdString(recmessage);
    if(sourcemsg.startsWith(CC_SIGNUP))    //注册
    {
        sourcemsg=sourcemsg.remove(0,CC_SIGNUP.length());
        possition=sourcemsg.indexOf(p_SPLITER,0);
        name=sourcemsg.mid(0,possition);
        sourcemsg=sourcemsg.remove(0,possition+1);
        possition=sourcemsg.indexOf(p_ENDOFDATA,0);
        password=sourcemsg.mid(0,possition);
        action='U';
    }else if(sourcemsg.startsWith(CC_SIGNIN))  //登陆
    {
        sourcemsg=sourcemsg.remove(0,CC_SIGNIN.length());
        possition=sourcemsg.indexOf(p_SPLITER,0);
        name=sourcemsg.mid(0,possition);
        sourcemsg=sourcemsg.remove(0,possition+1);
        possition=sourcemsg.indexOf(p_ENDOFDATA,0);
        password=sourcemsg.mid(0,possition);
        action='I';
    }else if(sourcemsg.startsWith(CC_SIGNOUT))  //注销
    {
        sourcemsg=sourcemsg.remove(0,CC_SIGNOUT.length());
        possition=sourcemsg.indexOf(p_ENDOFDATA,0);
        name=sourcemsg.mid(0,possition);
        action='O';
    }else if(sourcemsg.startsWith(CC_MESSAGE))  //文本
    {sourcemsg=sourcemsg.remove(0,CC_MESSAGE.length());
        possition=sourcemsg.indexOf(p_SPLITER,0);
        name=sourcemsg.mid(0,possition);
        sourcemsg=sourcemsg.remove(0,possition+1);
        possition=sourcemsg.indexOf(p_ENDOFDATA,0);
        text=sourcemsg.mid(0,possition);
        action='T';
    }else
    {
       action='F';
    }
    return action;
}
void Protocol::reBackSuccess(QTcpSocket *clientsocket)
{
     clientsocket->write(success.toLatin1(),success.length());
}
void Protocol::reBackFail(QTcpSocket *clientsocket)
{
      clientsocket->write(fail.toLatin1(),fail.length());
}
