#ifndef CUSTOMPAGE_H
#define CUSTOMPAGE_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class CustomPage : public QWidget
{
    Q_OBJECT
public:
    explicit CustomPage(const QString &text, QWidget *parent = nullptr) : QWidget(parent)
    {
        QLabel *label = new QLabel(text, this);
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(label);
        setLayout(layout);
    }
};

#endif // CUSTOMPAGE_H
