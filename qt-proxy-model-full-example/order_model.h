// order_model.h
#ifndef ORDER_MODEL_H
#define ORDER_MODEL_H

#include <QAbstractTableModel>
#include <QDateTime>
#include <QVector>
#include "order.h"

class OrderModel : public QAbstractTableModel {
    Q_OBJECT
public:
    explicit OrderModel(QObject *parent = nullptr)
        : QAbstractTableModel(parent) {}

    // 在C++模型中定义角色名称​
    enum Roles {
        IdRole = Qt::UserRole + 1,
        TimeRole,
        StatusRole,
        AmountRole
    };

    QHash<int, QByteArray> roleNames() const override {
        QHash<int, QByteArray> roles;
        roles[IdRole] = "id";
        roles[TimeRole] = "time";
        roles[StatusRole] = "status";
        roles[AmountRole] = "amount";
        return roles;
    }

    // 模拟添加订单（实际可从数据库/网络加载）
    void addOrder(const Order &order) {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        m_orders.append(order);
        endInsertRows();
    }

    // 实现QAbstractItemModel接口
    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        return parent.isValid() ? 0 : m_orders.size();
    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override {
        return 4; // 四列：ID、时间、状态、金额
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        if (!index.isValid() || index.row() >= m_orders.size()) return QVariant();
        const Order &order = m_orders[index.row()];
        if (role == Qt::DisplayRole) {
            // 处理表格视图的列显示
            switch (index.column()) {
            case 0: return order.id;
            case 1: return order.time.toString("yyyy-MM-dd hh:mm");
            case 2: return order.status;
            case 3: return QString::number(order.amount, 'f', 2);
            default: return QVariant();
            }
        } else if (role == Qt::UserRole) {
            // 处理排序使用的原始数据
            switch (index.column()) {
            case 1: return order.time.toMSecsSinceEpoch();
            case 3: return order.amount;
            default: return QVariant();
            }
        }

        // 处理自定义角色（供QML使用）
        switch (role) {
        case IdRole:
            return order.id;
        case TimeRole:
            return order.time.toString("yyyy-MM-dd hh:mm");
        case StatusRole:
            return order.status;
        case AmountRole:
            return QString::number(order.amount, 'f', 2);
        default:
            return QVariant();
        }
    }

private:
    QVector<Order> m_orders;
};

#endif // ORDER_MODEL_H
