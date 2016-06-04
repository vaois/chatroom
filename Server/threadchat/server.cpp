#include "server.h"

Server::Server(QObject *parent)
       :QTcpServer(parent),
         port(1111)
{
    cout<<listen(QHostAddress::Any,port)<<endl;    //对任何的Ip地址和port端口进行监听
    connect(this,SIGNAL(newConnection()),this,SLOT(slotAcceptConnection()));  //有客户连接时候自动发出newConnection()信号
    clientnamelist.append("自由用户：");
    allnospeakname.append("禁言用户：");
}
Server::~Server()
{
}
void Server::slotAcceptConnection()
{
    Tcpclientsocket *clientsocket;
    clientsocket=new Tcpclientsocket(this,this->nextPendingConnection(),this);
    connect(clientsocket,SIGNAL(upDateServerShow(QString,QString)),this,SLOT(slotUpDateServerShow(QString,QString)));
    connect(clientsocket,SIGNAL(upDateClientShow()),this,SLOT(slotUpdateClientShow()));
}
void Server::slotUpDateServerShow(QString name, QString text)
{
    emit sigUpDateServerShow(name,text);
}
void Server::slotUpdateClientShow()
{
    emit sigUpdateClientShow(clientnamelist,allnospeakname);
}
void Server::slotNoSpeak(QString msg)        //以#号分割，#结束，禁言
{
   QList<QString> nospeakname;      //用于存储禁言文本框输进来的客户名字
   int possition;
   while(msg!="")         //获取输入文本框的内容，存进nospeakname列表
   {
      possition=msg.indexOf("#",0);
      nospeakname.append(msg.mid(0,possition));
      msg=msg.remove(0,possition+1);
   }
   for(int i=0;i<nospeakname.count();i++)         //更新ui界面显示的客户的状态
   {
       QString item=nospeakname.at(i);
       QString name;
       for(int j=0;j<clientnamelist.count();j++)
       {
           name=clientnamelist.at(j);
           if(name==item)
           {
               clientnamelist.removeAt(j);
               allnospeakname.append(name);
               break;
           }
       }
   }
   emit sigUpdateClientShow(clientnamelist,allnospeakname);
}
void Server::slotAllowSpeak(QString msg)         //解禁言
{
   QList<QString> nospeakname;
   int possition;
   while(msg!="")                               //获取输入文本框的内容，存进nospeakname列表
   {
      possition=msg.indexOf("#",0);
      nospeakname.append(msg.mid(0,possition));
      msg=msg.remove(0,possition+1);
   }
   for(int i=0;i<nospeakname.count();i++)      //更新ui界面显示的客户的状态
   {
       QString item=nospeakname.at(i);
       QString name;
       for(int j=0;j<allnospeakname.count();j++)
       {
           name=allnospeakname.at(j);
           if(name==item)
           {
               allnospeakname.removeAt(j);
               clientnamelist.append(name);
               break;
           }
       }
   }
   emit sigUpdateClientShow(clientnamelist,allnospeakname);
}
void Server::slotQuit(QString msg)                 //强制退出
{
    QList<QString> nospeakname;
    QString name;
    int possition;
    while(msg!="")
    {
       possition=msg.indexOf("#",0);
       nospeakname.append(msg.mid(0,possition));
       msg=msg.remove(0,possition+1);
    }
    for(int i=0;i<nospeakname.count();i++)
    {
        QString item=nospeakname.at(i);
        if(namesocket.contains(item))       //如果输入的名字在线则进行列表更新操作
        {
            cout<<"contain"<<endl;
            QTcpSocket *it=namesocket[item];
            int soc=it->socketDescriptor();
            cout<<soc<<endl;
            for(int j=0;j<clientsocketlist.count();j++)    //更新套接字列表
            {
               if(soc==clientsocketlist.at(i)->socketDescriptor())
               {
                   cout<<"delete success"<<endl;
                   clientsocketlist.at(i)->close();
                   clientsocketlist.removeAt(j);
                   namesocket.remove(item);
                   break;
               }
            }
            for(int j=0;j<allnospeakname.count();j++)     //跟新禁言名单
            {
               name=allnospeakname.at(j);
               if(name==item)
               {
                  allnospeakname.removeAt(j);
                  break;
               }
            }
            for(int j=0;j<clientnamelist.count();j++)     //跟新在线名单
             {
               name=clientnamelist.at(j);
               if(name==item)
               {
                  clientnamelist.removeAt(j);
                  break;
               }
            }
        }
    }
    emit sigUpdateClientShow(clientnamelist,allnospeakname);
}
