#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>

#include "client.h"
#include <ui_chatdialog.h>

namespace Ui {
    class chatDialog;
}

class ChatDialog : public QDialog {
    Q_OBJECT

    public:
        explicit ChatDialog(QWidget *parent = nullptr);
        ~ChatDialog();

    private:
        Ui::chatDialog *ui;
        QLineEdit *chatField;
        QPushButton *sendButton;
        QTextEdit *chatDisplay;
        QListWidget *userList;
        Client *client;
        QString myNickName;
        QTextTableFormat tableFormat;

    private slots:
        void SendMessage();
        void newParticipant(const QString &nick);
        void participantLeft(const QString &nick);
        void showInformation();

    public slots:
        void appendMessage(const QString &from, const QString &message);

};

#endif // CHATDIALOG_H
