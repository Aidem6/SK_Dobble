#include "chatwindow.h"
#include "ui_chatwindow.h"
#include "chatclient.h"
#include <QStandardItemModel>
#include <QInputDialog>
#include <QMessageBox>
#include <QHostAddress>
#include <QJsonObject>
#include<QDebug>

ChatWindow::ChatWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChatWindow)
    , m_chatClient(new ChatClient(this))
    , m_chatModel(new QStandardItemModel(this))
{
    ui->setupUi(this);

    ui->progressBar_1->hide();
    ui->progressBar_2->hide();
    ui->progressBar_3->hide();
    ui->progressBar_4->hide();
    ui->progressBar_5->hide();
    ui->progressBar_6->hide();
    ui->progressBar_7->hide();
    ui->progressBar_8->hide();
    m_chatModel->insertColumn(0);
    ui->chatView->setModel(m_chatModel);

    connect(m_chatClient, &ChatClient::connected, this, &ChatWindow::connectedToServer);
    connect(m_chatClient, &ChatClient::loggedIn, this, &ChatWindow::loggedIn);
    connect(m_chatClient, &ChatClient::loginError, this, &ChatWindow::loginFailed);
    connect(m_chatClient, &ChatClient::messageReceived, this, &ChatWindow::messageReceived);
    connect(m_chatClient, &ChatClient::disconnected, this, &ChatWindow::disconnectedFromServer);
    connect(m_chatClient, &ChatClient::error, this, &ChatWindow::error);
    connect(m_chatClient, &ChatClient::userJoined, this, &ChatWindow::userJoined);
    connect(m_chatClient, &ChatClient::playerCount, this, &ChatWindow::playerCount);
    connect(m_chatClient, &ChatClient::countDown, this, &ChatWindow::countDown);
    connect(m_chatClient, &ChatClient::countDownFinished, this, &ChatWindow::countDownFinished);
    connect(m_chatClient, &ChatClient::userLeft, this, &ChatWindow::userLeft);

    connect(ui->connectButton, &QPushButton::clicked, this, &ChatWindow::attemptConnection);
    connect(ui->startButton, &QPushButton::clicked, this, &ChatWindow::startGame);
    connect(ui->buttonA, &QPushButton::clicked, this, &ChatWindow::sendMessage);
    connect(ui->buttonB, &QPushButton::clicked, this, &ChatWindow::sendMessage);
    connect(ui->buttonC, &QPushButton::clicked, this, &ChatWindow::sendMessage);
    connect(ui->buttonD, &QPushButton::clicked, this, &ChatWindow::sendMessage);
    connect(ui->buttonE, &QPushButton::clicked, this, &ChatWindow::sendMessage);
    connect(ui->buttonF, &QPushButton::clicked, this, &ChatWindow::sendMessage);
    connect(ui->buttonG, &QPushButton::clicked, this, &ChatWindow::sendMessage);
    connect(ui->buttonH, &QPushButton::clicked, this, &ChatWindow::sendMessage);
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

void ChatWindow::attemptConnection()
{
    const QString hostAddress = QInputDialog::getText(
        this
        , tr("Chose Server")
        , tr("Server Address")
        , QLineEdit::Normal
        , QStringLiteral("127.0.0.1")
    );
    if (hostAddress.isEmpty())
        return;
    ui->connectButton->setEnabled(false);
    m_chatClient->connectToServer(QHostAddress(hostAddress), 2000);
}

void ChatWindow::startGame()
{
    ui->connectButton->setEnabled(false);
    m_chatClient->startGame();
}

void ChatWindow::connectedToServer()
{
    const QString newUsername = QInputDialog::getText(this, tr("Chose Username"), tr("Username"));
    if (newUsername.isEmpty()){
        return m_chatClient->disconnectFromHost();
    }
    attemptLogin(newUsername);
}

void ChatWindow::attemptLogin(const QString &userName)
{
    m_chatClient->login(userName);
}

void ChatWindow::loggedIn()
{
    ui->chatView->setEnabled(true);
}

void ChatWindow::loginFailed(const QString &reason)
{
    QMessageBox::critical(this, tr("Error"), reason);
    connectedToServer();
}

void ChatWindow::messageReceived(const QString &text)
{
    int newRow = m_chatModel->rowCount();
    m_chatModel->insertRow(newRow);
    m_chatModel->setData(m_chatModel->index(newRow, 0), text);
    m_chatModel->setData(m_chatModel->index(newRow, 0), int(Qt::AlignLeft | Qt::AlignVCenter), Qt::TextAlignmentRole);
    ui->chatView->scrollToBottom();
}

void ChatWindow::sendMessage()
{
    auto button = qobject_cast<QPushButton *>(sender());
    QString message = button->text();
    m_chatClient->sendMessage(message);
}

void ChatWindow::disconnectedFromServer()
{
    QMessageBox::warning(this, tr("Disconnected"), tr("The host terminated the connection"));
    ui->buttonA->setEnabled(false);
    ui->buttonB->setEnabled(false);
    ui->buttonC->setEnabled(false);
    ui->buttonD->setEnabled(false);
    ui->buttonE->setEnabled(false);
    ui->buttonF->setEnabled(false);
    ui->buttonG->setEnabled(false);
    ui->buttonH->setEnabled(false);
    ui->chatView->setEnabled(false);
    ui->connectButton->setEnabled(true);
    ui->startButton->setEnabled(false);
    ui->playerCount->setText("Number of players: 0");
    ui->countDown->setText("");
}

void ChatWindow::userJoined(const QString &username)
{
    const int newRow = m_chatModel->rowCount();
    m_chatModel->insertRow(newRow);
    m_chatModel->setData(m_chatModel->index(newRow, 0), tr("%1 joined the game").arg(username));
    m_chatModel->setData(m_chatModel->index(newRow, 0), Qt::AlignCenter, Qt::TextAlignmentRole);
    m_chatModel->setData(m_chatModel->index(newRow, 0), QBrush(Qt::blue), Qt::ForegroundRole);
    ui->chatView->scrollToBottom();
}

void ChatWindow::resetPlayers()
{
    ui->progressBar_1->hide();
    ui->progressBar_2->hide();
    ui->progressBar_3->hide();
    ui->progressBar_4->hide();
    ui->progressBar_5->hide();
    ui->progressBar_6->hide();
    ui->progressBar_7->hide();
    ui->progressBar_8->hide();
    ui->cardsLeft1->setText("");
    ui->cardsLeft2->setText("");
    ui->cardsLeft3->setText("");
    ui->cardsLeft4->setText("");
    ui->cardsLeft5->setText("");
    ui->cardsLeft6->setText("");
    ui->cardsLeft7->setText("");
    ui->cardsLeft8->setText("");
    ui->playerName1->setText("");
    ui->playerName2->setText("");
    ui->playerName3->setText("");
    ui->playerName4->setText("");
    ui->playerName5->setText("");
    ui->playerName6->setText("");
    ui->playerName7->setText("");
    ui->playerName8->setText("");
}

void ChatWindow::playerCount(const int &n, const QJsonObject &players)
{
    ui->playerCount->setText("Number of players: " + QString::number(n));

    resetPlayers();
    for (int i = 1; i <= n; i++) {
        const QJsonValue player = players.value(QLatin1String("player")+QString::number(i));
        const QJsonValue points = players.value(QLatin1String("points")+QString::number(i));
        QString objectnameNick = "playerName"+QString::number(i);
        QString objectnameCardsLeft = "cardsLeft"+QString::number(i);
        QString objectnameProgressBar = "progressBar_"+QString::number(i);
        QLabel *nick = findChild<QLabel *>( objectnameNick );
        QLabel *cardsLeft = findChild<QLabel *>( objectnameCardsLeft );
        QProgressBar *bar = findChild<QProgressBar *>( objectnameProgressBar );
        if ( nick ) {
            nick->setText(player.toString());
            cardsLeft->setText(points.toString());
            bar->setVisible(true);
            int percent = 100-points.toString().toInt()*100/7;
            bar->setValue(percent);
        }
    }

    if (n == 1)
    {
        if(ui->buttonA->text() == "A")
            ui->startButton->setEnabled(true);
    }
}

void ChatWindow::countDown(const int &timer)
{
    if (timer <= 60) {
        ui->countDown->setText("Game will begin in " + QString::number(timer) + " seconds or when host will press start");
    }
    else {
        ui->countDown->setText("Too few players to start");
    }
}

void ChatWindow::countDownFinished(const bool &success, const QJsonObject &card, const QJsonObject &boardCard)
{
    if (success)
    {
        ui->buttonA->setEnabled(true);
        ui->buttonB->setEnabled(true);
        ui->buttonC->setEnabled(true);
        ui->buttonD->setEnabled(true);
        ui->buttonE->setEnabled(true);
        ui->buttonF->setEnabled(true);
        ui->buttonG->setEnabled(true);
        ui->buttonH->setEnabled(true);
        ui->labelA->setText(QString::number(boardCard["A"].toInt()));
        ui->labelB->setText(QString::number(boardCard["B"].toInt()));
        ui->labelC->setText(QString::number(boardCard["C"].toInt()));
        ui->labelD->setText(QString::number(boardCard["D"].toInt()));
        ui->labelE->setText(QString::number(boardCard["E"].toInt()));
        ui->labelF->setText(QString::number(boardCard["F"].toInt()));
        ui->labelG->setText(QString::number(boardCard["G"].toInt()));
        ui->labelH->setText(QString::number(boardCard["H"].toInt()));
        ui->buttonA->setText(QString::number(card["A"].toInt()));
        ui->buttonB->setText(QString::number(card["B"].toInt()));
        ui->buttonC->setText(QString::number(card["C"].toInt()));
        ui->buttonD->setText(QString::number(card["D"].toInt()));
        ui->buttonE->setText(QString::number(card["E"].toInt()));
        ui->buttonF->setText(QString::number(card["F"].toInt()));
        ui->buttonG->setText(QString::number(card["G"].toInt()));
        ui->buttonH->setText(QString::number(card["H"].toInt()));
        ui->countDown->setText("Game has started");
        ui->startButton->setEnabled(false);
    }
    else
    {
        QMessageBox::warning(this, "Error", "Too few players to start");
    }
}

void ChatWindow::userLeft(const QString &username)
{
    const int newRow = m_chatModel->rowCount();
    m_chatModel->insertRow(newRow);
    m_chatModel->setData(m_chatModel->index(newRow, 0), tr("%1 left the game").arg(username));
    m_chatModel->setData(m_chatModel->index(newRow, 0), Qt::AlignCenter, Qt::TextAlignmentRole);
    m_chatModel->setData(m_chatModel->index(newRow, 0), QBrush(Qt::red), Qt::ForegroundRole);
    ui->chatView->scrollToBottom();
}

void ChatWindow::error(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
    case QAbstractSocket::ProxyConnectionClosedError:
        return;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::critical(this, tr("Error"), tr("The host refused the connection"));
        break;
    case QAbstractSocket::ProxyConnectionRefusedError:
        QMessageBox::critical(this, tr("Error"), tr("The proxy refused the connection"));
        break;
    case QAbstractSocket::ProxyNotFoundError:
        QMessageBox::critical(this, tr("Error"), tr("Could not find the proxy"));
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::critical(this, tr("Error"), tr("Could not find the server"));
        break;
    case QAbstractSocket::SocketAccessError:
        QMessageBox::critical(this, tr("Error"), tr("You don't have permissions to execute this operation"));
        break;
    case QAbstractSocket::SocketResourceError:
        QMessageBox::critical(this, tr("Error"), tr("Too many connections opened"));
        break;
    case QAbstractSocket::SocketTimeoutError:
        QMessageBox::warning(this, tr("Error"), tr("Operation timed out"));
        return;
    case QAbstractSocket::ProxyConnectionTimeoutError:
        QMessageBox::critical(this, tr("Error"), tr("Proxy timed out"));
        break;
    case QAbstractSocket::NetworkError:
        QMessageBox::critical(this, tr("Error"), tr("Unable to reach the network"));
        break;
    case QAbstractSocket::UnknownSocketError:
        QMessageBox::critical(this, tr("Error"), tr("An unknown error occured"));
        break;
    case QAbstractSocket::UnsupportedSocketOperationError:
        QMessageBox::critical(this, tr("Error"), tr("Operation not supported"));
        break;
    case QAbstractSocket::ProxyAuthenticationRequiredError:
        QMessageBox::critical(this, tr("Error"), tr("Your proxy requires authentication"));
        break;
    case QAbstractSocket::ProxyProtocolError:
        QMessageBox::critical(this, tr("Error"), tr("Proxy comunication failed"));
        break;
    case QAbstractSocket::TemporaryError:
    case QAbstractSocket::OperationError:
        QMessageBox::warning(this, tr("Error"), tr("Operation failed, please try again"));
        return;
    default:
        Q_UNREACHABLE();
    }
    ui->connectButton->setEnabled(true);
    ui->startButton->setEnabled(false);
    ui->playerCount->setText("Number of players: 0");
    ui->countDown->setText("");
    ui->buttonA->setEnabled(false);
    ui->buttonB->setEnabled(false);
    ui->buttonC->setEnabled(false);
    ui->buttonD->setEnabled(false);
    ui->buttonE->setEnabled(false);
    ui->buttonF->setEnabled(false);
    ui->buttonG->setEnabled(false);
    ui->buttonH->setEnabled(false);
    ui->chatView->setEnabled(false);
}
