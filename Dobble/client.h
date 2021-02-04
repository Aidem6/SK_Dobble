#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>

class QHostAddress;
class QJsonDocument;
class Client : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Client)
public:
    explicit Client(QObject *parent = nullptr);
public slots:
    void connectToServer(const QHostAddress &address, quint16 port);
    void startGame();
    void login(const QString &userName);
    void sendMessage(const QString &text);
    void disconnectFromHost();
private slots:
    void onReadyRead();
signals:
    void connected();
    void loggedIn();
    void disconnected();
    void error(QAbstractSocket::SocketError socketError);
    void playerCount(const int &count, const QJsonObject &players);
    void countDown(const int &timer);
    void countDownFinished(const bool &success, const int &card, const int &boardCard);
    void loginDuplicate();
    void userLimit();
    void finishRound(const int isWin, const QString &username);
private:
    QTcpSocket *m_clientSocket;
    bool m_loggedIn;
    void jsonReceived(const QJsonObject &doc);
    void messageType(const QString &data);
};

#endif // CLIENT_H
