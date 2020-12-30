#include "serverwindow.h"
#include "ui_serverwindow.h"
#include "chatserver.h"
#include <QMessageBox>

ServerWindow::ServerWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServerWindow)
    , m_chatServer(new ChatServer(this))
{
    ui->setupUi(this);
    connect(ui->startStopButton, &QPushButton::clicked, this, &ServerWindow::toggleStartServer);
    connect(m_chatServer, &ChatServer::logMessage, this, &ServerWindow::logMessage);
    connect(m_chatServer, &ChatServer::addUser, this, &ServerWindow::addUser);
}

ServerWindow::~ServerWindow()
{
    delete ui;
}

void ServerWindow::addUser(const int &n)
{
    ui->playersCount->setText(tr("Liczba graczy ")+QString::number(n));
}

void ServerWindow::toggleStartServer()
{
    if (m_chatServer->isListening()) {
        m_chatServer->stopServer();
        ui->startStopButton->setText(tr("Start Server"));
        logMessage(QStringLiteral("Server Stopped"));
    } else {
        if (!m_chatServer->listen(QHostAddress::Any, 2000)) {
            QMessageBox::critical(this, tr("Error"), tr("Unable to start the server"));
            return;
        }
        logMessage(QStringLiteral("Server Started"));
        ui->startStopButton->setText(tr("Stop Server"));
    }
}

void ServerWindow::logMessage(const QString &msg)
{
    ui->logEditor->appendPlainText(msg + QLatin1Char('\n'));
}
