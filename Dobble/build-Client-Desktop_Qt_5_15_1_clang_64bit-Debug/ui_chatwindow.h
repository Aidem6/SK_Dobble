/********************************************************************************
** Form generated from reading UI file 'chatwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATWINDOW_H
#define UI_CHATWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatWindow
{
public:
    QGridLayout *gridLayout;
    QLabel *cardsLeft1;
    QPushButton *buttonB;
    QLabel *labelH;
    QLabel *labelC;
    QPushButton *buttonG;
    QPushButton *buttonH;
    QLabel *labelB;
    QLabel *playerName1;
    QLabel *countDown;
    QLabel *labelG;
    QLabel *labelD;
    QPushButton *buttonA;
    QLabel *labelF;
    QPushButton *buttonE;
    QFrame *line;
    QPushButton *buttonC;
    QPushButton *buttonF;
    QProgressBar *progressBar_1;
    QPushButton *startButton;
    QLabel *labelE;
    QPushButton *connectButton;
    QPushButton *buttonD;
    QListView *chatView;
    QLabel *labelA;
    QLabel *playerName2;
    QLabel *playerName3;
    QLabel *playerName4;
    QLabel *playerName5;
    QLabel *playerName6;
    QLabel *playerName7;
    QLabel *playerName8;
    QLabel *cardsLeft2;
    QLabel *cardsLeft3;
    QLabel *cardsLeft4;
    QLabel *cardsLeft5;
    QLabel *cardsLeft6;
    QLabel *cardsLeft7;
    QLabel *cardsLeft8;
    QProgressBar *progressBar_2;
    QProgressBar *progressBar_3;
    QProgressBar *progressBar_4;
    QProgressBar *progressBar_5;
    QProgressBar *progressBar_6;
    QProgressBar *progressBar_7;
    QProgressBar *progressBar_8;
    QLabel *playerCount;

    void setupUi(QWidget *ChatWindow)
    {
        if (ChatWindow->objectName().isEmpty())
            ChatWindow->setObjectName(QString::fromUtf8("ChatWindow"));
        ChatWindow->resize(409, 526);
        gridLayout = new QGridLayout(ChatWindow);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        cardsLeft1 = new QLabel(ChatWindow);
        cardsLeft1->setObjectName(QString::fromUtf8("cardsLeft1"));
        cardsLeft1->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(cardsLeft1, 11, 8, 1, 1);

        buttonB = new QPushButton(ChatWindow);
        buttonB->setObjectName(QString::fromUtf8("buttonB"));
        buttonB->setEnabled(false);

        gridLayout->addWidget(buttonB, 9, 3, 1, 2);

        labelH = new QLabel(ChatWindow);
        labelH->setObjectName(QString::fromUtf8("labelH"));
        labelH->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labelH, 7, 7, 1, 2);

        labelC = new QLabel(ChatWindow);
        labelC->setObjectName(QString::fromUtf8("labelC"));
        labelC->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labelC, 6, 5, 1, 2);

        buttonG = new QPushButton(ChatWindow);
        buttonG->setObjectName(QString::fromUtf8("buttonG"));
        buttonG->setEnabled(false);

        gridLayout->addWidget(buttonG, 10, 5, 1, 2);

        buttonH = new QPushButton(ChatWindow);
        buttonH->setObjectName(QString::fromUtf8("buttonH"));
        buttonH->setEnabled(false);

        gridLayout->addWidget(buttonH, 10, 7, 1, 2);

        labelB = new QLabel(ChatWindow);
        labelB->setObjectName(QString::fromUtf8("labelB"));
        labelB->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labelB, 6, 3, 1, 2);

        playerName1 = new QLabel(ChatWindow);
        playerName1->setObjectName(QString::fromUtf8("playerName1"));

        gridLayout->addWidget(playerName1, 11, 1, 1, 2);

        countDown = new QLabel(ChatWindow);
        countDown->setObjectName(QString::fromUtf8("countDown"));
        countDown->setMinimumSize(QSize(357, 0));

        gridLayout->addWidget(countDown, 4, 1, 1, 9);

        labelG = new QLabel(ChatWindow);
        labelG->setObjectName(QString::fromUtf8("labelG"));
        labelG->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labelG, 7, 5, 1, 2);

        labelD = new QLabel(ChatWindow);
        labelD->setObjectName(QString::fromUtf8("labelD"));
        labelD->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labelD, 6, 7, 1, 2);

        buttonA = new QPushButton(ChatWindow);
        buttonA->setObjectName(QString::fromUtf8("buttonA"));
        buttonA->setEnabled(true);

        gridLayout->addWidget(buttonA, 9, 1, 1, 2);

        labelF = new QLabel(ChatWindow);
        labelF->setObjectName(QString::fromUtf8("labelF"));
        labelF->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labelF, 7, 3, 1, 2);

        buttonE = new QPushButton(ChatWindow);
        buttonE->setObjectName(QString::fromUtf8("buttonE"));
        buttonE->setEnabled(false);

        gridLayout->addWidget(buttonE, 10, 1, 1, 2);

        line = new QFrame(ChatWindow);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 8, 1, 1, 8);

        buttonC = new QPushButton(ChatWindow);
        buttonC->setObjectName(QString::fromUtf8("buttonC"));
        buttonC->setEnabled(false);

        gridLayout->addWidget(buttonC, 9, 5, 1, 2);

        buttonF = new QPushButton(ChatWindow);
        buttonF->setObjectName(QString::fromUtf8("buttonF"));
        buttonF->setEnabled(false);

        gridLayout->addWidget(buttonF, 10, 3, 1, 2);

        progressBar_1 = new QProgressBar(ChatWindow);
        progressBar_1->setObjectName(QString::fromUtf8("progressBar_1"));
        progressBar_1->setEnabled(true);
        progressBar_1->setValue(0);

        gridLayout->addWidget(progressBar_1, 11, 3, 1, 5);

        startButton = new QPushButton(ChatWindow);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        startButton->setEnabled(false);

        gridLayout->addWidget(startButton, 3, 3, 1, 2);

        labelE = new QLabel(ChatWindow);
        labelE->setObjectName(QString::fromUtf8("labelE"));
        labelE->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labelE, 7, 1, 1, 2);

        connectButton = new QPushButton(ChatWindow);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));

        gridLayout->addWidget(connectButton, 3, 1, 1, 2);

        buttonD = new QPushButton(ChatWindow);
        buttonD->setObjectName(QString::fromUtf8("buttonD"));
        buttonD->setEnabled(false);

        gridLayout->addWidget(buttonD, 9, 7, 1, 2);

        chatView = new QListView(ChatWindow);
        chatView->setObjectName(QString::fromUtf8("chatView"));
        chatView->setEnabled(false);
        chatView->setEditTriggers(QAbstractItemView::NoEditTriggers);

        gridLayout->addWidget(chatView, 5, 0, 1, 10);

        labelA = new QLabel(ChatWindow);
        labelA->setObjectName(QString::fromUtf8("labelA"));
        labelA->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labelA, 6, 1, 1, 2);

        playerName2 = new QLabel(ChatWindow);
        playerName2->setObjectName(QString::fromUtf8("playerName2"));

        gridLayout->addWidget(playerName2, 12, 1, 1, 2);

        playerName3 = new QLabel(ChatWindow);
        playerName3->setObjectName(QString::fromUtf8("playerName3"));

        gridLayout->addWidget(playerName3, 13, 1, 1, 2);

        playerName4 = new QLabel(ChatWindow);
        playerName4->setObjectName(QString::fromUtf8("playerName4"));

        gridLayout->addWidget(playerName4, 14, 1, 1, 2);

        playerName5 = new QLabel(ChatWindow);
        playerName5->setObjectName(QString::fromUtf8("playerName5"));

        gridLayout->addWidget(playerName5, 15, 1, 1, 2);

        playerName6 = new QLabel(ChatWindow);
        playerName6->setObjectName(QString::fromUtf8("playerName6"));

        gridLayout->addWidget(playerName6, 16, 1, 1, 2);

        playerName7 = new QLabel(ChatWindow);
        playerName7->setObjectName(QString::fromUtf8("playerName7"));

        gridLayout->addWidget(playerName7, 17, 1, 1, 2);

        playerName8 = new QLabel(ChatWindow);
        playerName8->setObjectName(QString::fromUtf8("playerName8"));

        gridLayout->addWidget(playerName8, 18, 1, 1, 2);

        cardsLeft2 = new QLabel(ChatWindow);
        cardsLeft2->setObjectName(QString::fromUtf8("cardsLeft2"));
        cardsLeft2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(cardsLeft2, 12, 8, 1, 1);

        cardsLeft3 = new QLabel(ChatWindow);
        cardsLeft3->setObjectName(QString::fromUtf8("cardsLeft3"));
        cardsLeft3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(cardsLeft3, 13, 8, 1, 1);

        cardsLeft4 = new QLabel(ChatWindow);
        cardsLeft4->setObjectName(QString::fromUtf8("cardsLeft4"));
        cardsLeft4->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(cardsLeft4, 14, 8, 1, 1);

        cardsLeft5 = new QLabel(ChatWindow);
        cardsLeft5->setObjectName(QString::fromUtf8("cardsLeft5"));
        cardsLeft5->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(cardsLeft5, 15, 8, 1, 1);

        cardsLeft6 = new QLabel(ChatWindow);
        cardsLeft6->setObjectName(QString::fromUtf8("cardsLeft6"));
        cardsLeft6->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(cardsLeft6, 16, 8, 1, 1);

        cardsLeft7 = new QLabel(ChatWindow);
        cardsLeft7->setObjectName(QString::fromUtf8("cardsLeft7"));
        cardsLeft7->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(cardsLeft7, 17, 8, 1, 1);

        cardsLeft8 = new QLabel(ChatWindow);
        cardsLeft8->setObjectName(QString::fromUtf8("cardsLeft8"));
        cardsLeft8->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(cardsLeft8, 18, 8, 1, 1);

        progressBar_2 = new QProgressBar(ChatWindow);
        progressBar_2->setObjectName(QString::fromUtf8("progressBar_2"));
        progressBar_2->setEnabled(true);
        progressBar_2->setValue(0);

        gridLayout->addWidget(progressBar_2, 12, 3, 1, 5);

        progressBar_3 = new QProgressBar(ChatWindow);
        progressBar_3->setObjectName(QString::fromUtf8("progressBar_3"));
        progressBar_3->setValue(0);

        gridLayout->addWidget(progressBar_3, 13, 3, 1, 5);

        progressBar_4 = new QProgressBar(ChatWindow);
        progressBar_4->setObjectName(QString::fromUtf8("progressBar_4"));
        progressBar_4->setValue(0);

        gridLayout->addWidget(progressBar_4, 14, 3, 1, 5);

        progressBar_5 = new QProgressBar(ChatWindow);
        progressBar_5->setObjectName(QString::fromUtf8("progressBar_5"));
        progressBar_5->setValue(0);

        gridLayout->addWidget(progressBar_5, 15, 3, 1, 5);

        progressBar_6 = new QProgressBar(ChatWindow);
        progressBar_6->setObjectName(QString::fromUtf8("progressBar_6"));
        progressBar_6->setValue(0);

        gridLayout->addWidget(progressBar_6, 16, 3, 1, 5);

        progressBar_7 = new QProgressBar(ChatWindow);
        progressBar_7->setObjectName(QString::fromUtf8("progressBar_7"));
        progressBar_7->setValue(0);

        gridLayout->addWidget(progressBar_7, 17, 3, 1, 5);

        progressBar_8 = new QProgressBar(ChatWindow);
        progressBar_8->setObjectName(QString::fromUtf8("progressBar_8"));
        progressBar_8->setValue(0);

        gridLayout->addWidget(progressBar_8, 18, 3, 1, 5);

        playerCount = new QLabel(ChatWindow);
        playerCount->setObjectName(QString::fromUtf8("playerCount"));

        gridLayout->addWidget(playerCount, 3, 5, 1, 4);


        retranslateUi(ChatWindow);

        QMetaObject::connectSlotsByName(ChatWindow);
    } // setupUi

    void retranslateUi(QWidget *ChatWindow)
    {
        ChatWindow->setWindowTitle(QCoreApplication::translate("ChatWindow", "Qt Simple Chat Client", nullptr));
        cardsLeft1->setText(QString());
        buttonB->setText(QCoreApplication::translate("ChatWindow", "B", nullptr));
        labelH->setText(QCoreApplication::translate("ChatWindow", "H", nullptr));
        labelC->setText(QCoreApplication::translate("ChatWindow", "C", nullptr));
        buttonG->setText(QCoreApplication::translate("ChatWindow", "G", nullptr));
        buttonH->setText(QCoreApplication::translate("ChatWindow", "H", nullptr));
        labelB->setText(QCoreApplication::translate("ChatWindow", "B", nullptr));
        playerName1->setText(QString());
        countDown->setText(QString());
        labelG->setText(QCoreApplication::translate("ChatWindow", "G", nullptr));
        labelD->setText(QCoreApplication::translate("ChatWindow", "D", nullptr));
        buttonA->setText(QCoreApplication::translate("ChatWindow", "A", nullptr));
        labelF->setText(QCoreApplication::translate("ChatWindow", "F", nullptr));
        buttonE->setText(QCoreApplication::translate("ChatWindow", "E", nullptr));
        buttonC->setText(QCoreApplication::translate("ChatWindow", "C", nullptr));
        buttonF->setText(QCoreApplication::translate("ChatWindow", "F", nullptr));
        startButton->setText(QCoreApplication::translate("ChatWindow", "Start", nullptr));
        labelE->setText(QCoreApplication::translate("ChatWindow", "E", nullptr));
        connectButton->setText(QCoreApplication::translate("ChatWindow", "Connect", nullptr));
        buttonD->setText(QCoreApplication::translate("ChatWindow", "D", nullptr));
        labelA->setText(QCoreApplication::translate("ChatWindow", "A", nullptr));
        playerName2->setText(QString());
        playerName3->setText(QString());
        playerName4->setText(QString());
        playerName5->setText(QString());
        playerName6->setText(QString());
        playerName7->setText(QString());
        playerName8->setText(QString());
        cardsLeft2->setText(QString());
        cardsLeft3->setText(QString());
        cardsLeft4->setText(QString());
        cardsLeft5->setText(QString());
        cardsLeft6->setText(QString());
        cardsLeft7->setText(QString());
        cardsLeft8->setText(QString());
        playerCount->setText(QCoreApplication::translate("ChatWindow", "Number of players: 0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatWindow: public Ui_ChatWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATWINDOW_H
