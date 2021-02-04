#include "window.h"
#include "ui_window.h"
#include "client.h"
#include <QStandardItemModel>
#include <QInputDialog>
#include <QMessageBox>
#include <QHostAddress>
#include <QJsonObject>
#include <QDebug>
#include "cards.h"
#include <QTimer>

Window::Window(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Window)
    , m_Client(new Client(this))
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

    connect(m_Client, &Client::connected, this, &Window::connectedToServer);
    connect(m_Client, &Client::loggedIn, this, &Window::loggedIn);
    connect(m_Client, &Client::disconnected, this, &Window::disconnectedFromServer);
    connect(m_Client, &Client::error, this, &Window::error);
    connect(m_Client, &Client::playerCount, this, &Window::playerCount);
    connect(m_Client, &Client::countDown, this, &Window::countDown);
    connect(m_Client, &Client::countDownFinished, this, &Window::countDownFinished);
    connect(m_Client, &Client::loginDuplicate, this, &Window::loginDuplicate);
    connect(m_Client, &Client::finishRound, this, &Window::finishRound);
    connect(m_Client, &Client::userLimit, this, &Window::userLimit);

    connect(ui->connectButton, &QPushButton::clicked, this, &Window::attemptConnection);
    connect(ui->startButton, &QPushButton::clicked, this, &Window::startGame);
    connect(ui->buttonA, &QPushButton::clicked, this, &Window::sendMessage);
    connect(ui->buttonB, &QPushButton::clicked, this, &Window::sendMessage);
    connect(ui->buttonC, &QPushButton::clicked, this, &Window::sendMessage);
    connect(ui->buttonD, &QPushButton::clicked, this, &Window::sendMessage);
    connect(ui->buttonE, &QPushButton::clicked, this, &Window::sendMessage);
    connect(ui->buttonF, &QPushButton::clicked, this, &Window::sendMessage);
    connect(ui->buttonG, &QPushButton::clicked, this, &Window::sendMessage);
    connect(ui->buttonH, &QPushButton::clicked, this, &Window::sendMessage);
}

Window::~Window()
{
    delete ui;
}

void Window::attemptConnection()
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
    m_Client->connectToServer(QHostAddress(hostAddress), 2000);
}

void Window::startGame()
{
    ui->connectButton->setEnabled(false);
    m_Client->startGame();
}

void Window::connectedToServer()
{
    const QString newUsername = QInputDialog::getText(this, tr("Chose Username"), tr("Username"));
    if (newUsername.isEmpty()){
        QMessageBox::warning(this, "Error", "Empty login");
        return m_Client->disconnectFromHost();
    }
    attemptLogin(newUsername);
}

void Window::attemptLogin(const QString &userName)
{
    m_Client->login(userName);
}

void Window::sendMessage()
{
    auto button = qobject_cast<QPushButton *>(sender());
    QString message = button->objectName();
    m_Client->sendMessage("answer,"+QString::number(message[message.length()-1].unicode()-65));
}

void Window::disconnectedFromServer()
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
    ui->connectButton->setEnabled(true);
    ui->startButton->setEnabled(false);
    ui->playerCount->setText("Number of players: 0");
    ui->countDown->setText("");
}

void Window::clearBoard()
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
}

void Window::resetPlayers()
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

void Window::loggedIn()
{
    qDebug() << "Logged in successfully";
    ui->countDown->setText("Logged in successfully");
}

void Window::playerCount(const int &n, const QJsonObject &players)
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

void Window::countDown(const int &timer)
{
    ui->countDown->setText("Game will begin in " + QString::number(timer) + " seconds or when host will press start");
}

void Window::countDownFinished(const bool &success, const int &card, const int &boardCard)
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

void Window::loginDuplicate()
{
    QMessageBox::warning(this, "Error", "Duplicate username");
}

void Window::userLimit()
{
    qDebug() << "too many players";
    QMessageBox::warning(this, "Error", "Too many players");
}

void Window::finishRound(const int isWin, const QString &username)
{
    clearBoard();
    if (isWin) {
        ui->countDown->setText("You won");
    } else {
        ui->countDown->setText(username+" won");
    }
}

void Window::error(QAbstractSocket::SocketError socketError)
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
}
