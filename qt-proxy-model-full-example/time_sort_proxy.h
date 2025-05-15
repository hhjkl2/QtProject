// time_sort_proxy.h
#ifndef TIME_SORT_PROXY_H
#define TIME_SORT_PROXY_H

#include <QIdentityProxyModel> // 轻量级透明代理基类

class TimeSortProxy : public QIdentityProxyModel {
    Q_OBJECT
public:
    explicit TimeSortProxy(QObject *parent = nullptr)
        : QIdentityProxyModel(parent), m_ascending(true) {
        connect(this, &QIdentityProxyModel::sourceModelChanged, this, &TimeSortProxy::onSourceModelChanged);
    }

    void onSourceModelChanged() {
        QAbstractItemModel *oldModel = sourceModel();
        if (oldModel) {
            disconnect(oldModel, nullptr, this, nullptr); // 断开旧模型的所有信号
        }
        if (sourceModel()) {
            connect(sourceModel(), &QAbstractItemModel::dataChanged, this, &TimeSortProxy::invalidateCache);
            connect(sourceModel(), &QAbstractItemModel::rowsInserted, this, &TimeSortProxy::invalidateCache);
            connect(sourceModel(), &QAbstractItemModel::rowsRemoved, this, &TimeSortProxy::invalidateCache);
            connect(sourceModel(), &QAbstractItemModel::modelReset, this, &TimeSortProxy::invalidateCache);
        }
        invalidateCache();
    }

    void invalidateCache() {

        if (sourceModel()) {
            beginResetModel();
            m_sortedRows.clear();
            endResetModel();
        }else {
            m_sortedRows.clear();
        }
    }

    // 切换排序方向（升序/降序）
    void toggleSortOrder() {
        m_ascending = !m_ascending;
        invalidateCache();
    }

    // 重写排序逻辑（基于UserRole的时间戳）
    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override {
        Q_UNUSED(column);
        m_ascending = (order == Qt::AscendingOrder);
        invalidateCache();
    }

    // 重写index()实现排序后的索引映射
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override {
        if (!parent.isValid() && row >= 0 && row < rowCount()) {
            // 按时间排序后的源行号
            int sourceRow = sortedSourceRows().at(row);
            return mapFromSource(sourceModel()->index(sourceRow, column));
        }
        return QModelIndex();
    }

private:
    // 获取排序后的源行号列表（缓存优化）
    QVector<int> sortedSourceRows() const {
        if (!sourceModel() || sourceModel()->rowCount() == 0) return {};
        if (m_sortedRows.isEmpty()) {
            // 从源模型获取所有行的时间戳
            QVector<qint64> timestamps;
            for (int i = 0; i < sourceModel()->rowCount(); ++i) {
                timestamps.append(sourceModel()->index(i, 1).data(Qt::UserRole).toLongLong());
            }
            // 排序并记录源行号
            QVector<int> rows(sourceModel()->rowCount());
            std::iota(rows.begin(), rows.end(), 0);
            std::sort(rows.begin(), rows.end(), [&](int a, int b) {
                return m_ascending ? timestamps[a] < timestamps[b] : timestamps[a] > timestamps[b];
            });
            m_sortedRows = rows;
        }
        return m_sortedRows;
    }

    mutable QVector<int> m_sortedRows; // 缓存排序后的源行号
    bool m_ascending;
};

#endif // TIME_SORT_PROXY_H
