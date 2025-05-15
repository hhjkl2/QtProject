#ifndef ORDER_H
#define ORDER_H

// 订单结构体（ID、时间、状态、金额）
struct Order {
    QString id;
    QDateTime time;
    QString status; // "待支付"、"已发货"、"已完成"
    double amount;
};

#endif // ORDER_H
