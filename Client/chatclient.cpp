#include "chatclient.h"
#include <QDataStream>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <qeventloop.h>
#include <qtimer.h>
#define PORT 2000

ChatClient::ChatClient(QObject *parent)
    : QObject(parent)
    , m_clientSocket(new QTcpSocket(this))
    , m_loggedIn(false)
{
    connect(m_clientSocket, &QTcpSocket::connected, this, &ChatClient::connected);
    connect(m_clientSocket, &QTcpSocket::disconnected, this, &ChatClient::disconnected);
    connect(m_clientSocket, &QTcpSocket::readyRead, this, &ChatClient::onReadyRead);
    connect(m_clientSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &ChatClient::error);
    connect(m_clientSocket, &QTcpSocket::disconnected, this, [this]()->void{m_loggedIn = false;});
}

void ChatClient::login(const QString &userName)
{
    if (m_clientSocket->state() == QAbstractSocket::ConnectedState) {

        char mess[40] = "newLogin,";
        QByteArray ba = userName.toLocal8Bit();
        const char *mess2 = ba.data();
        strcat(mess, mess2);
        send(m_clientSocket->socketDescriptor(), mess, sizeof(mess), 0);
    }
}

void ChatClient::sendMessage(const QString &text)
{
    if (text.isEmpty())
        return;

    qDebug() << text;

    char mess[40] = "";
    QByteArray ba = text.toLocal8Bit();
    const char *mess2 = ba.data();
    strcat(mess, mess2);
    send(m_clientSocket->socketDescriptor(), mess, sizeof(mess), 0);
}

void ChatClient::disconnectFromHost()
{
    m_clientSocket->disconnectFromHost();
}

void ChatClient::messageType(const QString &data)
{
    qDebug() << data;
    emit messageReceived(data);
    QStringList list = data.split(',');
    if (list[0].compare(QLatin1String("loginSuccess"), Qt::CaseInsensitive) == 0) {
        emit loggedIn();
    } else if (list[0].compare(QLatin1String("countDown"), Qt::CaseInsensitive) == 0) {
        emit countDown(list[1].toInt());
    } else if (list[0].compare(QLatin1String("message"), Qt::CaseInsensitive) == 0) {
        emit messageReceived(list[1]);
    } else if (list[0].compare(QLatin1String("playerCount"), Qt::CaseInsensitive) == 0) {
        QStringList playersList = list[1].split(';');
        QJsonObject players;
        int n = playersList[0].toInt();
        int k = 1;
        for (int i=1; i<n+1; i++, k++) {
            players[QStringLiteral("player")+QString::number(i)] = QString(playersList[k]);
            k++;
            players[QStringLiteral("points")+QString::number(i)] = QString(playersList[k]);
        }
        emit playerCount(n, players);
    }
    else if (list[0].compare(QLatin1String("countDownFinished"), Qt::CaseInsensitive) == 0) {
        QStringList cardsList = list[1].split(';');
        emit countDownFinished(cardsList[0].toInt(), cardsList[1].toInt(), cardsList[2].toInt());
    }
    else if (list[0].compare(QLatin1String("duplicate"), Qt::CaseInsensitive) == 0) {
        emit loginDuplicate();
        disconnectFromHost();
    }
    else if (list[0].compare(QLatin1String("finish"), Qt::CaseInsensitive) == 0) {
        QStringList arg = list[1].split(';');
        emit finishRound(arg[0].toInt(), arg[1]);
    }
    else if (list[0].compare(QLatin1String("limit"), Qt::CaseInsensitive) == 0) {
        emit userLimit();
        disconnectFromHost();
    }
}

void ChatClient::connectToServer(const QHostAddress &address, quint16 port)
{
    m_clientSocket->connectToHost(address, port);
}

void ChatClient::startGame()
{
    char mess[20] = "startGame,";
    send(m_clientSocket->socketDescriptor(), mess, sizeof(mess), 0);
}

void ChatClient::onReadyRead()
{
    QString data;
    while(m_clientSocket->bytesAvailable())
    {
        data = m_clientSocket->readAll();

        messageType(data);

        QEventLoop loop;
        QTimer::singleShot(100, &loop, SLOT(quit()));
        loop.exec();
    }
}
