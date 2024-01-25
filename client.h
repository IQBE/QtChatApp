#ifndef CLIENT_H
#define CLIENT_H

#include "server.h"

#include <QAbstractSocket>
#include <QHash>
#include <QHostAddress>

class PeerManager;

class Client : public QObject {

    Q_OBJECT

public:
    static Client* instance();

    void sendMessage(const QString &message);
    QString nickName() const;
    bool hasConnection(const QHostAddress &senderIp, int senderPort = -1) const;

signals:
    void newMessage(const QString &from, const QString &message);
    void newParticipant(const QString &nick);
    void participantLeft(const QString &nick);

private slots:
    void newConnection(Connection *connection);
    void connectionError(QAbstractSocket::SocketError socketError);
    void disconnected();
    void readyForUse();

private:
    Client();
    ~Client();

    void removeConnection(Connection *connection);

    PeerManager *peerManager;
    Server server;
    QMultiHash<QHostAddress, Connection *> peers;

    Q_DISABLE_COPY(Client)
};

#endif
