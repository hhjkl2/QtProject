#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTranslator>

class LanguageSwitcher : public QWidget {
    Q_OBJECT

public:
    LanguageSwitcher(QWidget *parent = nullptr) : QWidget(parent) {
        setupUi();
        setupTranslator();
    }

private slots:
    void onChineseClicked() {
        changeLanguage(":/res/languages/zh_CN.qm");
    }

    void onEnglishClicked() {
        changeLanguage(":/res/languages/en_US.qm");
    }

    void onFrenchClicked() {
        changeLanguage(":/res/languages/fr_FR.qm");
    }

private:
    void setupUi() {
        QVBoxLayout *layout = new QVBoxLayout(this);

        // 创建一个标签，显示问候语
        label = new QLabel(QObject::tr("Hello, World!"), this);
        layout->addWidget(label);

        // 创建语言切换按钮
        chineseButton = new QPushButton(QObject::tr("Chinese"), this);
        englishButton = new QPushButton(QObject::tr("English"), this);
        frenchButton = new QPushButton(QObject::tr("French"), this);

        // 连接按钮点击信号到相应的槽函数
        connect(chineseButton, &QPushButton::clicked, this, &LanguageSwitcher::onChineseClicked);
        connect(englishButton, &QPushButton::clicked, this, &LanguageSwitcher::onEnglishClicked);
        connect(frenchButton, &QPushButton::clicked, this, &LanguageSwitcher::onFrenchClicked);

        // 将按钮添加到布局中
        layout->addWidget(chineseButton);
        layout->addWidget(englishButton);
        layout->addWidget(frenchButton);
    }

    void setupTranslator() {
        // 创建一个 QTranslator 对象
        translator = new QTranslator(this);
    }

    void changeLanguage(const QString &qmFile) {
        // 移除当前的翻译器
        qApp->removeTranslator(translator);
        // 尝试加载指定的 .qm 文件
        if (translator->load(qmFile)) {
            // 安装新的翻译器
            qApp->installTranslator(translator);
            // 更新界面上的文本
            label->setText(QObject::tr("Hello, World!"));
            chineseButton->setText(QObject::tr("Chinese"));
            englishButton->setText(QObject::tr("English"));
            frenchButton->setText(QObject::tr("French"));
        }
    }

    QLabel *label;
    QPushButton *chineseButton;
    QPushButton *englishButton;
    QPushButton *frenchButton;
    QTranslator *translator;
};

#include "main.moc"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    LanguageSwitcher w;
    w.show();

    return a.exec();
}
