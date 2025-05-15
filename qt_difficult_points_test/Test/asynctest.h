// asynctest.h
#ifndef ASYNCTEST_H
#define ASYNCTEST_H

#include <QObject>
#include <QtTest/QtTest>
#include <QTimer>

class AsyncTest : public QObject {
    Q_OBJECT
private slots:
    void testTimer();
};

#endif // ASYNCTEST_H
