#ifndef MYQLABEL_H
#define MYQLABEL_H

#include <QLabel>

class MyQLabel : public QLabel
{
public:
    MyQLabel();

    void resizeEvent(QResizeEvent *event) override {
        QLabel::resizeEvent(event);
        setPixmap(pixmap().scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
};

#endif // MYQLABEL_H
