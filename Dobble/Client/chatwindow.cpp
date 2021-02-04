#include "chatwindow.h"
#include "ui_chatwindow.h"
#include "chatclient.h"
#include <QStandardItemModel>
#include <QInputDialog>
#include <QMessageBox>
#include <QHostAddress>
#include <QJsonObject>
#include <QDebug>
#include "cards.h"
#include <QTimer>

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
    connect(m_chatClient, &ChatClient::loginDuplicate, this, &ChatWindow::loginDuplicate);
    connect(m_chatClient, &ChatClient::finishRound, this, &ChatWindow::finishRound);
    connect(m_chatClient, &ChatClient::userLimit, this, &ChatWindow::userLimit);
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
        QMessageBox::warning(this, "Error", "Empty login");
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
    QString message = button->objectName();
    m_chatClient->sendMessage("answer,"+QString::number(message[message.length()-1].unicode()-65));
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

void ChatWindow::clearBoard()
{
    ui->labelA->setText("");
    ui->labelB->setText("");
    ui->labelC->setText("");
    ui->labelD->setText("");
    ui->labelE->setText("");
    ui->labelF->setText("");
    ui->labelG->setText("");
    ui->labelH->setText("");
    ui->buttonA->setText("");
    ui->buttonB->setText("");
    ui->buttonC->setText("");
    ui->buttonD->setText("");
    ui->buttonE->setText("");
    ui->buttonF->setText("");
    ui->buttonG->setText("");
    ui->buttonH->setText("");
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
        if(ui->buttonA->text() == "A" || ui->buttonA->text() == "")
            ui->startButton->setEnabled(true);
    }
}

void ChatWindow::countDown(const int &timer)
{
    ui->countDown->setText("Game will begin in " + QString::number(timer) + " seconds or when host will press start");
}

void ChatWindow::countDownFinished(const bool &success, const int &card, const int &boardCard)
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
        ui->labelA->setText(cards->symbols[cards->cards[boardCard][0]-1]);
        ui->labelB->setText(cards->symbols[cards->cards[boardCard][1]-1]);
        ui->labelC->setText(cards->symbols[cards->cards[boardCard][2]-1]);
        ui->labelD->setText(cards->symbols[cards->cards[boardCard][3]-1]);
        ui->labelE->setText(cards->symbols[cards->cards[boardCard][4]-1]);
        ui->labelF->setText(cards->symbols[cards->cards[boardCard][5]-1]);
        ui->labelG->setText(cards->symbols[cards->cards[boardCard][6]-1]);
        ui->labelH->setText(cards->symbols[cards->cards[boardCard][7]-1]);
        ui->buttonA->setText(cards->symbols[cards->cards[card][0]-1]);
        ui->buttonB->setText(cards->symbols[cards->cards[card][1]-1]);
        ui->buttonC->setText(cards->symbols[cards->cards[card][2]-1]);
        ui->buttonD->setText(cards->symbols[cards->cards[card][3]-1]);
        ui->buttonE->setText(cards->symbols[cards->cards[card][4]-1]);
        ui->buttonF->setText(cards->symbols[cards->cards[card][5]-1]);
        ui->buttonG->setText(cards->symbols[cards->cards[card][6]-1]);
        ui->buttonH->setText(cards->symbols[cards->cards[card][7]-1]);
        ui->countDown->setText("Game has started");
        ui->startButton->setEnabled(false);
    }
    else
    {
        ui->countDown->setText("Too few players to start");
    }
}

void ChatWindow::loginDuplicate()
{
    QMessageBox::warning(this, "Error", "Duplicate username");
}

void ChatWindow::userLimit()
{
    QMessageBox::warning(this, "Error", "Too many players");
}

void ChatWindow::finishRound(const int isWin, const QString &username)
{
    clearBoard();
    if (isWin) {
        ui->countDown->setText("You won");
    } else {
        ui->countDown->setText(username+" won");
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
