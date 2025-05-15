// calculatortest.cpp
#include "calculatortest.h"

void CalculatorTest::testAddition() {
    Calculator calc;
    int result = calc.add(2, 3);
    QCOMPARE(result, 5);
}

void CalculatorTest::testSubtraction() {
    Calculator calc;
    int result = calc.subtract(5, 3);
    QCOMPARE(result, 2);
}

void CalculatorTest::testMultiplication() {
    Calculator calc;
    int result = calc.multiply(2, 3);
    QCOMPARE(result, 6);
}

void CalculatorTest::testDivision() {
    Calculator calc;
    double result = calc.divide(6, 3);
    QCOMPARE(result, 2.0);
}

void CalculatorTest::testDivisionByZero() {
    Calculator calc;
    QVERIFY_EXCEPTION_THROWN(calc.divide(6, 0), std::runtime_error);
}

void CalculatorTest::initTestCase() {
    // 全局初始化操作，如打开数据库连接
}

void CalculatorTest::cleanupTestCase() {
    // 全局清理操作，如关闭数据库连接
}

void CalculatorTest::init() {
    // 每个测试用例前的初始化操作，如创建临时文件
}

void CalculatorTest::cleanup() {
    // 每个测试用例后的清理操作，如删除临时文件
}
