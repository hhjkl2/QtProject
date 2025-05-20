#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>

class WorkerThread : public QThread
{
    Q_OBJECT
public:
    explicit WorkerThread(QObject *parent = nullptr);

signals:
    void progressUpdated(int value);

protected:
    void run() override;
};

#endif // WORKERTHREAD_H
