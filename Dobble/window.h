#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QAbstractSocket>
#include "cards.h"

class Client;
class QStandardItemModel;
namespace Ui { class Window; }
class Window : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(Window)
public:
    explicit Window(QWidget *parent = nullptr);
    ~Window();
private:
    Ui::Window *ui;
    Client *m_Client;
    QStandardItemModel *m_Model;
    Cards *cards = new Cards;
private slots:
    void attemptConnection();
    void startGame();
    void connectedToServer();
    void attemptLogin(const QString &userName);
    void loggedIn();
    void sendMessage();
    void disconnectedFromServer();
    void resetPlayers();
    void clearBoard();
    void playerCount(const int &count, const QJsonObject &players);
    void countDown(const int &timer);
    void countDownFinished(const bool &success, const int &card, const int &boardCard);
    void loginDuplicate();
    void userLimit();
    void block(const int &block);
    void finishRound(const int isWin, const QString &username);
    void error(QAbstractSocket::SocketError socketError);
};

#endif // WINDOW_H
