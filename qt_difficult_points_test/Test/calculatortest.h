// calculatortest.h
#ifndef CALCULATORTEST_H
#define CALCULATORTEST_H

#include <QObject>
#include <QtTest/QtTest>
#include "calculator.h"

class CalculatorTest : public QObject {
    Q_OBJECT
private slots:
    void testAddition();
    void testSubtraction();
    void testMultiplication();
    void testDivision();
    void testDivisionByZero();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();
};

#endif // CALCULATORTEST_H
