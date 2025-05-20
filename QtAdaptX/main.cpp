#include <QObject>
#include <QDebug>
#include <QCache>
#include <QTimer>
#include <QApplication>
#include <QDateTime>

// 底层数据库（模拟）
class Database : public QObject {
    Q_OBJECT
public:
    explicit Database(QObject* parent = nullptr) : QObject(parent) {
        // 模拟数据库数据（id → 姓名）
        m_data = { {1, "Alice"}, {2, "Bob"}, {3, "Charlie"} };
    }

    QString queryUser(int id) {
        QTimer::singleShot(100, this, [id]() { // 模拟查询延迟
            qDebug() << "数据库查询：id=" << id;
        });
        return m_data.value(id, "Unknown");
    }

signals:
    void dataChanged(int id); // 数据变更信号（如用户修改姓名）

private:
    QHash<int, QString> m_data;
};

// 带缓存的适配器
class CachedAdapter : public QObject {
    Q_OBJECT
public:
    explicit CachedAdapter(Database* db, QObject* parent = nullptr)
        : QObject(parent), m_db(db), m_cache(100) { // 缓存容量100项
        connect(m_db, &Database::dataChanged, this, &CachedAdapter::invalidateCache);
    }

    // 查询用户（优先使用缓存）
    QString getUser(int id) {
        if (m_cache.contains(id)) {
            return m_cache.object(id)->name;
        }

        // 缓存未命中，查询数据库并更新缓存
        QString name = m_db->queryUser(id);
        UserInfo* info = new UserInfo();
        info->name = name;
        info->timestamp = QDateTime::currentDateTime();
        m_cache.insert(id, info); // 插入缓存
        return name;
    }

private:
    struct UserInfo {
        QString name;
        QDateTime timestamp;
    };

    void invalidateCache(int id) {
        m_cache.remove(id); // 数据变更时失效对应缓存
        qDebug() << "缓存失效：id=" << id;
    }

    Database* m_db;
    QCache<int, UserInfo> m_cache; // 缓存：id → 用户信息
};

// 客户端：频繁查询用户的组件
class Client : public QObject {
    Q_OBJECT
public:
    explicit Client(CachedAdapter* adapter, QObject* parent = nullptr)
        : QObject(parent), m_adapter(adapter) {
        // 模拟频繁查询
        QTimer* timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &Client::queryUser);
        timer->start(500);
    }

public slots:
    void queryUser() {
        static int id = 1;
        QString name = m_adapter->getUser(id);
        qDebug() << "查询结果：id=" << id << "，姓名=" << name;
        id = (id % 3) + 1; // 循环查询id=1,2,3
    }
private:
    CachedAdapter* m_adapter;
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    Database db;
    CachedAdapter adapter(&db);
    Client client(&adapter);

    // 模拟数据库数据变更（触发缓存失效）
    QTimer::singleShot(2500, &db, [&db]() {
        emit db.dataChanged(1); // id=1的数据变更
    });

    return app.exec();
}

#include "main.moc"
