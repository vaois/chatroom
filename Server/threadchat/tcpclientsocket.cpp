#include "tcpclientsocket.h"

Tcpclientsocket::Tcpclientsocket(Server *last, QTcpSocket * tcpsoc,QObject *parent):
    CC_MESSAGE("4"),
    success("1@@"),
    fail("0@@"),
    p_SPLITER("#")
{
    clientsocket=tcpsoc;
    sourcelist=last;     // sourcelist用于对server里面的列表进行更新
    connect(this->clientsocket,SIGNAL(readyRead()),this,SLOT(threadStart()));  //当有数据发送到来的时候，自动发送readyRead信号
}
void Tcpclientsocket::threadStart()
{
    Thread *thread=new Thread(this,this->clientsocket);    //创建线程对象，对数据进行接收并进行划分处理
    //以下函数均为对客户的请求进行操作，并且回复
    connect(thread,SIGNAL(sigReback(QString)),this,SLOT(slotReback(QString)));   //识别用户请求失败
    connect(thread,SIGNAL(sigSignIn(QString,QString)),this,SLOT(slotSignIn(QString,QString)));
    connect(thread,SIGNAL(sigSignOut(QString)),this,SLOT(slotSignOut(QString)));
    connect(thread,SIGNAL(sigSignUp(QString,QString)),this,SLOT(slotSignUp(QString,QString)));
    connect(thread,SIGNAL(sigSignText(QString,QString)),this,SLOT(slotSignText(QString,QString)));
    //线程完成时候清除进程
    connect(thread,SIGNAL(finished()),thread,SLOT(deleteLater()),Qt::DirectConnection);
    thread->start();  //线程启动，执行run函数
}
void Tcpclientsocket::slotReback(QString msg)
{
    this->clientsocket->write(msg.toLatin1(),msg.length());
}
void Tcpclientsocket::slotSignIn(QString name, QString password)       //客户请求登陆操作
{

    QString str=name+p_SPLITER+password;
    sourcelist->namesocket.insert(name,this->clientsocket) ;        //用户名与套接字对应存储，用于强制登出
    for(int i=0;i<sourcelist->clientdatabase.count();i++)
    {
        QString item =sourcelist->clientdatabase.at(i);
        if(!QString::compare(str,item))                             //登陆成功，加入socket列表
        {
           this->clientsocket-> write(success.toLatin1(),success.length());
           sourcelist->clientnamelist.append(name);
           sourcelist->clientsocketlist.append(this->clientsocket);
           emit upDateClientShow();
        }
    }
}
void  Tcpclientsocket::slotSignOut(QString name)              //客户请求退出
{
    for(int i=0;i<sourcelist->clientsocketlist.count();i++)    //退出该客户的套接字socket列表
    {
        QTcpSocket *item =sourcelist->clientsocketlist.at(i);
        if(item->socketDescriptor()==this->clientsocket->socketDescriptor())
        {
          sourcelist->clientsocketlist.at(i)->close();          //关闭套接字
          sourcelist->clientsocketlist.removeAt(i);
        }
    }
    for(int i=0;i<sourcelist->clientnamelist.count();i++)               //跟新客户显示列表
    {
        QString item =sourcelist->clientnamelist.at(i);
        if(!QString::compare(name,item))
        {
           sourcelist->clientnamelist.removeAt(i);
        }
    }
    emit upDateClientShow();
    this->clientsocket->write(success.toLatin1(),success.length());
}
void  Tcpclientsocket::slotSignText(QString name,QString text)     //进行群发客户端的文本信息
{
    QString str=CC_MESSAGE+name+"#"+text+"@@";
    bool ifsend=1;
    for(int i=0;i<sourcelist->allnospeakname.count();i++)   //检查该客户是否在禁言用户名单中
    {
        QString item=sourcelist->allnospeakname.at(i);
        if(name==item)
        {
            ifsend=0;
            break;
        }
    }
    if(ifsend)                                                    //禁言用户的text不发送，不显示
    {
        for(int i=0;i<sourcelist->clientsocketlist.count();i++)     //往每个客户端列表写入某个客户的聊天信息
        {
             QTcpSocket *item =sourcelist->clientsocketlist.at(i);
             item->write(str.toUtf8() ,str.toUtf8().length());
        }
        emit upDateServerShow(name,text);
    }
}
void  Tcpclientsocket::slotSignUp(QString name, QString password)     //进行注册操作
{
    QString item;
    int position;
    QString sourcename;
    for(int i=0;i<sourcelist->clientdatabase.count();i++)   //检查用户的注册信息是否与已经注册的用户重名，重名的话注册不成功
    {
       item=sourcelist->clientdatabase.at(i);
       position=item.indexOf(p_SPLITER,0);
       sourcename=item.mid(0,position);
       if(sourcename==name)
       {
           this->clientsocket-> write(fail.toLatin1(),fail.length());
           return;
       }
    }
        QString str=name+p_SPLITER+password;
        sourcelist->clientdatabase.append(str);
        this->clientsocket-> write(success.toLatin1(),success.length());
}
