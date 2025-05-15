#include <QCoreApplication>
#include <QFile>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QFileSystemWatcher>
#include <QDebug>
#include <QMap>

class JsonParser {
public:
    // 解析JSON并返回配置映射
    QMap<QString, QJsonValue> parse(const QString &filePath) {
        QMap<QString, QJsonValue> configMap;
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly)) {
            qDebug() << "Failed to open file:" << filePath;
            return configMap;
        }

        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &error);
        file.close();

        if (error.error != QJsonParseError::NoError) {
            qDebug() << "JSON parsing error:" << error.errorString();
            return configMap;
        }

        if (!doc.isObject()) {
            qDebug() << "JSON root is not an object";
            return configMap;
        }

        QJsonObject root = doc.object();
        for (const QString &key : root.keys()) {
            QJsonValue value = root.value(key);
            configMap.insert(key, value);
            qDebug() << "Key:" << key << "Value:" << value;
        }

        return configMap;
    }
};

// 解析JSON文件的函数
void parseJsonFile(const QString &filePath) {
    JsonParser parser;
    QMap<QString, QJsonValue> configMap = parser.parse(filePath);
    qDebug() << "Parsed configuration items count:" << configMap.size();
}

// 监控文件变化的函数
void watchFile(const QString &filePath) {
    QFileSystemWatcher watcher;
    watcher.addPath(filePath);

    QObject::connect(&watcher, &QFileSystemWatcher::fileChanged, [filePath]() {
        qDebug() << "File changed:" << filePath;
        parseJsonFile(filePath);
    });
    qApp->exec();
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    //QString filePath = ":/config.json";//由于资源文件（:/config.json）是编译到程序内部的，​​无法监控文件变化​​
    QString filePath = "E:/qtProject/qt-large-json-parser/config.json";
    parseJsonFile(filePath);  // 首次解析
    watchFile(filePath);      // 启动监控

    return a.exec();
}
