#ifndef CHATSERVER_H
#define CHATSERVER_H

#include "cards.h"
#include <QTcpServer>
#include <QVector>
#include <QTimer>
class QThread;
class ServerWorker;
class ChatServer : public QTcpServer
{
    Q_OBJECT
    Q_DISABLE_COPY(ChatServer)
public:
    explicit ChatServer(QObject *parent = nullptr);
protected:
    void incomingConnection(qintptr socketDescriptor) override;
signals:
    void logMessage(const QString &msg);
    void addUser(const int &n);
public slots:
    void stopServer();
private slots:
    void broadcast(const QJsonObject &message, ServerWorker *exclude);
    void jsonReceived(ServerWorker *sender, const QJsonObject &doc);
    void userDisconnected(ServerWorker *sender);
    void userError(ServerWorker *sender);
    void timerUpdate();
    void countDown();
    void playerCount();
    void startGame();
private:
    QTimer *timer = new QTimer(this);
    int timerValue;
    bool first = true;
    bool isGameOn = false;
    Cards *cards = new Cards;
    void jsonFromLoggedOut(ServerWorker *sender, const QJsonObject &doc);
    bool inCardOnBoard(int n);
    void jsonFromLoggedIn(ServerWorker *sender, const QJsonObject &doc);
    void sendJson(ServerWorker *destination, const QJsonObject &message);
    void pushCardOnBoard(ServerWorker *sender);
    QVector<ServerWorker *> m_clients;
};

#endif // CHATSERVER_H
