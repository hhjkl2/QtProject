// datadrivencalculatortest.h
#ifndef DATADRIVENCALCULATORTEST_H
#define DATADRIVENCALCULATORTEST_H

#include <QObject>
#include <QtTest/QtTest>
#include "calculator.h"

class DataDrivenCalculatorTest : public QObject {
    Q_OBJECT
private slots:
    void testAddition_data();
    void testAddition();
};

#endif // DATADRIVENCALCULATORTEST_H
