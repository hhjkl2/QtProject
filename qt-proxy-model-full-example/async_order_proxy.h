// async_order_proxy.h
#ifndef ASYNC_ORDER_PROXY_H
#define ASYNC_ORDER_PROXY_H

#include <QAbstractProxyModel>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "order.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include "order_model.h"

class AsyncOrderProxy : public QAbstractProxyModel {
    Q_OBJECT
public:
    explicit AsyncOrderProxy(QObject *parent = nullptr)
        : QAbstractProxyModel(parent), m_manager(new QNetworkAccessManager(this)) {
        connect(m_manager, &QNetworkAccessManager::finished, this, &AsyncOrderProxy::onReplyFinished);
    }

    QHash<int, QByteArray> roleNames() const override {
        if (sourceModel()) {
            return sourceModel()->roleNames();
        }
        return QAbstractProxyModel::roleNames();
    }

    // 触发异步加载（模拟从URL获取订单数据）
    void loadFromUrl(const QUrl &url) {
       //m_manager->get(QNetworkRequest(url));

        // 模拟测试数据
        QVector<Order> testOrders = {
            {"A1", QDateTime::currentDateTime(), "已发货", 99.9},
            {"A2", QDateTime::currentDateTime().addDays(-1), "已完成", 149.9},
            {"A3", QDateTime::currentDateTime().addMonths(-1), "已发货", 299.9},
            {"A4", QDateTime::currentDateTime().addMonths(1), "已发货", 999.9}
        };
       // 创建OrderModel并填充数据
       OrderModel *localModel = new OrderModel(this);
       for (const auto &order : testOrders) {
           localModel->addOrder(order);
       }
       // 设置源模型
       setSourceModel(localModel);
    }

    // 实现QAbstractProxyModel接口（简化示例，仅处理行数据）
    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        return sourceModel() ? sourceModel()->rowCount(parent) : 0;
    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override {
        return sourceModel() ? sourceModel()->columnCount(parent) : 0;
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        if (!index.isValid() || index.row() >= sourceModel()->rowCount() || !sourceModel()) return QVariant();
        // 将请求转发到源模型的对应索引
        QModelIndex sourceIndex = mapToSource(index);
        return sourceModel()->data(sourceIndex, role);

        /* 除了使用源模型OrderModel ，也可以使用自己的m_loadedOrders,此时AsyncOrderProxy就是其他的源模型
        const Order &order = m_loadedOrders[index.row()];
        switch (role) {
        case Qt::DisplayRole: {
            switch (index.column()) {
            case 0: return order.id;
            case 1: return order.time.toString("yyyy-MM-dd hh:mm");
            case 2: return order.status;
            case 3: return QString::number(order.amount, 'f', 2);
            default: return QVariant();
            }
        }
        case Qt::UserRole: // 用于排序的原始数据
            switch (index.column()) {
            case 1: return order.time.toMSecsSinceEpoch();
            case 3: return order.amount;
            default: return QVariant();
            }
        default: return QVariant();
        }
        */
    }

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override {
        if (row >= 0 && row < rowCount(parent) && column >= 0 && column < columnCount(parent) && !parent.isValid()) {
            return createIndex(row, column);
        }
        return QModelIndex();
    }

    QModelIndex parent(const QModelIndex &child) const override {
        Q_UNUSED(child);
        return QModelIndex(); // 平面结构，无父节点
    }

    QModelIndex mapFromSource(const QModelIndex &sourceIndex) const override {
        // 异步加载后，源模型为本地缓存，直接返回索引
        if (!sourceModel() || !sourceIndex.isValid())
            return QModelIndex();
        // 创建代理索引，行和列与源模型相同
        return createIndex(sourceIndex.row(), sourceIndex.column());
    }

    QModelIndex mapToSource(const QModelIndex &proxyIndex) const override {
        if (!sourceModel() || !proxyIndex.isValid())
            return QModelIndex();
        // 返回源模型的索引
        return sourceModel()->index(proxyIndex.row(), proxyIndex.column());
    }

private:
    QVector<Order> parseOrdersFromJson(const QByteArray &jsonData) {
        QVector<Order> orders;

        // 示例解析逻辑（需根据实际JSON结构修改）
        QJsonDocument doc = QJsonDocument::fromJson(jsonData);
        if (doc.isArray()) {
            QJsonArray array = doc.array();
            for (const QJsonValue &value : array) {
                QJsonObject obj = value.toObject();
                Order order;
                order.id = obj["id"].toString();
                order.time = QDateTime::fromString(obj["time"].toString(), Qt::ISODate);
                order.status = obj["status"].toString();
                order.amount = obj["amount"].toDouble();
                orders.append(order);
            }
        }
        return orders;
    }

private slots:
    void onReplyFinished(QNetworkReply *reply) {
        if (reply->error() == QNetworkReply::NoError) {
            // 模拟解析JSON数据（实际需解析reply->readAll()）
            QVector<Order> newOrders = parseOrdersFromJson(reply->readAll());
            beginResetModel();
            m_loadedOrders = newOrders;
            endResetModel();
            // 将加载后的数据设置为源模型（本地缓存）
            if (sourceModel()) sourceModel()->deleteLater();
            OrderModel *localModel = new OrderModel(this);
            for (const auto &order : newOrders) localModel->addOrder(order);
            setSourceModel(localModel);
        }else{
            beginResetModel();
            m_loadedOrders.clear();
            if (sourceModel()) sourceModel()->deleteLater();
            setSourceModel(nullptr);
            endResetModel();
            qWarning() << "加载失败:" << reply->errorString();
        }
        reply->deleteLater();
    }

private:
    QVector<Order> m_loadedOrders; // 异步加载的订单缓存
    QNetworkAccessManager *m_manager;
};

#endif // ASYNC_ORDER_PROXY_H
