#include "chatdialog.h"

#include <QLineEdit>
#include <QDebug>

ChatDialog::ChatDialog(QWidget *parent): QDialog(parent), ui(new Ui::chatDialog) {
    ui->setupUi(this);

    chatField = ui->chatField;
    sendButton = ui->sendButton;

    connect(chatField, &QLineEdit::returnPressed,
            this, &ChatDialog::SendMessage);
    connect(sendButton, &QPushButton::pressed,
            this, &ChatDialog::SendMessage);
}

void ChatDialog::SendMessage() {
    QString msg = chatField->text();

    if (msg.isEmpty()) return;

    // Print sent message in debug console
    // TODO: Send message over network
    qDebug() << "Message sent: " << msg;

    chatField->clear();
}

ChatDialog::~ChatDialog() {
    delete ui;
}
