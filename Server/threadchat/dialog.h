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
    void slotOpen();
    void slotClose();
    void slotClear();
    void slotQuit();
    void slotNoSpeak();
    void slotAllowSpeak();
    void slotUpDateServerShow(QString,QString);
    void slotUpdateClientShow(QList<QString>,QList<QString>);

private:
    Ui::Dialog *ui;
    Server *server;
};

#endif // DIALOG_H
