#include <QApplication>
#include <QWidget>
#include <QFormLayout>
#include <QScrollArea>
#include <QPropertyAnimation>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QComboBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QDebug>
#include <QScrollBar>

// 控件工厂类
class WidgetFactory {
public:
    static QWidget* createWidget(const QString& type) {
        if (type == "bool") {
            QComboBox* combo = new QComboBox();
            combo->addItem("True");
            combo->addItem("False");
            combo->setObjectName("bool");
            return combo;
        } else if (type == "number") {
            QSpinBox* spinBox = new QSpinBox();
            spinBox->setObjectName("number");
            return spinBox;
        } else if (type == "string") {
            QLineEdit* lineEdit = new QLineEdit();
            lineEdit->setObjectName("string");
            return lineEdit;
        }
        return nullptr;
    }
};

// 对象池类
class WidgetPool {
public:
    WidgetPool() {}

    QWidget* acquireWidget(const QString& type) {
        for (auto it = pool.begin(); it != pool.end(); ++it) {
            if (it->first == type && it->second->parent() == nullptr) {
                QWidget* widget = it->second;
                pool.erase(it);
                return widget;
            }
        }
        return WidgetFactory::createWidget(type);
    }

    void releaseWidget(QWidget* widget) {
        pool.append({widget->objectName(), widget});
    }

private:
    QList<QPair<QString, QWidget*>> pool;
};

// 动态生成 UI
void generateUI(const QJsonObject& jsonConfig, QWidget* parent, WidgetPool& pool) {
    QFormLayout* layout = new QFormLayout(parent);
    for (auto it = jsonConfig.begin(); it != jsonConfig.end(); ++it) {
        QString paramName = it.key();
        QJsonObject paramConfig = it.value().toObject();
        QString type = paramConfig["type"].toString();
        QWidget* widget = pool.acquireWidget(type);
        layout->addRow(paramName, widget);
    }
    parent->setLayout(layout);
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // 读取 JSON 配置文件
    QFile file(":/config.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open JSON file.";
        return -1;
    }
    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
    QJsonObject jsonConfig = jsonDoc.object();

    // 创建主窗口和滚动区域
    QWidget mainWidget;
    QScrollArea scrollArea;
    QWidget contentWidget;
    scrollArea.setWidget(&contentWidget);
    scrollArea.setWidgetResizable(true);

    // 创建对象池
    WidgetPool widgetPool;

    // 动态生成 UI
    generateUI(jsonConfig, &contentWidget, widgetPool);

    // 滚动动画
    QPropertyAnimation* animation = new QPropertyAnimation(scrollArea.verticalScrollBar(), "value");
    animation->setDuration(500);
    animation->setStartValue(0);
    animation->setEndValue(scrollArea.verticalScrollBar()->maximum());
    animation->start();

    // 显示主窗口
    scrollArea.show();

    return a.exec();
}
