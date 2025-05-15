// signalstest.cpp
#include "signalstest.h"

void SignalsTest::testButtonClick() {
    QPushButton button("Click me");
    bool clicked = false;

    QObject::connect(&button, &QPushButton::clicked, [&clicked]() {
        clicked = true;
    });

    QTest::mouseClick(&button, Qt::LeftButton);
    QVERIFY(clicked);
}
