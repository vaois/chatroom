#include "thread.h"


Thread::Thread(QObject *parent,QTcpSocket *tcpsocket)
    :QThread(parent)
{
     clientsocket=tcpsocket;
}
void Thread::run()       //接收信息，并对信息进行划分处理
{
    char action;
    while(clientsocket-> bytesAvailable()>0)
    {
        int length = clientsocket-> bytesAvailable();
        clientsocket->read(buf,length);
        msg=buf;
        cout<<msg<<endl;
    }
    Protocol *protocol=new Protocol(this,msg);    //创建protocol对象对信息进行处理，根据“#”字符进行分割
    action=protocol->handle();
    switch(action)
    {
       case 'I':
              cout<<"thread"<<endl;
              emit sigSignIn(protocol->name,protocol->password);
              break;
       case 'O':
              emit sigSignOut(protocol->name);
              break;
       case 'U':
              emit sigSignUp(protocol->name,protocol->password);
              break;
       case 'T':
              emit sigSignText(protocol->name,protocol->text);
              break;
       case 'F':
              emit sigReback(fail);
    }
}
