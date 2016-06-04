#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->open,SIGNAL(clicked()),this,SLOT(slotOpen()));   //开启服务器
    connect(ui->close,SIGNAL(clicked()),this,SLOT(slotClose()));              //关闭服务器
    connect(ui->clear,SIGNAL(clicked()),this,SLOT(slotClear()));              //清空聊天内容
    connect(ui->allowspeak,SIGNAL(clicked()),this,SLOT(slotAllowSpeak()));    //解禁言
    connect(ui->nospeak,SIGNAL(clicked()),this,SLOT(slotNoSpeak()));          //禁言
    connect(ui->forcequit,SIGNAL(clicked()),this,SLOT(slotQuit()));           //强制退出
}

Dialog::~Dialog()
{
    delete ui;
}
void Dialog::slotQuit()
{
    QString str=ui->cotent->text();
    ui->cotent->clear();
    emit sigQuit(str);
}
void Dialog::slotNoSpeak()
{
    QString str=ui->cotent->text();
    ui->cotent->clear();
    emit sigNospeak(str);
}
void Dialog::slotAllowSpeak()
{
    QString str=ui->cotent->text();
    ui->cotent->clear();
    emit sigAllowSpeak(str);
}
void Dialog::slotClose()
{
    delete server;
    ui->serverstatus->setText("服务器：关闭");
    ui->open->setEnabled(true);
    ui->close->setEnabled(false);
    ui->clientmessage->clear();
}
void Dialog::slotOpen()
{
    server=new Server();
    connect(this,SIGNAL(sigAllowSpeak(QString)),server,SLOT(slotAllowSpeak(QString)));  //解禁言时对server对象的客户信息进行更新
    connect(this,SIGNAL(sigNospeak(QString)),server,SLOT(slotNoSpeak(QString)));        //禁言时对server对象的客户信息进行更新
    connect(this,SIGNAL(sigQuit(QString)),server,SLOT(slotQuit(QString)));              //强制退出时对server对象的客户信息进行更新
    connect(server,SIGNAL(sigUpDateServerShow(QString,QString)),this,SLOT(slotUpDateServerShow(QString,QString)));  //server对象里的聊天内容有更新时，对ui界面的聊天框内容更新
    connect(server,SIGNAL(sigUpdateClientShow(QList<QString>,QList<QString>)),this,SLOT(slotUpdateClientShow(QList<QString>,QList<QString>)));  //server对象里的客户信息有更新时，对ui的客户信息内容进行显示更新
    ui->serverstatus->setText("服务器：开启");
    ui->open->setEnabled(false);
    ui->close->setEnabled(true);
}
void Dialog::slotClear()
{
     ui->chatmessage->clear();
}
void Dialog::slotUpDateServerShow(QString name, QString text)
{
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString str = time.toString("yyyy-MM-dd hh:mm:ss ddd"); //设置显示格式
    ui->chatmessage->addItem(str+"--"+name);
    ui->chatmessage->addItem(text);

}
void Dialog::slotUpdateClientShow(QList<QString> clientnamelist,QList<QString> allnospeak)
{
    ui->clientmessage->clear();
    for(int i=0;i<clientnamelist.count();i++)
    {
         QString item =clientnamelist.at(i);
         ui->clientmessage->addItem(item);
    }
    for(int i=0;i<allnospeak.count();i++)
    {
         QString item =allnospeak.at(i);
         ui->clientmessage->addItem(item);
    }
}
