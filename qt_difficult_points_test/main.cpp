#include <QCoreApplication>
#include <QObject>
#include <QDebug>
#include <QEvent>

// 定义自定义事件类 CustomEvent
class CustomEvent : public QEvent {
public:
    static QEvent::Type eventType;
    explicit CustomEvent(const QString &data) : QEvent(eventType), data(data) {}
    QString getData() const { return data; }
private:
    QString data;
};

QEvent::Type CustomEvent::eventType = static_cast<QEvent::Type>(QEvent::registerEventType());

// 定义基类 BaseObject
class BaseObject : public QObject {
    Q_OBJECT
public:
    explicit BaseObject(QObject *parent = nullptr) : QObject(parent) {}
    bool event(QEvent *e) override {
        if (e->type() == CustomEvent::eventType) {
            handleMessage(static_cast<CustomEvent*>(e)->getData());
            return true;
        }
        return QObject::event(e);
    }
protected:
    virtual void handleMessage(const QString &message) {
        qDebug() << "BaseObject handling message:" << message;
    }
};

// 定义派生类 DerivedObject
class DerivedObject : public BaseObject {
    Q_OBJECT
public:
    explicit DerivedObject(QObject *parent = nullptr) : BaseObject(parent) {}
protected:
    void handleMessage(const QString &message) override {
        qDebug() << "DerivedObject handling message:" << message;
    }
};

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    BaseObject baseObject;
    DerivedObject derivedObject;

    // 发送自定义事件
    QCoreApplication::sendEvent(&baseObject, new CustomEvent("Message for base object"));
    QCoreApplication::sendEvent(&derivedObject, new CustomEvent("Message for derived object"));

    return app.exec();
}

#include "main.moc"
