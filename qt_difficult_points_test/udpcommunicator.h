#ifndef UDPCOMMUNICATOR_H
#define UDPCOMMUNICATOR_H

#include <QObject>
#include <QUdpSocket>
#include <QByteArray>
#include <QHostAddress>
#include <QDebug>

struct MyData {
    int id;
    QString name;
};

class UdpCommunicator : public QObject
{
    Q_OBJECT
public:
    explicit UdpCommunicator(QObject *parent = nullptr);
    ~UdpCommunicator();

    bool bindToPort(quint16 port);
    void sendData(const QByteArray &data, const QHostAddress &address, quint16 port);
    bool joinMulticastGroup(const QHostAddress &groupAddress);
    void sendMulticastData(const QByteArray &data, const QHostAddress &groupAddress, quint16 port);
    void sendSerializedData(const MyData &data, const QHostAddress &address, quint16 port);

private slots:
    void readPendingDatagrams();
    void handleSocketError(QAbstractSocket::SocketError socketError);

private:
    QUdpSocket *udpSocket;
};

QByteArray serializeData(const MyData &data);
MyData deserializeData(const QByteArray &byteArray);

#endif // UDPCOMMUNICATOR_H
