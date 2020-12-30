#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>
#include <QAbstractSocket>
class ChatClient;
class QStandardItemModel;
namespace Ui { class ChatWindow; }
class ChatWindow : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(ChatWindow)
public:
    explicit ChatWindow(QWidget *parent = nullptr);
    ~ChatWindow();
private:
    Ui::ChatWindow *ui;
    ChatClient *m_chatClient;
    QStandardItemModel *m_chatModel;
private slots:
    void attemptConnection();
    void startGame();
    void connectedToServer();
    void attemptLogin(const QString &userName);
    void loggedIn();
    void loginFailed(const QString &reason);
    void messageReceived(const QString &text);
    void sendMessage();
    void disconnectedFromServer();
    void userJoined(const QString &username);
    void resetPlayers();
    void playerCount(const int &count, const QJsonObject &players);
    void countDown(const int &timer);
    void countDownFinished(const bool &success, const QJsonObject &card, const QJsonObject &boardCard);
    void userLeft(const QString &username);
    void error(QAbstractSocket::SocketError socketError);
};

#endif // CHATWINDOW_H
