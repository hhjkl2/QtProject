#include <QCoreApplication>
#include <QStateMachine>
#include <QState>
#include <QFinalState>
#include <QReadWriteLock>
#include <QAtomicInt>
#include <QDebug>
#include <QThread>

// 定义全局变量和读写锁
QReadWriteLock globalDataLock;
QAtomicInt stateIdentifier(0);

// 模拟多个全局变量
const int NUM_GLOBAL_VARIABLES = 20;
int globalVariables[NUM_GLOBAL_VARIABLES];

// 定义状态枚举
enum ProjectState {
    STATE_NEW,
    STATE_OPEN,
    STATE_SAVE,
    STATE_SIMULATING,
    STATE_RESULT_EXPORTING,
    STATE_CLOSED,
    STATE_ERROR
};

// 状态转移函数
void transitionToState(QStateMachine& machine, QState* targetState) {
    machine.postEvent(new QEvent(QEvent::StateMachineSignal));
    targetState->assignProperty(nullptr, "dummy", 1);
}

// 模拟多线程仿真任务
class SimulationThread : public QThread {
    Q_OBJECT
public:
    explicit SimulationThread(QStateMachine& machine, QState* simulatingState, QState* resultExportingState)
        : QThread(nullptr), m_machine(machine), m_simulatingState(simulatingState), m_resultExportingState(resultExportingState) {}

protected:
    void run() override {
        // 模拟仿真开始
        transitionToState(m_machine, m_simulatingState);
        // 模拟仿真耗时操作
        for (int i = 0; i < 10; ++i) {
            globalDataLock.lockForWrite();
            for (int j = 0; j < NUM_GLOBAL_VARIABLES; ++j) {
                globalVariables[j] = i * j;
            }
            stateIdentifier.fetchAndStoreOrdered(STATE_SIMULATING);
            globalDataLock.unlock();
            msleep(100);
        }
        // 模拟仿真结束，进入结果导出状态
        transitionToState(m_machine, m_resultExportingState);
    }

private:
    QStateMachine& m_machine;
    QState* m_simulatingState;
    QState* m_resultExportingState;
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // 创建状态机
    QStateMachine machine;

    // 定义状态
    QState *newState = new QState(&machine);
    QState *openState = new QState(&machine);
    QState *saveState = new QState(&machine);
    QState *simulatingState = new QState(&machine);
    QState *resultExportingState = new QState(&machine);
    QState *closedState = new QState(&machine);
    QState *errorState = new QState(&machine);
    QFinalState *finalState = new QFinalState(&machine);

    // 定义状态转移规则
    newState->addTransition(newState, SIGNAL(propertiesAssigned()), openState);
    openState->addTransition(openState, SIGNAL(propertiesAssigned()), saveState);
    saveState->addTransition(saveState, SIGNAL(propertiesAssigned()), simulatingState);
    simulatingState->addTransition(simulatingState, SIGNAL(propertiesAssigned()), resultExportingState);
    resultExportingState->addTransition(resultExportingState, SIGNAL(propertiesAssigned()), closedState);
    closedState->addTransition(closedState, SIGNAL(propertiesAssigned()), finalState);
    // 可以添加更多错误处理的转移规则
    newState->addTransition(errorState, SIGNAL(propertiesAssigned()), errorState);
    openState->addTransition(errorState, SIGNAL(propertiesAssigned()), errorState);
    saveState->addTransition(errorState, SIGNAL(propertiesAssigned()), errorState);
    simulatingState->addTransition(errorState, SIGNAL(propertiesAssigned()), errorState);
    resultExportingState->addTransition(errorState, SIGNAL(propertiesAssigned()), errorState);
    errorState->addTransition(errorState, SIGNAL(propertiesAssigned()), finalState);

    // 状态进入时的操作
    QObject::connect(newState, &QState::entered, [&]() {
        globalDataLock.lockForWrite();
        for (int i = 0; i < NUM_GLOBAL_VARIABLES; ++i) {
            globalVariables[i] = 0;
        }
        stateIdentifier.fetchAndStoreOrdered(STATE_NEW);
        globalDataLock.unlock();
        qDebug() << "Entered New State";
    });

    QObject::connect(openState, &QState::entered, [&]() {
        globalDataLock.lockForWrite();
        for (int i = 0; i < NUM_GLOBAL_VARIABLES; ++i) {
            globalVariables[i] = 1;
        }
        stateIdentifier.fetchAndStoreOrdered(STATE_OPEN);
        globalDataLock.unlock();
        qDebug() << "Entered Open State";
    });

    QObject::connect(saveState, &QState::entered, [&]() {
        globalDataLock.lockForWrite();
        for (int i = 0; i < NUM_GLOBAL_VARIABLES; ++i) {
            globalVariables[i] = 2;
        }
        stateIdentifier.fetchAndStoreOrdered(STATE_SAVE);
        globalDataLock.unlock();
        qDebug() << "Entered Save State";
    });

    QObject::connect(simulatingState, &QState::entered, [&]() {
        globalDataLock.lockForWrite();
        for (int i = 0; i < NUM_GLOBAL_VARIABLES; ++i) {
            globalVariables[i] = 3;
        }
        stateIdentifier.fetchAndStoreOrdered(STATE_SIMULATING);
        globalDataLock.unlock();
        qDebug() << "Entered Simulating State";
    });

    QObject::connect(resultExportingState, &QState::entered, [&]() {
        globalDataLock.lockForWrite();
        for (int i = 0; i < NUM_GLOBAL_VARIABLES; ++i) {
            globalVariables[i] = 4;
        }
        stateIdentifier.fetchAndStoreOrdered(STATE_RESULT_EXPORTING);
        globalDataLock.unlock();
        qDebug() << "Entered Result Exporting State";
    });

    QObject::connect(closedState, &QState::entered, [&]() {
        globalDataLock.lockForWrite();
        for (int i = 0; i < NUM_GLOBAL_VARIABLES; ++i) {
            globalVariables[i] = 5;
        }
        stateIdentifier.fetchAndStoreOrdered(STATE_CLOSED);
        globalDataLock.unlock();
        qDebug() << "Entered Closed State";
    });

    QObject::connect(errorState, &QState::entered, [&]() {
        globalDataLock.lockForWrite();
        for (int i = 0; i < NUM_GLOBAL_VARIABLES; ++i) {
            globalVariables[i] = -1;
        }
        stateIdentifier.fetchAndStoreOrdered(STATE_ERROR);
        globalDataLock.unlock();
        qDebug() << "Entered Error State";
    });

    QObject::connect(finalState, &QFinalState::entered, [&]() {
        qDebug() << "Entered Final State";
        a.quit();
    });

    // 设置初始状态
    machine.setInitialState(newState);

    // 启动状态机
    machine.start();

    // 启动仿真线程
    SimulationThread simulationThread(machine, simulatingState, resultExportingState);
    simulationThread.start();

    return a.exec();
}

#include "main.moc"
