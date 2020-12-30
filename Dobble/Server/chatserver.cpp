#include "chatserver.h"
#include "serverworker.h"
#include "cards.h"
#include <QThread>
#include <functional>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QTimer>
ChatServer::ChatServer(QObject *parent)
    : QTcpServer(parent)
{}

void ChatServer::incomingConnection(qintptr socketDescriptor)
{
    ServerWorker *worker = new ServerWorker(this);
    if (!worker->setSocketDescriptor(socketDescriptor)) {
        worker->deleteLater();
        return;
    }
    connect(worker, &ServerWorker::disconnectedFromClient, this, std::bind(&ChatServer::userDisconnected, this, worker));
    connect(worker, &ServerWorker::error, this, std::bind(&ChatServer::userError, this, worker));
    connect(worker, &ServerWorker::jsonReceived, this, std::bind(&ChatServer::jsonReceived, this, worker, std::placeholders::_1));
    connect(worker, &ServerWorker::logMessage, this, &ChatServer::logMessage);
    connect(worker, &ServerWorker::addUser, this, &ChatServer::addUser);
    if (first) {
        connect(timer, &QTimer::timeout, this, &ChatServer::timerUpdate);
        first = false;
        cards->randomize();
    }
    m_clients.append(worker);
    emit logMessage(QStringLiteral("New client Connected"));
}

void ChatServer::countDown()
{
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &ChatServer::timerUpdate);
    timer->start(1000);
}

void ChatServer::timerUpdate()
{
    if (timerValue >= 0) {
        QJsonObject message;
        message[QStringLiteral("type")] = QStringLiteral("countDown");
        message[QStringLiteral("timer")] = timerValue;
        broadcast(message, nullptr);
        emit logMessage(QStringLiteral("Game will start in: ")+QString::number(timerValue));
        timerValue--;
    }
    if (timerValue == -1) {
        if (m_clients.size() >= 3) {
            ChatServer::startGame();
        }
        else {
            emit logMessage(QStringLiteral("Too few players to start"));
            timerValue = 63;
        }
    }
}

void ChatServer::sendJson(ServerWorker *destination, const QJsonObject &message)
{
    Q_ASSERT(destination);
    destination->sendJson(message);
}

void ChatServer::broadcast(const QJsonObject &message, ServerWorker *exclude)
{
    for (ServerWorker *worker : m_clients) {
        Q_ASSERT(worker);
        if (worker == exclude)
            continue;
        sendJson(worker, message);
    }
}

void ChatServer::jsonReceived(ServerWorker *sender, const QJsonObject &doc)
{
    Q_ASSERT(sender);
    emit logMessage(QLatin1String("JSON received ") + QString::fromUtf8(QJsonDocument(doc).toJson()));
    if (sender->userName().isEmpty())
        return jsonFromLoggedOut(sender, doc);
    jsonFromLoggedIn(sender, doc);
}

void ChatServer::playerCount()
{
    int i = 1;
    QJsonObject players;
    for (ServerWorker *worker : m_clients) {
        players[QStringLiteral("player")+QString::number(i)] = QString(worker->userName());
        players[QStringLiteral("points")+QString::number(i)] = QString::number(worker->points());
        i++;
    }
    QJsonObject message;
    message[QStringLiteral("type")] = QStringLiteral("playerCount");
    message[QStringLiteral("count")] = m_clients.size();
    message[QStringLiteral("players")] = players;
    broadcast(message, nullptr);
}

void ChatServer::userDisconnected(ServerWorker *sender)
{
    m_clients.removeAll(sender);
    emit addUser(m_clients.size());
    const QString userName = sender->userName();
    if (!userName.isEmpty()) {
        QJsonObject disconnectedMessage;
        disconnectedMessage[QStringLiteral("type")] = QStringLiteral("userdisconnected");
        disconnectedMessage[QStringLiteral("username")] = userName;
        broadcast(disconnectedMessage, nullptr);
        emit logMessage(userName + QLatin1String(" disconnected"));
    }
    sender->deleteLater();
    playerCount();
    if (m_clients.size() < 1) {
        timer->stop();
        emit logMessage(QLatin1String("timer stopped userDisconnected"));
    }
}

void ChatServer::userError(ServerWorker *sender)
{
    Q_UNUSED(sender)
    emit logMessage(QLatin1String("Error from ") + sender->userName());
    playerCount();
    if (m_clients.size() < 1) {
        timer->stop();
        emit logMessage(QLatin1String("timer stopped userError"));
    }
}

void ChatServer::stopServer()
{
    for (ServerWorker *worker : m_clients) {
        worker->disconnectFromClient();
    }
    emit addUser(m_clients.size());
    timer->stop();
    emit logMessage(QLatin1String("timer stopped stopServer"));

    close();
}

void ChatServer::jsonFromLoggedOut(ServerWorker *sender, const QJsonObject &docObj)
{
    Q_ASSERT(sender);
    const QJsonValue typeVal = docObj.value(QLatin1String("type"));
    if (typeVal.isNull() || !typeVal.isString())
        return;
    if (typeVal.toString().compare(QLatin1String("login"), Qt::CaseInsensitive) != 0)
        return;
    const QJsonValue usernameVal = docObj.value(QLatin1String("username"));
    if (usernameVal.isNull() || !usernameVal.isString())
        return;
    const QString newUserName = usernameVal.toString().simplified();
    if (newUserName.isEmpty())
        return;
    for (ServerWorker *worker : qAsConst(m_clients)) {
        if (worker == sender)
            continue;
        if (worker->userName().compare(newUserName, Qt::CaseInsensitive) == 0) {
            QJsonObject message;
            message[QStringLiteral("type")] = QStringLiteral("login");
            message[QStringLiteral("success")] = false;
            message[QStringLiteral("reason")] = QStringLiteral("duplicate username");
            sendJson(sender, message);
            return;
        }
    }
    sender->setUserName(newUserName);
    sender->setPoints(7);
    QJsonObject successMessage;
    successMessage[QStringLiteral("type")] = QStringLiteral("login");
    successMessage[QStringLiteral("success")] = true;
    sendJson(sender, successMessage);
    emit addUser(m_clients.size());
    if (m_clients.size() == 1) {
        timerValue = 60;
        timer->start(1000);
        emit logMessage(QLatin1String("timer started"));
    }
    playerCount();

    if (isGameOn) {
        sender->setPoints(0);
        for (ServerWorker *worker : m_clients) {
            if (worker->points() > sender->points()) {
                sender->setPoints(worker->points());
            }
        }
        int a = cards->stash[cards->cardOnBoard];
        QJsonObject boardCard;
        boardCard[QStringLiteral("A")] = cards->cards[a][0];
        boardCard[QStringLiteral("B")] = cards->cards[a][1];
        boardCard[QStringLiteral("C")] = cards->cards[a][2];
        boardCard[QStringLiteral("D")] = cards->cards[a][3];
        boardCard[QStringLiteral("E")] = cards->cards[a][4];
        boardCard[QStringLiteral("F")] = cards->cards[a][5];
        boardCard[QStringLiteral("G")] = cards->cards[a][6];
        boardCard[QStringLiteral("H")] = cards->cards[a][7];

        int b = cards->stash[cards->cardIterator];
        QJsonObject card;
        card[QStringLiteral("A")] = cards->cards[b][0];
        card[QStringLiteral("B")] = cards->cards[b][1];
        card[QStringLiteral("C")] = cards->cards[b][2];
        card[QStringLiteral("D")] = cards->cards[b][3];
        card[QStringLiteral("E")] = cards->cards[b][4];
        card[QStringLiteral("F")] = cards->cards[b][5];
        card[QStringLiteral("G")] = cards->cards[b][6];
        card[QStringLiteral("H")] = cards->cards[b][7];
        sender->setCardOnHand(cards->cardIterator);
        cards->cardIterator++;
        QJsonObject message;
        message[QStringLiteral("type")] = QStringLiteral("countDownFinished");
        message[QStringLiteral("success")] = true;
        message[QStringLiteral("card")] = card;
        message[QStringLiteral("boardCard")] = boardCard;
        sendJson(sender, message);
        emit logMessage(QLatin1String("Starting the game"));
        QJsonObject secondMessage;
        message[QStringLiteral("type")] = QStringLiteral("message");
        QString line = "Card on board: ";
        for (int i=0; i<8; i++) {
            line += QString::number(cards->cards[a][i])+" ";
        }
        message[QStringLiteral("text")] = line;
        message[QStringLiteral("sender")] = "Server";
        sendJson(sender, message);
        line = "Card in hand: ";
        for (int i=0; i<8; i++) {
            line += QString::number(cards->cards[b][i])+" ";
        }
        message[QStringLiteral("text")] = line;
        message[QStringLiteral("sender")] = "Server";
        sendJson(sender, message);
    }
}

void ChatServer::pushCardOnBoard(ServerWorker *sender)
{
    cards->cardOnBoard = sender->cardOnHand();
    int a = cards->stash[cards->cardOnBoard];
    QJsonObject boardCard;
    boardCard[QStringLiteral("A")] = cards->cards[a][0];
    boardCard[QStringLiteral("B")] = cards->cards[a][1];
    boardCard[QStringLiteral("C")] = cards->cards[a][2];
    boardCard[QStringLiteral("D")] = cards->cards[a][3];
    boardCard[QStringLiteral("E")] = cards->cards[a][4];
    boardCard[QStringLiteral("F")] = cards->cards[a][5];
    boardCard[QStringLiteral("G")] = cards->cards[a][6];
    boardCard[QStringLiteral("H")] = cards->cards[a][7];

    if (sender->cardOnHand() > 0) {
        sender->setCardOnHand(cards->cardIterator);
        cards->cardIterator++;
    }

    for (ServerWorker *worker : m_clients) {
        QJsonObject card;
        int b = 0;
        if (!(worker == sender && sender->points() == 0)) {
            b = cards->stash[worker->cardOnHand()];
            card[QStringLiteral("A")] = cards->cards[b][0];
            card[QStringLiteral("B")] = cards->cards[b][1];
            card[QStringLiteral("C")] = cards->cards[b][2];
            card[QStringLiteral("D")] = cards->cards[b][3];
            card[QStringLiteral("E")] = cards->cards[b][4];
            card[QStringLiteral("F")] = cards->cards[b][5];
            card[QStringLiteral("G")] = cards->cards[b][6];
            card[QStringLiteral("H")] = cards->cards[b][7];
        } else {
            card[QStringLiteral("A")] = "";
            card[QStringLiteral("B")] = "";
            card[QStringLiteral("C")] = "";
            card[QStringLiteral("D")] = "";
            card[QStringLiteral("E")] = "";
            card[QStringLiteral("F")] = "";
            card[QStringLiteral("G")] = "";
            card[QStringLiteral("H")] = "";
        }
        QJsonObject message;
        message[QStringLiteral("type")] = QStringLiteral("countDownFinished");
        message[QStringLiteral("success")] = true;
        message[QStringLiteral("card")] = card;
        message[QStringLiteral("boardCard")] = boardCard;
        sendJson(worker, message);
        QJsonObject secondMessage;
        message[QStringLiteral("type")] = QStringLiteral("message");
        QString line = "Card on board: ";
        for (int i=0; i<8; i++) {
            line += QString::number(cards->cards[a][i])+" ";
        }
        message[QStringLiteral("text")] = line;
        message[QStringLiteral("sender")] = "Server";
        sendJson(worker, message);
        line = "Card in hand: ";
        for (int i=0; i<8; i++) {
            line += QString::number(cards->cards[b][i])+" ";
        }
        message[QStringLiteral("text")] = line;
        message[QStringLiteral("sender")] = "Server";
        sendJson(worker, message);
    }
}

void ChatServer::startGame()
{
    timer->stop();
    cards->randomize();

    int a = cards->stash[cards->cardOnBoard];
    QJsonObject boardCard;
    boardCard[QStringLiteral("A")] = cards->cards[a][0];
    boardCard[QStringLiteral("B")] = cards->cards[a][1];
    boardCard[QStringLiteral("C")] = cards->cards[a][2];
    boardCard[QStringLiteral("D")] = cards->cards[a][3];
    boardCard[QStringLiteral("E")] = cards->cards[a][4];
    boardCard[QStringLiteral("F")] = cards->cards[a][5];
    boardCard[QStringLiteral("G")] = cards->cards[a][6];
    boardCard[QStringLiteral("H")] = cards->cards[a][7];

    for (ServerWorker *worker : m_clients) {
        int b = cards->stash[cards->cardIterator];
        QJsonObject card;
        card[QStringLiteral("A")] = cards->cards[b][0];
        card[QStringLiteral("B")] = cards->cards[b][1];
        card[QStringLiteral("C")] = cards->cards[b][2];
        card[QStringLiteral("D")] = cards->cards[b][3];
        card[QStringLiteral("E")] = cards->cards[b][4];
        card[QStringLiteral("F")] = cards->cards[b][5];
        card[QStringLiteral("G")] = cards->cards[b][6];
        card[QStringLiteral("H")] = cards->cards[b][7];
        worker->setCardOnHand(cards->cardIterator);
        cards->cardIterator++;
        QJsonObject message;
        message[QStringLiteral("type")] = QStringLiteral("countDownFinished");
        message[QStringLiteral("success")] = true;
        message[QStringLiteral("card")] = card;
        message[QStringLiteral("boardCard")] = boardCard;
        sendJson(worker, message);
        emit logMessage(QLatin1String("Starting the game"));
        QJsonObject secondMessage;
        message[QStringLiteral("type")] = QStringLiteral("message");
        QString line = "Card on board: ";
        for (int i=0; i<8; i++) {
            line += QString::number(cards->cards[a][i])+" ";
        }
        message[QStringLiteral("text")] = line;
        message[QStringLiteral("sender")] = "Server";
        sendJson(worker, message);
        line = "Card in hand: ";
        for (int i=0; i<8; i++) {
            line += QString::number(cards->cards[b][i])+" ";
        }
        message[QStringLiteral("text")] = line;
        message[QStringLiteral("sender")] = "Server";
        sendJson(worker, message);
    }
    isGameOn = true;
}

bool ChatServer::inCardOnBoard(int n)
{
    for (int i = 0; i < 8; i++) {
        if(cards->cards[cards->stash[cards->cardOnBoard]][i] == n)
            return true;
    }
    return false;
}

void ChatServer::jsonFromLoggedIn(ServerWorker *sender, const QJsonObject &docObj)
{
    Q_ASSERT(sender);
    const QJsonValue typeVal = docObj.value(QLatin1String("type"));
    if (typeVal.isNull() || !typeVal.isString())
        return;
    if (typeVal.toString().compare(QLatin1String("message"), Qt::CaseInsensitive) == 0) {
        const QJsonValue textVal = docObj.value(QLatin1String("text"));
        if (textVal.isNull() || !textVal.isString())
            return;
        const QString text = textVal.toString().trimmed();
        if (text.isEmpty())
            return;

        if (inCardOnBoard(text.toInt())) {
            sender->setPoints(sender->points()-1);
            pushCardOnBoard(sender);
        }
        playerCount();
    }
    if (typeVal.toString().compare(QLatin1String("startGame"), Qt::CaseInsensitive) == 0) {
        if(m_clients.size() > 2) {
            ChatServer::startGame();
        }
        else {
            QJsonObject message;
            message[QStringLiteral("type")] = QStringLiteral("countDownFinished");
            message[QStringLiteral("success")] = false;
            broadcast(message, nullptr);
        }
    }

}


