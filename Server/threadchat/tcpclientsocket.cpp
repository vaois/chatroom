#include "tcpclientsocket.h"

Tcpclientsocket::Tcpclientsocket(Server *last, QObject *parent)
            //:QTcpSocket(parent)
{
    sourcelist=last;
    connect(this,SIGNAL(readyRead()),this,SLOT(threadStart()));
}
void Tcpclientsocket::threadStart()
{
    Thread *thread=new Thread(this,this);
    connect(thread,SIGNAL(sigReback(QString)),this,SLOT(slotReback(QString)));
    connect(thread,SIGNAL(sigSignIn(QString,QString)),this,SLOT(slotSignIn(QString,QString)));
    connect(thread,SIGNAL(sigSignOut(QString)),this,SLOT(slotSignOut(QString)));
    connect(thread,SIGNAL(sigSignUp(QString,QString)),this,SLOT(slotSignUp(QString,QString)));
    connect(thread,SIGNAL(sigSignText(QString,QString)),this,SLOT(slotSignText(QString,QString)));
    connect(thread,SIGNAL(finished()),thread,SLOT(deleteLater()),Qt::DirectConnection);
    thread->start();
}
void Tcpclientsocket::slotReback(QString msg)
{
    this->write(msg.toLatin1(),msg.length());
}
void Tcpclientsocket::slotSignIn(QString name, QString password)       //登陆
{

    QString str=name+p_SPLITER+password;
    sourcelist->namesocket.insert(name,this) ;        //用户名与套接字对应上
    for(int i=0;i<sourcelist->clientdatabase.count();i++)
    {
        QString item =sourcelist->clientdatabase.at(i);
        if(!QString::compare(str,item))                        //登陆成功，加入socket列表
        {
           this->write(success.toLatin1(),success.length());
           sourcelist->clientnamelist.append(name);
           sourcelist->clientsocketlist.append(this);
           emit upDateClientShow();
        }
    }
}
void  Tcpclientsocket::slotSignOut(QString name)
{
    for(int i=0;i<sourcelist->clientsocketlist.count();i++)    //退出socket列表
    {
        QTcpSocket *item =sourcelist->clientsocketlist.at(i);
        if(item->socketDescriptor()==this->socketDescriptor())
        {
          sourcelist->clientsocketlist.at(i)->close();         //关闭套接字
          sourcelist->clientsocketlist.removeAt(i);
        }
    }
    for(int i=0;i<sourcelist->clientnamelist.count();i++)               //跟新客户列表
    {
        QString item =sourcelist->clientnamelist.at(i);
        if(!QString::compare(name,item))
        {
           sourcelist->clientnamelist.removeAt(i);
        }
    }
    emit upDateClientShow();
    this->write(success.toLatin1(),success.length());
}
void  Tcpclientsocket::slotSignText(QString name,QString text)
{
    QString str=CC_MESSAGE+name+"#"+text+"@@";
    //this->write(str.toUtf8() ,str.toUtf8().length());
    bool ifsend=1;
    for(int i=0;i<sourcelist->allnospeakname.count();i++)
    {
        QString item=sourcelist->allnospeakname.at(i);
        if(name==item)
        {
            ifsend=0;
            break;
        }
    }
    if(ifsend)                                               //禁言用户的text不发送，不显示
    {
        for(int i=0;i<sourcelist->clientsocketlist.count();i++)     //往每个客户端列表写入新的信息
        {
             QTcpSocket *item =sourcelist->clientsocketlist.at(i);
             item->write(str.toUtf8() ,str.toUtf8().length());
        }
        emit upDateServerShow(name,text);
    }
}
void  Tcpclientsocket::slotSignUp(QString name, QString password)     //注册
{
    QString item;
    int position;
    QString sourcename;
    for(int i=0;i<sourcelist->clientdatabase.count();i++)
    {
       item=sourcelist->clientdatabase.at(i);
       position=item.indexOf(p_SPLITER,0);
       sourcename=item.mid(0,position);
       if(sourcename==name)
       {
           this->write(fail.toLatin1(),fail.length());
           return;
       }
    }
        QString str=name+p_SPLITER+password;
        sourcelist->clientdatabase.append(str);
        this->write(success.toLatin1(),success.length());
}
