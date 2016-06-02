#include "server.h"

Server::Server(QObject *parent)
       :QTcpServer(parent)
{
    clientnamelist.append("自由用户：");
    allnospeakname.append("禁言用户：");
}
Server::~Server()
{
}
void Server::incomingConnection(int socketDescriptor)        //当有客户端连接的时候该函数启动
{
         //enableconnect=0;
         //connect(thread,SIGNAL(finished()),thread,SLOT(deleteLater()));
         //socketDesc=socketDescriptor;
         Tcpclientsocket *clientsocket=new Tcpclientsocket(this,this);
         clientsocket->setSocketDescriptor(socketDescriptor);
         connect(clientsocket,SIGNAL(upDateServerShow(QString,QString)),this,SLOT(slotUpDateServerShow(QString,QString)));
         connect(clientsocket,SIGNAL(upDateClientShow()),this,SLOT(slotUpdateClientShow()));
         //clientsocketlist.append(clientsocket);         //将套接字对象写入到列表中
}
void Server::slotUpDateServerShow(QString name, QString text)
{
    emit sigUpDateServerShow(name,text);
}
void Server::slotUpdateClientShow()
{
    emit sigUpdateClientShow(clientnamelist,allnospeakname);
}
void Server::slotNoSpeak(QString msg)   //以#号分割，禁言
{
   QList<QString> nospeakname;
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
   /* for(int i=0;i<allnospeakname.count();i++)
    {
        cout<<"shuchu"<<endl;
        cout<<allnospeakname.at(i).toStdString()<<endl;
    }*/
   emit sigUpdateClientShow(clientnamelist,allnospeakname);
}
void Server::slotAllowSpeak(QString msg)         //解禁言
{
   QList<QString> nospeakname;
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
void Server::slotQuit(QString msg)                 //强制登出
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
        if(namesocket.contains(item))       //如果包含键值
        {
            cout<<"contain"<<endl;
            QTcpSocket *it=namesocket[item];
            int soc=it->socketDescriptor();
            cout<<soc<<endl;
            for(int j=0;j<clientsocketlist.count();j++)
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
            for(int j=0;j<allnospeakname.count();j++)
            {
               name=allnospeakname.at(j);
               if(name==item)
               {
                  allnospeakname.removeAt(j);
                  break;
               }
            }
            for(int j=0;j<clientnamelist.count();j++)
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
