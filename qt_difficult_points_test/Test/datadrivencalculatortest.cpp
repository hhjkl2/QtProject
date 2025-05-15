// datadrivencalculatortest.cpp
#include "datadrivencalculatortest.h"

void DataDrivenCalculatorTest::testAddition_data() {
    QTest::addColumn<int>("a");
    QTest::addColumn<int>("b");
    QTest::addColumn<int>("expected");

    QTest::newRow("test1") << 1 << 2 << 3;
    QTest::newRow("test2") << 5 << 3 << 8;
    QTest::newRow("test3") << 0 << 0 << 0;
}

void DataDrivenCalculatorTest::testAddition() {
    QFETCH(int, a);
    QFETCH(int, b);
    QFETCH(int, expected);

    Calculator calc;
    int result = calc.add(a, b);
    QCOMPARE(result, expected);
}
