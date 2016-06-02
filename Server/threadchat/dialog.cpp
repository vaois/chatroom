#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->open,SIGNAL(clicked()),this,SLOT(on_pushButton_clicked()));
    connect(ui->close,SIGNAL(clicked()),this,SLOT(slotclose()));
    connect(ui->clear,SIGNAL(clicked()),this,SLOT(slotclear()));
    connect(ui->allowspeak,SIGNAL(clicked()),this,SLOT(slotAllowSpeak()));
    connect(ui->nospeak,SIGNAL(clicked()),this,SLOT(slotNoSpeak()));
    connect(ui->forcequit,SIGNAL(clicked()),this,SLOT(slotQuit()));
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
void Dialog::slotclose()
{
    //~Server();
    delete server;
    ui->serverstatus->setText("服务器：关闭");
    ui->open->setEnabled(true);
    ui->close->setEnabled(false);
    ui->clientmessage->clear();
}
void Dialog::on_pushButton_clicked()
{
    server=new Server();
    server->listen(QHostAddress::Any,port);
    connect(this,SIGNAL(sigAllowSpeak(QString)),server,SLOT(slotAllowSpeak(QString)));
    connect(this,SIGNAL(sigNospeak(QString)),server,SLOT(slotNoSpeak(QString)));
    connect(this,SIGNAL(sigQuit(QString)),server,SLOT(slotQuit(QString)));
    connect(server,SIGNAL(sigUpDateServerShow(QString,QString)),this,SLOT(slotUpDateServerShow(QString,QString)));
    connect(server,SIGNAL(sigUpdateClientShow(QList<QString>,QList<QString>)),this,SLOT(slotUpdateClientShow(QList<QString>,QList<QString>)));
    ui->serverstatus->setText("服务器：开启");
    ui->open->setEnabled(false);
    ui->close->setEnabled(true);
}
void Dialog::slotclear()
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

void Dialog::on_open_clicked()
{

}
