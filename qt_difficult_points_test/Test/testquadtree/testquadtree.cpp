// // testquadtree.cpp
// #include "testquadtree.h"
// #include <QRectF>

// void TestQuadtree::testInsertWithinBounds() {
//     QRectF bounds(0, 0, 100, 100);
//     QuadTreeNode node(bounds, 4);
//     DataPoint p{10, 10};
//     QVERIFY(node.insert(p)); // 插入成功应返回 true
// }

// void TestQuadtree::testInsertOutsideBounds() {
//     QRectF bounds(0, 0, 100, 100);
//     QuadTreeNode node(bounds, 4);
//     DataPoint p{150, 150};
//     QVERIFY(!node.insert(p)); // 插入失败应返回 false
// }

// void TestQuadtree::testSubdivision() {
//     QRectF bounds(0, 0, 100, 100);
//     QuadTreeNode node(bounds, 2); // 容量设为 2

//     // 插入三个点触发分割
//     node.insert({10, 10});
//     node.insert({20, 20});
//     QVERIFY(node.insert({30, 30})); // 插入第三个点应成功

//     // 验证子节点已创建
//     // 注：需在 QuadTreeNode 中添加访问子节点的方法（测试专用）
//     // 假设存在访问函数 northWest() 等
//     // QVERIFY(node.northWest() != nullptr);
// }

// void TestQuadtree::testQuery() {
//     QRectF bounds(0, 0, 100, 100);
//     QuadTreeNode node(bounds, 4);

//     // 插入测试点
//     node.insert({10, 10});
//     node.insert({90, 90});

//     // 查询左下半区域
//     QVector<DataPoint> results;
//     node.query(QRectF(0, 0, 50, 50), results);
//     // 查询后添加调试信息
//     if (results.size() != 1) {
//         qDebug() << "查询结果异常，找到的点:";
//         for (const auto& p : results) {
//             qDebug() << "坐标: (" << p.x << "," << p.y << ")";
//         }
//     }
//     QCOMPARE(results.size(), 1); // 应找到 (10,10)
// }

// void TestQuadtree::testEdgeCases() {
//     QRectF bounds(0, 0, 100, 100);
//     QuadTreeSIMD node(bounds, 2);

//     // 插入点刚好在边界上
//     DataPoint edgePoint{100, 100};
//     QVERIFY(node.insert(edgePoint));

//     // 查询包含边界的区域
//     QVector<DataPoint> results;
//     node.query(QRectF(99, 99, 2, 2), results);
//     // 添加调试输出
//     if (results.isEmpty()) {
//         qDebug() << "边界点未找到，查询区域:"
//                  << QRectF(99, 99, 2, 2);
//     }
//     QCOMPARE(results.size(), 1);
// }

// #include <QElapsedTimer>
// #define COUNT 10'000'000

// void TestQuadtree::testPerformanceInsert() {
//     QRectF bounds(0, 0, 1000, 1000);
//     QuadTreeNode node(bounds, 4);
//     QElapsedTimer timer;

//     // 插入1000万个随机点
//     timer.start();
//     for (int i = 0; i < COUNT; ++i) {
//         DataPoint p{QRandomGenerator::global()->bounded(1000.0),
//                     QRandomGenerator::global()->bounded(1000.0)};
//         node.insert(p);
//     }
//     qint64 elapsed = timer.elapsed();
//     qDebug() << "插入1000万点耗时:" << elapsed << "ms";

//     // 验证时间在合理范围（根据硬件调整阈值）
//     QVERIFY2(elapsed < 40'000, u8"插入性能不达标");
// }

// void TestQuadtree::testPerformanceInsert2() {
//     QRectF bounds(0, 0, 1000, 1000);
//     QuadTreeNode2 node(bounds, 4);
//     QElapsedTimer timer;

//     // 插入1000万个随机点
//     timer.start();
//     for (int i = 0; i < COUNT; ++i) {
//         DataPoint p{QRandomGenerator::global()->bounded(1000.0),
//                     QRandomGenerator::global()->bounded(1000.0)};
//         node.insert(p);
//     }
//     qint64 elapsed = timer.elapsed();
//     qDebug() << "插入1000万点耗时:" << elapsed << "ms";

//     // 验证时间在合理范围（根据硬件调整阈值）
//     QVERIFY2(elapsed < 40'000, u8"插入性能不达标");
// }

// void TestQuadtree::testPerformanceInsert3() {
//     QRectF bounds(0, 0, 1000, 1000);
//     QuadTreeSIMD node(bounds, 4);
//     QElapsedTimer timer;

//     // 插入1000万个随机点
//     timer.start();
//     for (int i = 0; i < COUNT; ++i) {
//         // qDebug() << "执行第" << i << "次for循环";
//         DataPoint p{QRandomGenerator::global()->bounded(1000.0),
//                     QRandomGenerator::global()->bounded(1000.0)};
//         node.insert(p);
//     }
//     qint64 elapsed = timer.elapsed();
//     qDebug() << "插入1000万点耗时:" << elapsed << "ms";

//     // 验证时间在合理范围（根据硬件调整阈值）
//     QVERIFY2(elapsed < 40'000, u8"插入性能不达标");
// }

// void TestQuadtree::testPerformanceQuery() {
//     QRectF bounds(0, 0, 1000, 1000);
//     QuadTreeNode node(bounds, 4);

//     // 预填充数据
//     for (int i = 0; i < COUNT; ++i) {
//         DataPoint p{QRandomGenerator::global()->bounded(1000.0),
//                     QRandomGenerator::global()->bounded(1000.0)};
//         node.insert(p);
//     }

//     // 测试查询性能
//     QElapsedTimer timer;
//     timer.start();
//     QVector<DataPoint> results;
//     node.query(QRectF(200, 200, 600, 600), results);
//     qint64 elapsed = timer.elapsed();
//     qDebug() << "查询区域耗时:" << elapsed << "ms，找到点数:" << results.size();

//     QVERIFY2(elapsed < 1'000, u8"查询性能不达标");
// }

// void TestQuadtree::testPerformanceQuery2() {
//     QRectF bounds(0, 0, 1000, 1000);
//     QuadTreeNode2 node(bounds, 4);

//     // 预填充数据
//     for (int i = 0; i < COUNT; ++i) {
//         DataPoint p{QRandomGenerator::global()->bounded(1000.0),
//                     QRandomGenerator::global()->bounded(1000.0)};
//         node.insert(p);
//     }

//     // 测试查询性能
//     QElapsedTimer timer;
//     timer.start();
//     QVector<DataPoint> results;
//     node.query(QRectF(200, 200, 600, 600), results);
//     qint64 elapsed = timer.elapsed();
//     qDebug() << "查询区域耗时:" << elapsed << "ms，找到点数:" << results.size();

//     QVERIFY2(elapsed < 1'000, u8"查询性能不达标");
// }

// void TestQuadtree::testPerformanceQuery3() {
//     QRectF bounds(0, 0, 1000, 1000);
//     QuadTreeNode3 node(bounds, 4);

//     // 预填充数据
//     for (int i = 0; i < COUNT; ++i) {
//         DataPoint p{QRandomGenerator::global()->bounded(1000.0),
//                     QRandomGenerator::global()->bounded(1000.0)};
//         node.insert(p);
//     }

//     // 测试查询性能
//     QElapsedTimer timer;
//     timer.start();
//     QVector<DataPoint> results;
//     node.query(QRectF(200, 200, 600, 600), results);
//     qint64 elapsed = timer.elapsed();
//     qDebug() << "查询区域耗时:" << elapsed << "ms，找到点数:" << results.size();

//     QVERIFY2(elapsed < 1'000, u8"查询性能不达标");
// }


// void TestQuadtree::testStructureAfterSubdivision() {
//     QRectF bounds(0, 0, 100, 100);
//     QuadTreeNode node(bounds, 2); // 容量设为2

//     // 插入三个点触发分割
//     node.insert({10, 10});
//     node.insert({20, 20});
//     QVERIFY(node.insert({30, 30})); // 应成功插入

//     // 验证子节点指针非空
//     QVERIFY(node.m_northwest != nullptr);
//     QVERIFY(node.m_northeast != nullptr);
//     QVERIFY(node.m_southwest != nullptr);
//     QVERIFY(node.m_southeast != nullptr);

//     // 验证父节点数据未清空
//     QCOMPARE(node.m_points.size(), 2);
// }

// void TestQuadtree::testStructureAfterSubdivision2() {
//     QRectF bounds(0, 0, 100, 100);
//     QuadTreeNode2 node(bounds, 2); // 容量设为2

//     // 插入三个点触发分割
//     node.insert({10, 10});
//     node.insert({20, 20});
//     QVERIFY(node.insert({30, 30})); // 应成功插入

//     // 验证子节点指针非空
//     QVERIFY(node.m_northwest != nullptr);
//     QVERIFY(node.m_northeast != nullptr);
//     QVERIFY(node.m_southwest != nullptr);
//     QVERIFY(node.m_southeast != nullptr);

//     // 验证父节点数据已清空
//     QCOMPARE(node.m_points.size(), 0);
// }

// QTEST_APPLESS_MAIN(TestQuadtree)
// #include "testquadtree.moc"
