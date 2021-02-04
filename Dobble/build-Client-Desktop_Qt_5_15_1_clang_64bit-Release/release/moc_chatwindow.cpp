/****************************************************************************
** Meta object code from reading C++ file 'chatwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Client/chatwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chatwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ChatWindow_t {
    QByteArrayData data[35];
    char stringdata0[390];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ChatWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ChatWindow_t qt_meta_stringdata_ChatWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ChatWindow"
QT_MOC_LITERAL(1, 11, 17), // "attemptConnection"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 9), // "startGame"
QT_MOC_LITERAL(4, 40, 17), // "connectedToServer"
QT_MOC_LITERAL(5, 58, 12), // "attemptLogin"
QT_MOC_LITERAL(6, 71, 8), // "userName"
QT_MOC_LITERAL(7, 80, 8), // "loggedIn"
QT_MOC_LITERAL(8, 89, 11), // "loginFailed"
QT_MOC_LITERAL(9, 101, 6), // "reason"
QT_MOC_LITERAL(10, 108, 15), // "messageReceived"
QT_MOC_LITERAL(11, 124, 4), // "text"
QT_MOC_LITERAL(12, 129, 11), // "sendMessage"
QT_MOC_LITERAL(13, 141, 22), // "disconnectedFromServer"
QT_MOC_LITERAL(14, 164, 10), // "userJoined"
QT_MOC_LITERAL(15, 175, 8), // "username"
QT_MOC_LITERAL(16, 184, 12), // "resetPlayers"
QT_MOC_LITERAL(17, 197, 10), // "clearBoard"
QT_MOC_LITERAL(18, 208, 11), // "playerCount"
QT_MOC_LITERAL(19, 220, 5), // "count"
QT_MOC_LITERAL(20, 226, 7), // "players"
QT_MOC_LITERAL(21, 234, 9), // "countDown"
QT_MOC_LITERAL(22, 244, 5), // "timer"
QT_MOC_LITERAL(23, 250, 17), // "countDownFinished"
QT_MOC_LITERAL(24, 268, 7), // "success"
QT_MOC_LITERAL(25, 276, 4), // "card"
QT_MOC_LITERAL(26, 281, 9), // "boardCard"
QT_MOC_LITERAL(27, 291, 14), // "loginDuplicate"
QT_MOC_LITERAL(28, 306, 9), // "userLimit"
QT_MOC_LITERAL(29, 316, 11), // "finishRound"
QT_MOC_LITERAL(30, 328, 5), // "isWin"
QT_MOC_LITERAL(31, 334, 8), // "userLeft"
QT_MOC_LITERAL(32, 343, 5), // "error"
QT_MOC_LITERAL(33, 349, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(34, 378, 11) // "socketError"

    },
    "ChatWindow\0attemptConnection\0\0startGame\0"
    "connectedToServer\0attemptLogin\0userName\0"
    "loggedIn\0loginFailed\0reason\0messageReceived\0"
    "text\0sendMessage\0disconnectedFromServer\0"
    "userJoined\0username\0resetPlayers\0"
    "clearBoard\0playerCount\0count\0players\0"
    "countDown\0timer\0countDownFinished\0"
    "success\0card\0boardCard\0loginDuplicate\0"
    "userLimit\0finishRound\0isWin\0userLeft\0"
    "error\0QAbstractSocket::SocketError\0"
    "socketError"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ChatWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  114,    2, 0x08 /* Private */,
       3,    0,  115,    2, 0x08 /* Private */,
       4,    0,  116,    2, 0x08 /* Private */,
       5,    1,  117,    2, 0x08 /* Private */,
       7,    0,  120,    2, 0x08 /* Private */,
       8,    1,  121,    2, 0x08 /* Private */,
      10,    1,  124,    2, 0x08 /* Private */,
      12,    0,  127,    2, 0x08 /* Private */,
      13,    0,  128,    2, 0x08 /* Private */,
      14,    1,  129,    2, 0x08 /* Private */,
      16,    0,  132,    2, 0x08 /* Private */,
      17,    0,  133,    2, 0x08 /* Private */,
      18,    2,  134,    2, 0x08 /* Private */,
      21,    1,  139,    2, 0x08 /* Private */,
      23,    3,  142,    2, 0x08 /* Private */,
      27,    0,  149,    2, 0x08 /* Private */,
      28,    0,  150,    2, 0x08 /* Private */,
      29,    2,  151,    2, 0x08 /* Private */,
      31,    1,  156,    2, 0x08 /* Private */,
      32,    1,  159,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QJsonObject,   19,   20,
    QMetaType::Void, QMetaType::Int,   22,
    QMetaType::Void, QMetaType::Bool, QMetaType::Int, QMetaType::Int,   24,   25,   26,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   30,   15,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void, 0x80000000 | 33,   34,

       0        // eod
};

void ChatWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ChatWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->attemptConnection(); break;
        case 1: _t->startGame(); break;
        case 2: _t->connectedToServer(); break;
        case 3: _t->attemptLogin((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->loggedIn(); break;
        case 5: _t->loginFailed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->messageReceived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->sendMessage(); break;
        case 8: _t->disconnectedFromServer(); break;
        case 9: _t->userJoined((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->resetPlayers(); break;
        case 11: _t->clearBoard(); break;
        case 12: _t->playerCount((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const QJsonObject(*)>(_a[2]))); break;
        case 13: _t->countDown((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 14: _t->countDownFinished((*reinterpret_cast< const bool(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< const int(*)>(_a[3]))); break;
        case 15: _t->loginDuplicate(); break;
        case 16: _t->userLimit(); break;
        case 17: _t->finishRound((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 18: _t->userLeft((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 19: _t->error((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 19:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ChatWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ChatWindow.data,
    qt_meta_data_ChatWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ChatWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ChatWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ChatWindow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ChatWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
