#include "chatdialog.h"

#include <QLineEdit>
#include <QDebug>
#include <QTimer>
#include <QTextTable>
#include <QMessageBox>
#include <QScrollBar>

ChatDialog::ChatDialog(QWidget *parent): QDialog(parent), ui(new Ui::chatDialog) {
    ui->setupUi(this);

    chatField = ui->chatField;
    sendButton = ui->sendButton;
    chatDisplay = ui->chatDisplay;
    userList = ui->userList;

    connect(chatField, &QLineEdit::returnPressed, this, &ChatDialog::SendMessage);
    connect(sendButton, &QPushButton::pressed, this, &ChatDialog::SendMessage);

    connect(&client, &Client::newParticipant, this, &ChatDialog::newParticipant);
    connect(&client, &Client::participantLeft, this, &ChatDialog::participantLeft);

    myNickName = client.nickName();
    newParticipant(myNickName);
    tableFormat.setBorder(0);
    QTimer::singleShot(30 * 1000, this, &ChatDialog::showInformation);
}

void ChatDialog::SendMessage() {
    QString msg = chatField->text();

    if (msg.isEmpty()) return;

    // Keep debug to track send messages
    qDebug() << "Message sent: " << msg;

    if (msg.startsWith(QChar('/'))) {
        QColor color = chatDisplay->textColor();
        chatDisplay->setTextColor(Qt::red);
        chatDisplay->append(tr("! Unknown command: %1").arg(msg.left(msg.indexOf(' '))));
        chatDisplay->setTextColor(color);
    } else {
        client.sendMessage(msg);
        appendMessage(myNickName, msg);
    }

    chatField->clear();
}

void ChatDialog::appendMessage(const QString &from, const QString &message)
{
    if (from.isEmpty() || message.isEmpty())
        return;

    QTextCursor cursor(chatDisplay->textCursor());
    cursor.movePosition(QTextCursor::End);
    QTextTable *table = cursor.insertTable(1, 2, tableFormat);
    table->cellAt(0, 0).firstCursorPosition().insertText('<' + from + "> ");
    table->cellAt(0, 1).firstCursorPosition().insertText(message);
    QScrollBar *bar = chatDisplay->verticalScrollBar();
    bar->setValue(bar->maximum());
}

void ChatDialog::newParticipant(const QString &nick)
{
    if (nick.isEmpty())
        return;

    QColor color = chatDisplay->textColor();
    chatDisplay->setTextColor(Qt::gray);
    chatDisplay->append(tr("* %1 has joined").arg(nick));
    chatDisplay->setTextColor(color);
    userList->addItem(nick);
}

void ChatDialog::participantLeft(const QString &nick)
{
    if (nick.isEmpty())
        return;

    QList<QListWidgetItem *> items = userList->findItems(nick, Qt::MatchExactly);
    if (items.isEmpty())
        return;

    delete items.at(0);
    QColor color = chatDisplay->textColor();
    chatDisplay->setTextColor(Qt::gray);
    chatDisplay->append(tr("* %1 has left").arg(nick));
    chatDisplay->setTextColor(color);
}

void ChatDialog::showInformation()
{
    if (userList->count() == 1) {
        QMessageBox::information(this, tr("Chat"),
                                 tr("Launch several instances of this "
                                    "program on your local network and "
                                    "start chatting!"));
    }
}

ChatDialog::~ChatDialog() {
    delete ui;
}
