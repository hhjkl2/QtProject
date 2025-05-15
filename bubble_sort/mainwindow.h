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
    int arr[9] = {8, 6, 5, 4, 9, 7, 1, 2, 3};
    int n = 9;
    int i = 0;
    int j = 0;
    bool sorted = false;
    QLabel *labels[9];  // 用于显示每个元素的标签数组
    QHBoxLayout *layout;
    void updateLabel();
    void createLabels();
};

#endif // MAINWINDOW_H
