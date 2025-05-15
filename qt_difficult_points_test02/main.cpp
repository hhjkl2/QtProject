#include <QtNetwork/QTcpSocket>
#include <QDebug>
#include <QCoreApplication>
#include <QTimer>

// 简单的异或加密函数
QByteArray encrypt(const QByteArray &data, char key)
{
    QByteArray encrypted = data;
    for (int i = 0; i < encrypted.size(); ++i) {
        encrypted[i] = encrypted[i] ^ key;
    }
    return encrypted;
}

// 简单的异或解密函数
QByteArray decrypt(const QByteArray &data, char key)
{
    return encrypt(data, key);
}

class SecureClient : public QObject
{
    Q_OBJECT
public:
    explicit SecureClient(QObject *parent = nullptr) : QObject(parent), encryptionKey('A')
    {
        socket = new QTcpSocket(this);
        reconnectTimer = new QTimer(this);
        reconnectTimer->setInterval(5000);

        connect(socket, &QTcpSocket::connected, this, &SecureClient::onConnected);
        connect(socket, &QTcpSocket::readyRead, this, &SecureClient::onReadyRead);
        connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::errorOccurred),
                this, &SecureClient::onError);
        connect(socket, &QTcpSocket::disconnected, this, &SecureClient::onDisconnected);
        connect(reconnectTimer, &QTimer::timeout, this, &SecureClient::reconnect);

        connectToServer();
    }

private slots:
    void onConnected()
    {
        qDebug() << "Connected to server.";
        reconnectTimer->stop();
        QByteArray message = "Hello, server!";
        QByteArray encryptedMessage = encrypt(message, encryptionKey);
        socket->write(encryptedMessage);
    }

    void onReadyRead()
    {
        QByteArray encryptedData = socket->readAll();
        QByteArray decryptedData = decrypt(encryptedData, encryptionKey);
        qDebug() << "Received response from server: " << decryptedData;
    }

    void onError(QAbstractSocket::SocketError socketError)
    {
        qDebug() << "Connection error: " << socket->errorString();
        reconnectTimer->start();
    }

    void onDisconnected()
    {
        qDebug() << "Disconnected from server.";
        reconnectTimer->start();
    }

    void reconnect()
    {
        qDebug() << "Trying to reconnect...";
        connectToServer();
    }

private:
    void connectToServer()
    {
        socket->connectToHost(QHostAddress::LocalHost, 1234);
    }

    QTcpSocket *socket;
    QTimer *reconnectTimer;
    char encryptionKey;
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SecureClient client;

    return a.exec();
}

#include "main.moc"
