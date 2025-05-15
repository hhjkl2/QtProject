// status_filter_proxy.h
#ifndef STATUS_FILTER_PROXY_H
#define STATUS_FILTER_PROXY_H

#include <QSortFilterProxyModel>

class StatusFilterProxy : public QSortFilterProxyModel {
    Q_OBJECT
public:
    explicit StatusFilterProxy(QObject *parent = nullptr)
        : QSortFilterProxyModel(parent) {}

    // 设置目标状态（如"已发货"）
    void setTargetStatus(const QString &status) {
        m_targetStatus = status;
        invalidateFilter();
    }

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override {
        if (!sourceModel()) return false;
        QModelIndex statusIndex = sourceModel()->index(source_row, 2, source_parent);
        qDebug() << sourceModel()->data(statusIndex).toString();
        return sourceModel()->data(statusIndex).toString() == m_targetStatus;
    }

private:
    QString m_targetStatus;
};

#endif // STATUS_FILTER_PROXY_H
