// asynctest.cpp
#include "asynctest.h"

void AsyncTest::testTimer() {
    QTimer timer;
    QSignalSpy spy(&timer, &QTimer::timeout);

    timer.start(100);
    QTest::qWait(200);

    QCOMPARE(spy.count(), 1);
}
