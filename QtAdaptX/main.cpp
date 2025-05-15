#include <QObject>
#include <QDebug>
#include <QApplication>
#include <functional>

// 通用回调适配器（模板类）
template <typename... Args>
class CallbackAdapter : public QObject {
    Q_OBJECT
public:
    using CallbackType = std::function<void(Args...)>;

    explicit CallbackAdapter(QObject* parent = nullptr) : QObject(parent) {}

    // 设置第三方回调，并绑定到Qt信号
    void setCallback(CallbackType cb) {
        m_callback = [this, cb](Args... args) {
            cb(args...);          // 执行原始回调
            emit signalEmitted(args...); // 触发Qt信号
        };
    }

    // 获取回调函数（供第三方库注册）
    CallbackType getCallback() const {
        return m_callback;
    }

signals:
    void signalEmitted(Args... args); // 泛型信号（参数类型与回调一致）

private:
    CallbackType m_callback;
};

// 测试：第三方库（支持两种回调类型）
namespace ThirdPartyLib {
using IntCallback = std::function<void(int)>;
using StringCallback = std::function<void(const QString&)>;

static IntCallback intCb;
static StringCallback strCb;

void triggerIntEvent(int value) { if (intCb) intCb(value); }
void triggerStringEvent(const QString& msg) { if (strCb) strCb(msg); }
}

// 客户端：处理信号的组件
class Client : public QObject {
    Q_OBJECT
public:
    explicit Client(QObject* parent = nullptr) : QObject(parent) {}

public slots:
    void onIntEvent(int value) {
        qDebug() << "接收到整数事件：" << value;
    }

    void onStringEvent(const QString& msg) {
        qDebug() << "接收到字符串事件：" << msg;
    }
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // 适配int类型回调
    CallbackAdapter<int> intAdapter;
    ThirdPartyLib::intCb = intAdapter.getCallback();
    QObject::connect(&intAdapter, &CallbackAdapter<int>::signalEmitted,
                     new Client(), &Client::onIntEvent);

    // 适配QString类型回调
    CallbackAdapter<const QString&> strAdapter;
    ThirdPartyLib::strCb = strAdapter.getCallback();
    QObject::connect(&strAdapter, &CallbackAdapter<const QString&>::signalEmitted,
                     new Client(), &Client::onStringEvent);

    // 模拟第三方库触发事件
    ThirdPartyLib::triggerIntEvent(42);       // 输出：接收到整数事件：42
    ThirdPartyLib::triggerStringEvent("Hello"); // 输出：接收到字符串事件：Hello

    return app.exec();
}

#include "main.moc"
