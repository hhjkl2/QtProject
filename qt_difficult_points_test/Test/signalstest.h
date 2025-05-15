// signalstest.h
#ifndef SIGNALSTEST_H
#define SIGNALSTEST_H

#include <QObject>
#include <QtTest/QtTest>
#include <QPushButton>

class SignalsTest : public QObject {
    Q_OBJECT
private slots:
    void testButtonClick();
};

#endif // SIGNALSTEST_H
