#include "customwidget.h"
#include "ui_customwidget.h"
#include <QMessageBox>

CustomWidget::CustomWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CustomWidget)
{
    ui->setupUi(this);
}

CustomWidget::~CustomWidget()
{
    delete ui;
}

void CustomWidget::on_pushButton_clicked()
{
    QMessageBox::information(this, "提示", "按钮被点击了！");
}
