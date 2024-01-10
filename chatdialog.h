#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>
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

    public slots:

    private slots:
        void SendMessage();

};

#endif // CHATDIALOG_H
