#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QVBoxLayout>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
private:
    Ui::MainWindow *ui;
    int arr[5] = {5, 4, 3, 2, 1};
    int n = 5;
    int i = 0;
    int j = 1;
    int minIndex = 0;
    bool sorted = false;
    QLabel *labels[5];
    QHBoxLayout *arrayLayout;
    void createLabels();
    void updateLabels();
    void swapLabels(int index1, int index2);
    void initLabels();
};

#endif // MAINWINDOW_H
