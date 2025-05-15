#include "udpcommunicator.h"

#include <QVariant>

UdpCommunicator::UdpCommunicator(QObject *parent) : QObject(parent)
{
    udpSocket = new QUdpSocket(this);
    connect(udpSocket, &QUdpSocket::readyRead, this, &UdpCommunicator::readPendingDatagrams);
    connect(udpSocket, SIGNAL(errorOccurred(QAbstractSocket::SocketError)), this, SLOT(handleSocketError(QAbstractSocket::SocketError)));
}

UdpCommunicator::~UdpCommunicator()
{
    if (udpSocket->isOpen()) {
        udpSocket->close();
    }
    delete udpSocket;
}

bool UdpCommunicator::bindToPort(quint16 port)
{
    return udpSocket->bind(QHostAddress::Any, port);
}

void UdpCommunicator::sendData(const QByteArray &data, const QHostAddress &address, quint16 port)
{
    qint64 bytesWritten = udpSocket->writeDatagram(data, address, port);
    if (bytesWritten == -1) {
        qDebug() << "Error sending data:" << udpSocket->errorString();
    }
}

bool UdpCommunicator::joinMulticastGroup(const QHostAddress &groupAddress)
{
    return udpSocket->joinMulticastGroup(groupAddress);
}

void UdpCommunicator::sendMulticastData(const QByteArray &data, const QHostAddress &groupAddress, quint16 port)
{
    udpSocket->setSocketOption(QAbstractSocket::MulticastTtlOption, QVariant(1));
    qint64 bytesWritten = udpSocket->writeDatagram(data, groupAddress, port);
    if (bytesWritten == -1) {
        qDebug() << "Error sending multicast data:" << udpSocket->errorString();
    }
}

QByteArray serializeData(const MyData &data)
{
    QByteArray byteArray;
    QDataStream stream(&byteArray, QIODevice::WriteOnly);
    stream << data.id << data.name;
    return byteArray;
}

MyData deserializeData(const QByteArray &byteArray)
{
    MyData data;
    QDataStream stream(const_cast<QByteArray*>(&byteArray), QIODevice::ReadOnly);
    stream >> data.id >> data.name;
    return data;
}

void UdpCommunicator::sendSerializedData(const MyData &data, const QHostAddress &address, quint16 port)
{
    QByteArray serializedData = serializeData(data);
    sendData(serializedData, address, port);
}

void UdpCommunicator::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        MyData receivedData = deserializeData(datagram);
        qDebug() << "Received data from" << sender.toString() << ":" << senderPort;
        qDebug() << "ID:" << receivedData.id << "Name:" << receivedData.name;
    }
}

void UdpCommunicator::handleSocketError(QAbstractSocket::SocketError socketError)
{
    qDebug() << "Socket error:" << udpSocket->errorString();
    switch (socketError) {
    case QAbstractSocket::ConnectionRefusedError:
        qDebug() << "Connection refused";
        break;
    case QAbstractSocket::RemoteHostClosedError:
        qDebug() << "Remote host closed";
        break;
    default:
        break;
    }
}
