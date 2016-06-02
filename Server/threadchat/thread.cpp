#include "thread.h"


Thread::Thread(QObject *parent,QTcpSocket *tcpsocket)
    :QThread(parent)
{
     clientsocket=tcpsocket;
}
void Thread::run()   //接收信息，并对信息进行处理
{
    char action;
    while(clientsocket-> bytesAvailable()>0)
    {
        int length = clientsocket-> bytesAvailable();
        clientsocket->read(buf,length);
        //cout<<buf<<endl;
        msg=buf;
        cout<<"thread"<<endl;
        cout<<msg<<endl;
        cout<<"end"<<endl;
    }
    Protocol *protocol=new Protocol(this,msg);
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
              //emit sigReback(success);
              emit sigSignText(protocol->name,protocol->text);
              break;
       case 'F':
              emit sigReback(fail);
    }
    //emit cancelthread();
}
