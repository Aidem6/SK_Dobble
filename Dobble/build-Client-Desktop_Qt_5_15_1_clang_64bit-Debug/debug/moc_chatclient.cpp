/****************************************************************************
** Meta object code from reading C++ file 'chatclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Client/chatclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chatclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ChatClient_t {
    QByteArrayData data[34];
    char stringdata0[352];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ChatClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ChatClient_t qt_meta_stringdata_ChatClient = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ChatClient"
QT_MOC_LITERAL(1, 11, 9), // "connected"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 8), // "loggedIn"
QT_MOC_LITERAL(4, 31, 10), // "loginError"
QT_MOC_LITERAL(5, 42, 6), // "reason"
QT_MOC_LITERAL(6, 49, 12), // "disconnected"
QT_MOC_LITERAL(7, 62, 15), // "messageReceived"
QT_MOC_LITERAL(8, 78, 4), // "text"
QT_MOC_LITERAL(9, 83, 5), // "error"
QT_MOC_LITERAL(10, 89, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(11, 118, 11), // "socketError"
QT_MOC_LITERAL(12, 130, 10), // "userJoined"
QT_MOC_LITERAL(13, 141, 8), // "username"
QT_MOC_LITERAL(14, 150, 11), // "playerCount"
QT_MOC_LITERAL(15, 162, 5), // "count"
QT_MOC_LITERAL(16, 168, 7), // "players"
QT_MOC_LITERAL(17, 176, 9), // "countDown"
QT_MOC_LITERAL(18, 186, 5), // "timer"
QT_MOC_LITERAL(19, 192, 17), // "countDownFinished"
QT_MOC_LITERAL(20, 210, 7), // "success"
QT_MOC_LITERAL(21, 218, 4), // "card"
QT_MOC_LITERAL(22, 223, 9), // "boardCard"
QT_MOC_LITERAL(23, 233, 8), // "userLeft"
QT_MOC_LITERAL(24, 242, 15), // "connectToServer"
QT_MOC_LITERAL(25, 258, 12), // "QHostAddress"
QT_MOC_LITERAL(26, 271, 7), // "address"
QT_MOC_LITERAL(27, 279, 4), // "port"
QT_MOC_LITERAL(28, 284, 9), // "startGame"
QT_MOC_LITERAL(29, 294, 5), // "login"
QT_MOC_LITERAL(30, 300, 8), // "userName"
QT_MOC_LITERAL(31, 309, 11), // "sendMessage"
QT_MOC_LITERAL(32, 321, 18), // "disconnectFromHost"
QT_MOC_LITERAL(33, 340, 11) // "onReadyRead"

    },
    "ChatClient\0connected\0\0loggedIn\0"
    "loginError\0reason\0disconnected\0"
    "messageReceived\0text\0error\0"
    "QAbstractSocket::SocketError\0socketError\0"
    "userJoined\0username\0playerCount\0count\0"
    "players\0countDown\0timer\0countDownFinished\0"
    "success\0card\0boardCard\0userLeft\0"
    "connectToServer\0QHostAddress\0address\0"
    "port\0startGame\0login\0userName\0sendMessage\0"
    "disconnectFromHost\0onReadyRead"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ChatClient[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x06 /* Public */,
       3,    0,  100,    2, 0x06 /* Public */,
       4,    1,  101,    2, 0x06 /* Public */,
       6,    0,  104,    2, 0x06 /* Public */,
       7,    1,  105,    2, 0x06 /* Public */,
       9,    1,  108,    2, 0x06 /* Public */,
      12,    1,  111,    2, 0x06 /* Public */,
      14,    2,  114,    2, 0x06 /* Public */,
      17,    1,  119,    2, 0x06 /* Public */,
      19,    3,  122,    2, 0x06 /* Public */,
      23,    1,  129,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      24,    2,  132,    2, 0x0a /* Public */,
      28,    0,  137,    2, 0x0a /* Public */,
      29,    1,  138,    2, 0x0a /* Public */,
      31,    1,  141,    2, 0x0a /* Public */,
      32,    0,  144,    2, 0x0a /* Public */,
      33,    0,  145,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, QMetaType::Int, QMetaType::QJsonObject,   15,   16,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void, QMetaType::Bool, QMetaType::QJsonObject, QMetaType::QJsonObject,   20,   21,   22,
    QMetaType::Void, QMetaType::QString,   13,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 25, QMetaType::UShort,   26,   27,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   30,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ChatClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ChatClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connected(); break;
        case 1: _t->loggedIn(); break;
        case 2: _t->loginError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->disconnected(); break;
        case 4: _t->messageReceived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->error((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 6: _t->userJoined((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->playerCount((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const QJsonObject(*)>(_a[2]))); break;
        case 8: _t->countDown((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 9: _t->countDownFinished((*reinterpret_cast< const bool(*)>(_a[1])),(*reinterpret_cast< const QJsonObject(*)>(_a[2])),(*reinterpret_cast< const QJsonObject(*)>(_a[3]))); break;
        case 10: _t->userLeft((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->connectToServer((*reinterpret_cast< const QHostAddress(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2]))); break;
        case 12: _t->startGame(); break;
        case 13: _t->login((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 14: _t->sendMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 15: _t->disconnectFromHost(); break;
        case 16: _t->onReadyRead(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ChatClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatClient::connected)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ChatClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatClient::loggedIn)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ChatClient::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatClient::loginError)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ChatClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatClient::disconnected)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ChatClient::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatClient::messageReceived)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ChatClient::*)(QAbstractSocket::SocketError );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatClient::error)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (ChatClient::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatClient::userJoined)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (ChatClient::*)(const int & , const QJsonObject & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatClient::playerCount)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (ChatClient::*)(const int & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatClient::countDown)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (ChatClient::*)(const bool & , const QJsonObject & , const QJsonObject & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatClient::countDownFinished)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (ChatClient::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatClient::userLeft)) {
                *result = 10;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ChatClient::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ChatClient.data,
    qt_meta_data_ChatClient,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ChatClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ChatClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ChatClient.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ChatClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void ChatClient::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ChatClient::loggedIn()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ChatClient::loginError(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ChatClient::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void ChatClient::messageReceived(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ChatClient::error(QAbstractSocket::SocketError _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ChatClient::userJoined(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ChatClient::playerCount(const int & _t1, const QJsonObject & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void ChatClient::countDown(const int & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void ChatClient::countDownFinished(const bool & _t1, const QJsonObject & _t2, const QJsonObject & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void ChatClient::userLeft(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
