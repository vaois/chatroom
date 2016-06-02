#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "server.h"
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
signals:
    void sigNospeak(QString);
    void sigAllowSpeak(QString);
    void sigQuit(QString);
public slots:
    void on_pushButton_clicked();
    void slotclose();
    void slotclear();
    void slotQuit();
    void slotNoSpeak();
    void slotAllowSpeak();
    void slotUpDateServerShow(QString,QString);
    void slotUpdateClientShow(QList<QString>,QList<QString>);
private slots:
    void on_open_clicked();

private:
    Ui::Dialog *ui;
    int port=1111;
    Server *server;
};

#endif // DIALOG_H
